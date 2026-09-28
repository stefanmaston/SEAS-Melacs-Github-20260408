import { useEffect, useState } from "react";
import { WEEKDAYS } from "../shared/columns.js";
import { dateValue, fieldsFromRtc, timeValue } from "./format.js";

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

function ClockForm({ rtc, busy, onSet }) {
  const [fields, setFields] = useState(null);
  const [localError, setLocalError] = useState("");

  useEffect(() => {
    if (rtc && fields === null) {
      setFields(fieldsFromRtc(rtc));
    }
  }, [rtc, fields]);

  if (!fields) return null;

  const applyDate = (value) => {
    const [year, month, day] = value.split("-").map(Number);
    const weekday = new Date(year, month - 1, day).getDay();
    setFields((prev) => ({ ...prev, year, month, day, weekday }));
  };

  const applyTime = (value) => {
    const [hour, minute, second] = value.split(":").map(Number);
    setFields((prev) => ({
      ...prev,
      hour,
      minute,
      second: Number.isInteger(second) ? second : 0,
    }));
  };

  const submit = (event) => {
    event.preventDefault();
    setLocalError("");
    onSet(fields).then((ok) => {
      if (!ok) setLocalError("Klockan ställdes inte.");
    });
  };

  return (
    <form className="stack" onSubmit={submit}>
      <div className="split">
        <label>
          Datum
          <input type="date" value={dateValue(fields)} onChange={(event) => applyDate(event.target.value)} required />
        </label>
        <label>
          Tid
          <input type="time" step="1" value={timeValue(fields)} onChange={(event) => applyTime(event.target.value)} required />
        </label>
        <label>
          Veckodag
          <select
            value={fields.weekday}
            onChange={(event) => setFields((prev) => ({ ...prev, weekday: Number(event.target.value) }))}
          >
            {WEEKDAYS.map((name, index) => (
              <option key={name} value={index}>
                {index} {name}
              </option>
            ))}
          </select>
        </label>
      </div>
      <div className="actions">
        <button type="submit" className="primary" disabled={busy}>
          Ställ klockan
        </button>
        <button type="button" onClick={() => setFields(fieldsFromRtc(rtc))}>
          Hämta från kortet
        </button>
      </div>
      {localError ? <p className="warn-text">{localError}</p> : null}
      <p className="muted">Kortet tar år, datum, tid och veckodag i samma kommando. 0 är söndag.</p>
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
