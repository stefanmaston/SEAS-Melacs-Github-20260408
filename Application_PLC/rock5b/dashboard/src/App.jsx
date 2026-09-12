import { useLiveStatus } from "./useLiveStatus.js";

function Badge({ ok, label }) {
  return (
    <span className={ok ? "badge ok" : "badge off"}>
      {label}: {ok ? "ja" : "nej"}
    </span>
  );
}

export function App() {
  const s = useLiveStatus();

  return (
    <main className="page">
      <header>
        <h1>Melacs</h1>
        <p>Generell I/O + logger. PLC valfritt. Källa: {s.source}</p>
      </header>
      <section className="row">
        <Badge ok={s.logger_ok} label="Logger" />
        <Badge ok={s.sd_ok} label="SD" />
        <Badge ok={s.plc_loaded} label="PLC inlagt" />
        <Badge ok={s.plc_running} label="PLC kör" />
      </section>
      <section className="cards">
        <article>
          <h2>Process</h2>
          <p>Värmare {s.heater_temp} °C</p>
          <p>Motor {s.engine_temp} °C</p>
          <p>Tryck {s.engine_pressure}</p>
          <p>Kort {s.board_temp} °C</p>
        </article>
        <article>
          <h2>Fel</h2>
          <p>{s.error_code === 0 ? "Inga larm" : `Kod ${s.error_code}`}</p>
        </article>
      </section>
    </main>
  );
}
