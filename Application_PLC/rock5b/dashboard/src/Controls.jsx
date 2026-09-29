import { useEffect, useState } from "react";
import { fieldsFromRtc, formatRtc } from "./format.js";

function Toggle({ pressed, label, hint, onClick }) {
  return (
    <button type="button" className={pressed ? "toggle on" : "toggle"} aria-pressed={pressed} onClick={onClick}>
      <span>{label}</span>
      <b>{pressed ? "på" : "av"}</b>
      {hint ? <small>{hint}</small> : null}
    </button>
  );
}

function Level({ label, value, onCommit }) {
  const [draft, setDraft] = useState(value);

  useEffect(() => {
    setDraft(value);
  }, [value]);

  const commit = (next) => {
    const n = Number(next);
    if (Number.isInteger(n) && n >= 0 && n <= 65535 && n !== value) {
      onCommit(n);
    }
  };

  return (
    <label className="level">
      <span>
        {label}
        <b>{draft}</b>
      </span>
      <input
        type="range"
        min="0"
        max="65535"
        value={draft}
        onChange={(event) => setDraft(Number(event.target.value))}
        onPointerUp={(event) => commit(event.currentTarget.value)}
        onKeyUp={(event) => commit(event.currentTarget.value)}
        onBlur={(event) => commit(event.currentTarget.value)}
      />
    </label>
  );
}

function NoteField({ value, onCommit }) {
  const [draft, setDraft] = useState(String(value));

  useEffect(() => {
    setDraft(String(value));
  }, [value]);

  return (
    <label className="level">
      NOTE
      <input
        type="number"
        min="0"
        max="65535"
        value={draft}
        onChange={(event) => setDraft(event.target.value)}
        onBlur={() => {
          const n = Number(draft);
          if (Number.isInteger(n) && n >= 0 && n <= 65535 && n !== value) onCommit(n);
        }}
      />
    </label>
  );
}

const blankClock = {
  year: "", month: "", day: "", hour: "", minute: "", second: "",
};

const clockParts = [
  ["year", "År", "2000–2099"],
  ["month", "Månad", "1–12"],
  ["day", "Dag", "1–31"],
  ["hour", "Timme", "0–23"],
  ["minute", "Minut", "0–59"],
  ["second", "Sekund", "0–59"],
];

function wholeNumber(text) {
  if (!/^\d+$/.test(text)) return null;
  return Number(text);
}

function parseClock(fields) {
  if (clockParts.some(([key]) => fields[key] === "")) {
    return { error: "Fyll i år, månad, dag, timme, minut och sekund." };
  }
  const year = wholeNumber(fields.year);
  const month = wholeNumber(fields.month);
  const day = wholeNumber(fields.day);
  const hour = wholeNumber(fields.hour);
  const minute = wholeNumber(fields.minute);
  const second = wholeNumber(fields.second);
  if (year === null || year < 2000 || year > 2099) return { error: "År ska vara 2000–2099." };
  if (month === null || month < 1 || month > 12) return { error: "Månad ska vara 1–12." };
  const maxDay = new Date(year, month, 0).getDate();
  if (day === null || day < 1 || day > maxDay) return { error: "Dagen finns inte i den månaden." };
  if (hour === null || hour > 23) return { error: "Timme ska vara 0–23." };
  if (minute === null || minute > 59) return { error: "Minut ska vara 0–59." };
  if (second === null || second > 59) return { error: "Sekund ska vara 0–59." };
  const weekday = new Date(year, month - 1, day).getDay();
  return { value: { year, month, day, hour, minute, second, weekday } };
}

function ClockForm({ rtc, busy, onSet }) {
  const [fields, setFields] = useState(blankClock);
  const [pending, setPending] = useState(null);
  const [localError, setLocalError] = useState("");

  const edit = (key, value) => {
    setPending(null);
    setFields((prev) => ({ ...prev, [key]: value.replace(/\D/g, "") }));
  };

  const prepare = (event) => {
    event.preventDefault();
    const parsed = parseClock(fields);
    if (parsed.error) {
      setLocalError(parsed.error);
      setPending(null);
      return;
    }
    setLocalError("");
    setPending(parsed.value);
  };

  const write = () => {
    if (!pending) return;
    setLocalError("");
    onSet(pending).then((ok) => {
      if (!ok) setLocalError("Klockan skrevs inte.");
      else setPending(null);
    });
  };

  const fetchFromCard = () => {
    if (!rtc) return;
    const fetched = fieldsFromRtc(rtc);
    setFields({
      year: String(fetched.year),
      month: String(fetched.month),
      day: String(fetched.day),
      hour: String(fetched.hour),
      minute: String(fetched.minute),
      second: String(fetched.second),
    });
    setPending(null);
    setLocalError("");
  };

  return (
    <form className="stack" onSubmit={prepare}>
      <p className="muted">Kortet visar {formatRtc(rtc)}. Fälten skrivs inte förrän du bekräftar.</p>
      <div className="clock-fields">
        {clockParts.map(([key, label, hint]) => (
          <label key={key}>
            {label}
            <input
              inputMode="numeric"
              autoComplete="off"
              value={fields[key]}
              aria-label={label}
              placeholder={hint}
              onChange={(event) => edit(key, event.target.value)}
            />
          </label>
        ))}
      </div>
      <div className="actions">
        <button type="submit" disabled={busy}>
          Kontrollera
        </button>
        <button type="button" disabled={!rtc} onClick={fetchFromCard}>
          Hämta från kortet
        </button>
      </div>
      {pending ? (
        <div className="confirm">
          <p>Skriv {formatRtc(pending)} till kortet.</p>
          <button type="button" className="primary" disabled={busy} onClick={write}>
            Skriv till kortet
          </button>
          <button type="button" onClick={() => setPending(null)}>Avbryt</button>
        </div>
      ) : null}
      {localError ? <p className="warn-text">{localError}</p> : null}
      <p className="muted">Veckodagen räknas från datumet. 0 är söndag.</p>
    </form>
  );
}

function BridgeBox({ name, prefix, cmd, confirm, setConfirm, busy, onChange }) {
  const dis = cmd[`${prefix}_dis`];
  const asking = confirm === prefix;
  return (
    <fieldset>
      <legend>{name}</legend>
      <p className="muted">Spärr på håller bryggan av. Spärr av släpper på drivningen.</p>
      <div className="toggles">
        <Toggle
          pressed={dis}
          label="Spärr"
          hint={dis ? "bryggan av" : "drivning släppt"}
          onClick={() => {
            if (dis) {
              setConfirm(prefix);
              return;
            }
            setConfirm("");
            onChange({ [`${prefix}_dis`]: true });
          }}
        />
        <Toggle pressed={cmd[`${prefix}_ali`]} label="ALI" onClick={() => onChange({ [`${prefix}_ali`]: !cmd[`${prefix}_ali`] })} />
        <Toggle pressed={cmd[`${prefix}_bli`]} label="BLI" onClick={() => onChange({ [`${prefix}_bli`]: !cmd[`${prefix}_bli`] })} />
      </div>
      {asking ? (
        <div className="confirm">
          <p>Spärren tas bort och bryggan kan driva.</p>
          <button type="button" className="danger" disabled={busy} onClick={() => { onChange({ [`${prefix}_dis`]: false }); setConfirm(""); }}>
            Släpp spärren
          </button>
          <button type="button" onClick={() => setConfirm("")}>Avbryt</button>
        </div>
      ) : null}
      <Level label="AHI" value={cmd[`${prefix}_ahi`]} onCommit={(n) => onChange({ [`${prefix}_ahi`]: n })} />
      <Level label="BHI" value={cmd[`${prefix}_bhi`]} onCommit={(n) => onChange({ [`${prefix}_bhi`]: n })} />
    </fieldset>
  );
}

export function Controls({ plant, busy, onCommand }) {
  const cmd = plant.commanded;
  const holding = plant.holding;
  const [confirm, setConfirm] = useState("");
  const [period, setPeriod] = useState(String(holding.log_period_s));

  useEffect(() => {
    setPeriod(String(holding.log_period_s));
  }, [holding.log_period_s]);

  const outputs = (patch) => onCommand({ op: "outputs", ...patch }, "Utgången är skickad.");
  const hold = (patch, text) => onCommand({ op: "holding", safe_mode: holding.safe_mode, log_period_s: holding.log_period_s, ...patch }, text);

  return (
    <div className="stack">
      <section className="panel">
        <h2>Klocka och datum</h2>
        <ClockForm
          rtc={plant.rtc}
          busy={busy}
          onSet={(fields) => onCommand({ op: "clock", ...fields }, "Klockan är ställd.")}
        />
      </section>
      <section className="panel">
        <h2>Drift</h2>
        <div className="split">
          <label>
            Styrning
            <select
              value={holding.safe_mode === 0 ? "0" : "1"}
              onChange={(event) => hold({ safe_mode: Number(event.target.value) }, "Driftläge uppdaterat.")}
            >
              <option value="0">PLC får styra utgångarna</option>
              <option value="1">Säkra utgångar</option>
            </select>
          </label>
          <label>
            Loggperiod, sekunder
            <input
              type="number"
              min="0"
              max="65535"
              value={period}
              onChange={(event) => setPeriod(event.target.value)}
              onBlur={() => {
                if (period === "") return;
                const n = Number(period);
                if (Number.isInteger(n) && n >= 0 && n <= 65535 && n !== holding.log_period_s) {
                  hold({ log_period_s: n }, n === 0 ? "Period 0 blir 6 sekunder." : "Loggperioden är sparad.");
                }
              }}
            />
          </label>
        </div>
        <NoteField value={cmd.note} onCommit={(n) => outputs({ note: n })} />
      </section>
      <section className="panel">
        <h2>Digitala utgångar</h2>
        <div className="toggles">
          {cmd.dio.map((on, index) => (
            <Toggle
              key={index}
              pressed={on}
              label={`DIO${4 + index}`}
              onClick={() => {
                const dio = cmd.dio.slice();
                dio[index] = !on;
                outputs({ dio });
              }}
            />
          ))}
        </div>
      </section>
      <section className="panel">
        <h2>Analoga utgångar</h2>
        {cmd.ao.map((value, index) => (
          <Level
            key={index}
            label={`AO${index}`}
            value={value}
            onCommit={(n) => {
              const ao = cmd.ao.slice();
              ao[index] = n;
              outputs({ ao });
            }}
          />
        ))}
      </section>
      <section className="panel">
        <h2>SIP</h2>
        <p className="muted">SIP0 och SIP3 har inget bekräftat ben. SIP4 är JP7 och LED10, och tänds när den är hög.</p>
        <div className="toggles">
          {cmd.sip.map((on, index) => (
            <Toggle
              key={index}
              pressed={on}
              label={`SIP${index}`}
              hint={index === 0 || index === 3 ? "obekräftat ben" : ""}
              onClick={() => {
                const sip = cmd.sip.slice();
                sip[index] = !on;
                outputs({ sip });
              }}
            />
          ))}
        </div>
      </section>
      <BridgeBox name="H-brygga 1" prefix="h1" cmd={cmd} confirm={confirm} setConfirm={setConfirm} busy={busy} onChange={outputs} />
      <BridgeBox name="H-brygga 2" prefix="h2" cmd={cmd} confirm={confirm} setConfirm={setConfirm} busy={busy} onChange={outputs} />
    </div>
  );
}
