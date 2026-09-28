import { useEffect, useState } from "react";
import { Controls } from "./Controls.jsx";
import { alarmText, errorText, formatRtc } from "./format.js";
import { LoggerPanel } from "./LoggerPanel.jsx";
import { Schematic } from "./Schematic.jsx";
import { usePlant } from "./usePlant.js";

const VIEWS = [
  { id: "overview", label: "Översikt" },
  { id: "controls", label: "Reglage" },
  { id: "logger", label: "Logger" },
];

function readTheme() {
  try {
    return localStorage.getItem("melacs-theme") === "dark" ? "dark" : "light";
  } catch {
    return "light";
  }
}

function ThemeIcon({ theme }) {
  if (theme === "dark") {
    return (
      <svg className="theme-icon" viewBox="0 0 24 24" aria-hidden="true">
        <circle cx="12" cy="12" r="4" fill="currentColor" />
        <path
          fill="none"
          stroke="currentColor"
          strokeWidth="1.8"
          strokeLinecap="round"
          d="M12 2.5v2.2M12 19.3v2.2M4.8 4.8l1.6 1.6M17.6 17.6l1.6 1.6M2.5 12h2.2M19.3 12h2.2M4.8 19.2l1.6-1.6M17.6 6.4l1.6-1.6"
        />
      </svg>
    );
  }
  return (
    <svg className="theme-icon" viewBox="0 0 24 24" aria-hidden="true">
      <path fill="currentColor" d="M15.5 3.2a8.2 8.2 0 1 0 5.3 12.6A7 7 0 0 1 15.5 3.2z" />
    </svg>
  );
}

function Mark() {
  return (
    <svg className="mark" viewBox="0 0 48 48" aria-hidden="true">
      <rect x="2" y="2" width="44" height="44" rx="8" />
      <path d="M10 32 V16 H18 L24 26 L30 16 H38 V32 H32 V22 L26 32 H22 L16 22 V32 Z" />
    </svg>
  );
}

function Status({ plant }) {
  const inp = plant.inputs;
  const items = [
    ["SD", inp.sd_ok],
    ["Logger", inp.logger_ok],
    ["Länk", plant.link],
    ["Master", inp.plc_loaded],
    ["Utgångar aktiva", inp.plc_running],
  ];
  return (
    <ul className="status">
      {items.map(([label, on]) => (
        <li key={label} className={on ? "on" : ""}>
          {label}
        </li>
      ))}
    </ul>
  );
}

function Overview({ plant }) {
  const inp = plant.inputs;
  const tiles = [
    ["T_BOARD", `${inp.t_board} °C`],
    ["T1", inp.t1],
    ["T2", inp.t2],
    ["P", inp.p],
    ["VALUE", inp.value],
    ["Fel", errorText(inp.error_code)],
  ];
  const safe = !plant.inputs.plc_running;
  return (
    <div className="stack">
      {safe ? (
        <p className="banner">
          Fysiska utgångar ligger i safe. De följer reglagen först när en master har skrivit och safe_mode är 0.
        </p>
      ) : null}
      <Status plant={plant} />
      <Schematic plant={plant} />
      <section className="tiles">
        {tiles.map(([label, value]) => (
          <article key={label}>
            <h3>{label}</h3>
            <p>{value}</p>
          </article>
        ))}
      </section>
    </div>
  );
}

export function App() {
  const { plant, log, error, notice, busy, command } = usePlant();
  const [view, setView] = useState("overview");
  const [theme, setTheme] = useState(readTheme);

  useEffect(() => {
    document.documentElement.dataset.theme = theme;
    try {
      localStorage.setItem("melacs-theme", theme);
    } catch {
      /* Sidan fungerar även om lagringen är avstängd. */
    }
  }, [theme]);

  return (
    <div className="app">
      <header className="topbar">
        <div className="brand">
          <Mark />
          <div>
            <h1>Melacs SEAS PLC</h1>
            <p>{plant ? (plant.source === "modbus" ? `Länk aktiv · ${plant.host}` : `Simulerad data · ${plant.host}`) : "söker länk"}</p>
          </div>
        </div>
        <div className="top-tools">
          <p className="clock">{plant ? formatRtc(plant.rtc) : "—"}</p>
          <button
            type="button"
            className="theme-toggle"
            aria-pressed={theme === "dark"}
            aria-label={theme === "dark" ? "Byt till ljust läge" : "Byt till mörkt läge"}
            onClick={() => setTheme(theme === "dark" ? "light" : "dark")}
          >
            <ThemeIcon theme={theme} />
            <span>{theme === "dark" ? "Ljust" : "Mörkt"}</span>
          </button>
        </div>
      </header>
      <main className="shell">
        <div className="viewbar">
          <nav className="nav" aria-label="Vyer">
            {VIEWS.map((item) => (
              <button
                key={item.id}
                type="button"
                className={view === item.id ? "active" : ""}
                aria-current={view === item.id ? "page" : undefined}
                onClick={() => setView(item.id)}
              >
                {item.label}
              </button>
            ))}
          </nav>
          <p
            className={error ? "banner bad" : notice ? "banner good" : "banner idle"}
            role={error ? "alert" : "status"}
            title={error || notice || undefined}
          >
            {error ? alarmText(error) : notice}
          </p>
        </div>
        {!plant ? <p className="panel">Hämtar kortets värden.</p> : null}
        {plant && view === "overview" ? <Overview plant={plant} /> : null}
        {plant && view === "controls" ? <Controls plant={plant} busy={busy} onCommand={command} /> : null}
        {plant && view === "logger" ? <LoggerPanel rows={log} /> : null}
      </main>
    </div>
  );
}
