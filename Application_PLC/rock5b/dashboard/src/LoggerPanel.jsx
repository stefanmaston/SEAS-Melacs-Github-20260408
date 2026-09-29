import { useEffect, useState } from "react";
import { LOG_KEYS, LOG_PREVIEW } from "../shared/columns.js";
import { alarmText, downloadMelacsCsv } from "./format.js";
import { TrendChart } from "./TrendChart.jsx";

const EXT_FULL_MV = 3300;
const Y_SCALES = Array.from({ length: 1000 }, (_, index) => (index + 1) * 10);

const SIGNAL_GROUPS = [
  {
    label: "Extern A/D, mV",
    options: Array.from({ length: 8 }, (_, index) => ({
      id: `an${index}`,
      label: `AN${index} mV`,
      key: `an${index}`,
    })),
  },
  {
    label: "PIC A/D",
    options: Array.from({ length: 8 }, (_, index) => ({
      id: `pic${index}`,
      label: `IO${index} analog`,
      key: `pic${index}`,
    })),
  },
  {
    label: "Puls in",
    options: Array.from({ length: 8 }, (_, index) => ({
      id: `pulse${index}`,
      label: `IO${index} puls`,
      key: `pulse${index}`,
    })),
  },
  {
    label: "Utgång",
    options: Array.from({ length: 8 }, (_, index) => ({
      id: `out${index}`,
      label: `IO${index} ut`,
      key: `out${index}`,
    })),
  },
  {
    label: "1-wire",
    options: Array.from({ length: 4 }, (_, index) => ({
      id: `wire${index + 1}`,
      label: `1-wire ${index + 1}`,
      key: `wire${index + 1}`,
    })),
  },
];

const SIGNALS = SIGNAL_GROUPS.flatMap((group) => group.options);

const CURVES = [
  { id: "leftA", axis: "left", color: "#03a9f4", caption: "Vänster" },
  { id: "leftB", axis: "left", color: "#7e57c2", caption: "Vänster 2" },
  { id: "rightA", axis: "right", color: "#ff9800", caption: "Höger" },
  { id: "rightB", axis: "right", color: "#4caf50", caption: "Höger 2" },
];

function signalById(id) {
  return SIGNALS.find((item) => item.id === id) || null;
}

function SignalSelect({ label, value, onChange }) {
  return (
    <label>
      {label}
      <select aria-label={label} value={value} onChange={(event) => onChange(event.target.value)}>
        <option value="">Ingen</option>
        {SIGNAL_GROUPS.map((group) => (
          <optgroup key={group.label} label={group.label}>
            {group.options.map((option) => (
              <option key={option.id} value={option.id}>{option.label}</option>
            ))}
          </optgroup>
        ))}
      </select>
    </label>
  );
}

function ScaleSelect({ label, value, onChange }) {
  return (
    <label>
      {label}
      <select aria-label={label} value={value} onChange={(event) => onChange(Number(event.target.value))}>
        {Y_SCALES.map((scale) => (
          <option key={scale} value={scale}>{scale}</option>
        ))}
      </select>
    </label>
  );
}

const WINDOWS = [
  { minutes: 1, label: "1 minut" },
  { minutes: 5, label: "5 minuter" },
  { minutes: 10, label: "10 minuter" },
  { minutes: 30, label: "30 minuter" },
  { minutes: 60, label: "1 timme" },
];

function rowTime(row) {
  return Date.parse(String(row.TimeStamp).replace(" ", "T"));
}

function rowsInWindow(rows, minutes) {
  const ordered = [...rows].sort((a, b) => rowTime(a) - rowTime(b));
  if (ordered.length === 0) return [];
  const latest = rowTime(ordered[ordered.length - 1]);
  if (!Number.isFinite(latest)) return ordered;
  const start = latest - minutes * 60 * 1000;
  return ordered.filter((row) => {
    const stamp = rowTime(row);
    return Number.isFinite(stamp) && stamp >= start && stamp <= latest + 5000;
  });
}

function chartSource(liveRows, sdRows) {
  const merged = new Map();
  for (const row of sdRows) merged.set(row.TimeStamp, enrich(row));
  for (const row of liveRows) {
    const previous = merged.get(row.TimeStamp) || {};
    merged.set(row.TimeStamp, { ...previous, ...enrich(row) });
  }
  return [...merged.values()];
}

function enrich(row) {
  const next = { ...row };
  for (let index = 0; index < 8; index += 1) {
    const raw = Number(row[`AD${index}`]);
    if (Number.isFinite(raw)) next[`an${index}`] = Math.round((raw * EXT_FULL_MV) / 4096);
    const level = Number(row[`DIO${index}`]);
    if (index >= 4 && Number.isFinite(level)) next[`out${index}`] = level;
  }
  if (!Number.isFinite(Number(next.an6)) && Number.isFinite(Number(row.T1))) {
    next.an6 = Math.round((Number(row.T1) * EXT_FULL_MV) / 4096);
  }
  if (!Number.isFinite(Number(next.an7)) && Number.isFinite(Number(row.T2))) {
    next.an7 = Math.round((Number(row.T2) * EXT_FULL_MV) / 4096);
  }
  return next;
}

export function LoggerPanel({ rows }) {
  const [full, setFull] = useState(false);
  const [minutes, setMinutes] = useState(10);
  const [picks, setPicks] = useState({
    leftA: "an0",
    leftB: "an1",
    rightA: "out4",
    rightB: "",
  });
  const [yMaxLeft, setYMaxLeft] = useState(3300);
  const [yMaxRight, setYMaxRight] = useState(10);
  const [sdRows, setSdRows] = useState([]);
  const [sdNote, setSdNote] = useState("Inga mätpunkter.");
  const columns = full ? LOG_KEYS : LOG_PREVIEW;
  const shown = rows.slice(-80).reverse();
  const chartRows = rowsInWindow(chartSource(rows, sdRows), minutes);
  const series = CURVES.flatMap((curve) => {
    const signal = signalById(picks[curve.id]);
    if (!signal) return [];
    return [{
      id: curve.id,
      key: signal.key,
      label: signal.label,
      color: curve.color,
      axis: curve.axis,
    }];
  });
  const chartNote = chartRows.length >= 2
    ? "AN0–AN7 är millivolt, full skala 3300. Puls, 1-wire och PIC A/D på IO0–IO7 saknas i loggen. IO4–IO7 ut är 0 eller 1."
    : sdNote;

  useEffect(() => {
    let stop = false;
    const load = async () => {
      try {
        const res = await fetch(`/api/history?minutes=${minutes}`, { cache: "no-store" });
        const data = await res.json();
        if (stop) return;
        if (!res.ok) {
          setSdRows([]);
          const text = alarmText(data.error);
          setSdNote(text && !/kontakt|svarade|bröt/i.test(text) ? text : "Inga mätpunkter.");
          return;
        }
        setSdRows(data.rows || []);
        setSdNote(data.rows && data.rows.length > 0 ? "" : "Inga loggrader i det här fönstret på SD-kortet.");
      } catch {
        if (!stop) setSdNote("Inga mätpunkter.");
      }
    };
    const tick = async () => {
      await load();
      if (!stop) timer = setTimeout(tick, 20000);
    };
    let timer;
    tick();
    return () => {
      stop = true;
      clearTimeout(timer);
    };
  }, [minutes]);

  const download = () => downloadMelacsCsv(rows);

  return (
    <div className="stack">
      <TrendChart
        title="Logg"
        note={chartNote}
        rows={chartRows}
        series={series}
        yMaxLeft={yMaxLeft}
        yMaxRight={yMaxRight}
        extra={(
          <label className="chart-window">
            Tidsfönster
            <select
              aria-label="Tidsfönster för diagrammet"
              value={minutes}
              onChange={(event) => setMinutes(Number(event.target.value))}
            >
              {WINDOWS.map((item) => (
                <option key={item.minutes} value={item.minutes}>{item.label}</option>
              ))}
            </select>
          </label>
        )}
        controls={(
          <div className="chart-picks">
            {CURVES.map((curve) => (
              <SignalSelect
                key={curve.id}
                label={curve.caption}
                value={picks[curve.id]}
                onChange={(value) => setPicks((current) => ({ ...current, [curve.id]: value }))}
              />
            ))}
            <ScaleSelect label="Vänster skala" value={yMaxLeft} onChange={setYMaxLeft} />
            <ScaleSelect label="Höger skala" value={yMaxRight} onChange={setYMaxRight} />
          </div>
        )}
      />
      <section className="panel">
        <div className="section-head">
          <h2>Datalogger</h2>
          <div className="actions">
            <button type="button" onClick={() => setFull((value) => !value)}>
              {full ? "Färre kolumner" : "Alla kolumner"}
            </button>
            <button type="button" className="primary" onClick={download} disabled={rows.length === 0}>
              Hämta CSV
            </button>
          </div>
        </div>
        <p className="muted">{rows.length} rader. Samma kolumner som MELACS.CSV på SD-kortet. Tabellen visar de senaste 80.</p>
        {shown.length === 0 ? (
          <p>Ingen loggrad ännu.</p>
        ) : (
          <div className="table-wrap">
            <table>
              <thead>
                <tr>
                  {columns.map((key) => (
                    <th key={key}>{key}</th>
                  ))}
                </tr>
              </thead>
              <tbody>
                {shown.map((row) => (
                  <tr key={row.TimeStamp}>
                    {columns.map((key) => (
                      <td key={key}>{row[key]}</td>
                    ))}
                  </tr>
                ))}
              </tbody>
            </table>
          </div>
        )}
      </section>
    </div>
  );
}
