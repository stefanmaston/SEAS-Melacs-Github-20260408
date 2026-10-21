import { useEffect, useState } from "react";
import { Access } from "./Access.jsx";
import { Controls } from "./Controls.jsx";
import { alarmText, downloadMelacsCsv, errorText, formatRtc } from "./format.js";
import { LoggerPanel } from "./LoggerPanel.jsx";
import { Login } from "./Login.jsx";
import { Schematic } from "./Schematic.jsx";
import { usePlant } from "./usePlant.js";

const VIEWS = [
  { id: "overview", label: "Översikt" },
  { id: "fuxa", label: "FUXA" },
  { id: "controls", label: "Reglage" },
  { id: "logger", label: "Logger" },
  { id: "cockpit", label: "Cockpit" },
  { id: "access", label: "PLC editor" },
];

function allowedViews(session) {
  const admin = session.role === "admin" || session.role === "service";
  return VIEWS.filter((item) => {
    if (item.id === "cockpit" || item.id === "access") return admin;
    return true;
  });
}

const emptyPlant = {
  host: "—",
  link: false,
  inputs: {
    ad: [null, null, null, null, null, null, null, null],
    dio: [false, false, false, false],
    sd_ok: false,
    t_board: "—",
    t1: "—",
    t2: "—",
  },
  applied: {
    dio: [false, false, false, false],
    ao: [0, 0, 0],
    sip: [false, false, false, false, false, false, false, false],
    h1_dis: true,
    h1_ali: false,
    h1_bli: false,
    h1_ahi: 0,
    h1_bhi: 0,
    h2_dis: true,
    h2_ali: false,
    h2_bli: false,
    h2_ahi: 0,
    h2_bhi: 0,
  },
  holding: { safe_mode: 1, log_period_s: "" },
  commanded: {
    dio: [false, false, false, false],
    ao: [0, 0, 0],
    sip: [false, false, false, false, false, false, false, false],
    h1_dis: true,
    h1_ali: false,
    h1_bli: false,
    h1_ahi: 0,
    h1_bhi: 0,
    h2_dis: true,
    h2_ali: false,
    h2_bli: false,
    h2_ahi: 0,
    h2_bhi: 0,
    note: 0,
  },
};

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
  const live = Boolean(plant.source);
  const tiles = [
    ["T_BOARD", live ? `${inp.t_board} °C` : "—"],
    ["T1", live ? inp.t1 : "—"],
    ["T2", live ? inp.t2 : "—"],
    ["P", live ? (inp.p ?? "—") : "—"],
    ["VALUE", live ? (inp.value ?? "—") : "—"],
    ["Fel", live ? errorText(inp.error_code) : "—"],
  ];
  const safe = live && !plant.inputs.plc_running;
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

export function ControlsView({ plant, busy, onCommand, canControl }) {
  return (
    <div className="workbench">
      <div className="controls-col">
        {canControl ? null : <p className="banner">Du kan läsa anläggningen. Styrning kräver operatör.</p>}
        <div className={canControl ? "controls-lock" : "controls-lock locked"}>
          <Controls plant={plant} busy={busy} onCommand={onCommand} />
        </div>
      </div>
      <figure className="board-photo">
        <img src="/melacs7.jpg" alt="Melacs 7-kortet" />
      </figure>
    </div>
  );
}

function readView(session) {
  const views = allowedViews(session);
  try {
    const match = document.cookie.match(/(?:^|; )melacs-view=([^;]*)/);
    const saved = match ? decodeURIComponent(match[1]) : "";
    if (views.some((item) => item.id === saved)) return saved;
  } catch {
    /* Sidan fungerar även om lagringen är avstängd. */
  }
  return "overview";
}

function keepCockpit(frame) {
  try {
    const path = frame.contentWindow.location.pathname || "/";
    if (path !== "/console" && !path.startsWith("/console/")) frame.contentWindow.location.replace("/console/");
  } catch {
    /* En sida på en annan adress går inte att styra. */
  }
}

function CockpitFrame() {
  return (
    <iframe
      className="cockpit-frame"
      title="Cockpit"
      src="/console/"
      onLoad={(event) => keepCockpit(event.currentTarget)}
    />
  );
}

function keepFuxa(frame) {
  try {
    const path = frame.contentWindow.location.pathname || "/";
    if (path !== "/fuxa" && !path.startsWith("/fuxa/")) frame.contentWindow.location.replace("/fuxa/");
  } catch {
    /* En sida på en annan adress går inte att styra. */
  }
}

function FuxaFrame() {
  return (
    <iframe
      className="cockpit-frame"
      title="FUXA"
      src="/fuxa/"
      onLoad={(event) => keepFuxa(event.currentTarget)}
    />
  );
}

function PlantShell({ session, onSession, onLogout, theme, onTheme }) {
  const { plant, log, error, notice, busy, command } = usePlant(onLogout);
  const views = allowedViews(session);
  const [view, setView] = useState(() => readView(session));
  const canControl = session.role === "operator" || session.role === "admin" || session.role === "service";

  useEffect(() => {
    try {
      document.cookie = `melacs-view=${encodeURIComponent(view)}; Path=/; SameSite=Lax; Max-Age=86400`;
    } catch {
      /* Sidan fungerar även om lagringen är avstängd. */
    }
  }, [view]);

  return (
    <>
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
          <p className="who">{session.name}</p>
          <button
            type="button"
            className="theme-toggle"
            aria-pressed={theme === "dark"}
            aria-label={theme === "dark" ? "Byt till ljust läge" : "Byt till mörkt läge"}
            onClick={onTheme}
          >
            <ThemeIcon theme={theme} />
            <span>{theme === "dark" ? "Ljust" : "Mörkt"}</span>
          </button>
          <button type="button" className="theme-toggle" onClick={onLogout}>
            Logga ut
          </button>
        </div>
      </header>
      <main className="shell">
        <div className="viewbar">
          <nav className="nav" aria-label="Vyer">
            {views.map((item) => (
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
          <div className="view-side">
            <p
              className={error ? "banner bad" : notice ? "banner good" : "banner idle"}
              role={error ? "alert" : "status"}
              title={error || notice || undefined}
            >
              {error ? alarmText(error) : notice}
            </p>
            <button
              type="button"
              className="primary"
              onClick={() => downloadMelacsCsv(log)}
              disabled={log.length === 0}
            >
              Ladda ned datafil
            </button>
          </div>
        </div>
        {view === "overview" ? <Overview plant={plant || emptyPlant} /> : null}
        {view === "fuxa" ? <FuxaFrame /> : null}
        {view === "controls" ? (
          <ControlsView plant={plant || emptyPlant} busy={busy} onCommand={command} canControl={canControl} />
        ) : null}
        {view === "logger" ? <LoggerPanel rows={plant ? log : []} /> : null}
        {view === "cockpit" ? <CockpitFrame /> : null}
        {view === "access" ? <Access session={session} onSession={onSession} /> : null}
      </main>
    </>
  );
}

export function App() {
  const [session, setSession] = useState(undefined);
  const [theme, setTheme] = useState(readTheme);

  useEffect(() => {
    document.documentElement.dataset.theme = theme;
    try {
      localStorage.setItem("melacs-theme", theme);
    } catch {
      /* Sidan fungerar även om lagringen är avstängd. */
    }
  }, [theme]);

  useEffect(() => {
    let cancelled = false;
    fetch("/api/session", { cache: "no-store" })
      .then(async (res) => {
        if (!res.ok) return null;
        return res.json();
      })
      .then((data) => {
        if (!cancelled) setSession(data);
      })
      .catch(() => {
        if (!cancelled) setSession(null);
      });
    return () => {
      cancelled = true;
    };
  }, []);

  const logout = async () => {
    try {
      await fetch("/api/session", { method: "DELETE" });
    } catch {
      /* Utloggningen rensar kontot även om anropet inte når fram. */
    }
    setSession(null);
  };

  return (
    <div className="app">
      {session ? (
        <PlantShell
          session={session}
          onSession={setSession}
          onLogout={logout}
          theme={theme}
          onTheme={() => setTheme(theme === "dark" ? "light" : "dark")}
        />
      ) : (
        <>
          <header className="topbar">
            <div className="brand">
              <Mark />
              <div>
                <h1>Melacs SEAS PLC</h1>
                <p>lokal anläggning</p>
              </div>
            </div>
            <div className="top-tools">
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
          {session === undefined ? null : <Login onSuccess={setSession} />}
        </>
      )}
    </div>
  );
}
