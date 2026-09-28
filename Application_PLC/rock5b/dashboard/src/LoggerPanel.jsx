import { useEffect, useState } from "react";
import { LOG_KEYS, LOG_PREVIEW } from "../shared/columns.js";
import { alarmText } from "./format.js";
import { TrendChart } from "./TrendChart.jsx";

const TEMP_SERIES = [
  { key: "T_BOARD", label: "T_BOARD °C", color: "#03a9f4" },
  { key: "T1", label: "T1", color: "#ff9800", axis: "right" },
  { key: "T2", label: "T2", color: "#4caf50", axis: "right" },
];

const WINDOWS = [
  { minutes: 1, label: "1 minut" },
  { minutes: 5, label: "5 minuter" },
  { minutes: 10, label: "10 minuter" },
  { minutes: 30, label: "30 minuter" },
  { minutes: 60, label: "1 timme" },
];

function rowsInWindow(rows, minutes) {
  if (rows.length === 0) return [];
  const latest = Date.parse(String(rows[rows.length - 1].TimeStamp).replace(" ", "T"));
  if (!Number.isFinite(latest)) return rows;
  const start = latest - minutes * 60 * 1000;
  return rows.filter((row) => {
    const stamp = Date.parse(String(row.TimeStamp).replace(" ", "T"));
    return Number.isFinite(stamp) && stamp >= start && stamp <= latest + 5000;
  });
}

function csvEscape(value) {
  const text = String(value ?? "");
  if (/[",\n]/.test(text)) return `"${text.replaceAll('"', '""')}"`;
  return text;
}

export function LoggerPanel({ rows }) {
  const [full, setFull] = useState(false);
  const [minutes, setMinutes] = useState(10);
  const [sdRows, setSdRows] = useState([]);
  const [sdNote, setSdNote] = useState("Läser från SD-kortet.");
  const columns = full ? LOG_KEYS : LOG_PREVIEW;
  const shown = rows.slice(-80).reverse();
  const fromSd = sdRows.length >= 2;
  const chartRows = fromSd ? sdRows : rowsInWindow(rows, minutes);
  const chartNote = fromSd
    ? "T_BOARD är grader. T1 och T2 är råvärden, höger skala."
    : chartRows.length >= 2
      ? "Senaste avläsningarna i fönstret. Hela fönstret från SD-kortet kommer när kortet har det nya programmet."
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
          setSdNote(alarmText(data.error) || "SD-loggen kunde inte läsas");
          return;
        }
        setSdRows(data.rows || []);
        setSdNote(data.rows && data.rows.length > 0 ? "" : "Inga loggrader i det här fönstret på SD-kortet.");
      } catch {
        if (!stop) setSdNote("SD-loggen kunde inte läsas");
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

  const download = () => {
    const lines = [
      LOG_KEYS.join(","),
      ...rows.map((row) => LOG_KEYS.map((key) => csvEscape(row[key])).join(",")),
    ];
    const blob = new Blob([lines.join("\n")], { type: "text/csv;charset=utf-8" });
    const url = URL.createObjectURL(blob);
    const link = document.createElement("a");
    link.href = url;
    link.download = "MELACS.CSV";
    link.click();
    URL.revokeObjectURL(url);
  };

  return (
    <div className="stack">
      <TrendChart
        title="Loggade temperaturer"
        note={chartNote}
        rows={chartRows}
        series={TEMP_SERIES}
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
