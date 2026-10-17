import { useEffect, useState } from "react";

const ROLES = [
  ["viewer", "Läsare"],
  ["operator", "Operatör"],
  ["admin", "Administratör"],
];

function roleLabel(role) {
  if (role === "service") return "Service";
  const found = ROLES.find((item) => item[0] === role);
  return found ? found[1] : role;
}

async function readJson(res) {
  const data = await res.json();
  if (!res.ok) throw new Error(data.error || "Begäran misslyckades");
  return data;
}

export function Access({ session, onSession }) {
  const [users, setUsers] = useState([]);
  const [openplc, setOpenplc] = useState(null);
  const [name, setName] = useState("");
  const [password, setPassword] = useState("");
  const [role, setRole] = useState("viewer");
  const [code, setCode] = useState("");
  const [error, setError] = useState("");
  const [notice, setNotice] = useState("");
  const [busy, setBusy] = useState(false);

  const load = async () => {
    const [userData, plcData] = await Promise.all([
      fetch("/api/users", { cache: "no-store" }).then(readJson),
      fetch("/api/openplc", { cache: "no-store" }).then(readJson),
    ]);
    setUsers(userData.users || []);
    setOpenplc(plcData);
  };

  useEffect(() => {
    let cancelled = false;
    load().catch((err) => {
      if (!cancelled) setError(err.message);
    });
    return () => {
      cancelled = true;
    };
  }, []);

  const addUser = async (event) => {
    event.preventDefault();
    setBusy(true);
    setError("");
    setNotice("");
    try {
      await fetch("/api/users", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ name, password, role }),
      }).then(readJson);
      setName("");
      setPassword("");
      setNotice("Användaren är tillagd.");
      await load();
    } catch (err) {
      setError(err.message);
    } finally {
      setBusy(false);
    }
  };

  const removeUser = async (userName) => {
    setBusy(true);
    setError("");
    setNotice("");
    try {
      await fetch(`/api/users?name=${encodeURIComponent(userName)}`, { method: "DELETE" }).then(readJson);
      setNotice("Användaren är borttagen.");
      await load();
    } catch (err) {
      setError(err.message);
    } finally {
      setBusy(false);
    }
  };

  const activate = async (event) => {
    event.preventDefault();
    setBusy(true);
    setError("");
    setNotice("");
    try {
      const data = await fetch("/api/license", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ code }),
      }).then(readJson);
      setCode("");
      setNotice("Licensen är aktiverad.");
      onSession({ ...session, license: data.license, plantId: data.plantId });
      await load();
    } catch (err) {
      setError(err.message);
    } finally {
      setBusy(false);
    }
  };

  const connect = async () => {
    setBusy(true);
    setError("");
    setNotice("");
    try {
      const data = await fetch("/api/openplc", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: "{}",
      }).then(readJson);
      setOpenplc(data);
      setNotice(data.running ? "OpenPLC är ansluten." : "OpenPLC startade inte.");
    } catch (err) {
      setError(err.message);
    } finally {
      setBusy(false);
    }
  };

  return (
    <div className="stack access">
      {error ? (
        <p className="banner bad" role="alert">
          {error}
        </p>
      ) : null}
      {notice ? <p className="banner good">{notice}</p> : null}
      <section className="access-card">
        <h2>Användare</h2>
        <p className="muted">Inbjudna användare loggar in med webbläsaren. Servicekontot ligger kvar vid sidan av dem.</p>
        <ul className="user-list">
          {users.map((user) => (
            <li key={user.name}>
              <span>
                {user.name}
                <small>{roleLabel(user.role)}</small>
              </span>
              {user.role === "service" || user.name === "root" ? (
                <small>kan inte tas bort</small>
              ) : (
                <button type="button" className="danger" disabled={busy} onClick={() => removeUser(user.name)}>
                  Ta bort
                </button>
              )}
            </li>
          ))}
        </ul>
        <form className="access-form" onSubmit={addUser}>
          <label>
            Användarnamn
            <input value={name} onChange={(event) => setName(event.target.value)} autoComplete="off" required />
          </label>
          <label>
            Lösenord
            <input
              type="password"
              value={password}
              onChange={(event) => setPassword(event.target.value)}
              autoComplete="new-password"
              required
            />
          </label>
          <label>
            Roll
            <select value={role} onChange={(event) => setRole(event.target.value)}>
              {ROLES.map(([value, label]) => (
                <option key={value} value={value}>
                  {label}
                </option>
              ))}
            </select>
          </label>
          <button type="submit" className="primary" disabled={busy}>
            Lägg till
          </button>
        </form>
      </section>
      <section className="access-card">
        <h2>OpenPLC</h2>
        <p className="muted">Anläggnings-id {session.plantId}</p>
        {session.license ? (
          <p className="banner good">Licensen är aktiv.</p>
        ) : (
          <form className="access-form" onSubmit={activate}>
            <label>
              Licenskod
              <input value={code} onChange={(event) => setCode(event.target.value)} autoComplete="off" required />
            </label>
            <button type="submit" className="primary" disabled={busy}>
              Aktivera licens
            </button>
          </form>
        )}
        <p>{openplc && openplc.running ? "OpenPLC kör." : "OpenPLC är inte ansluten."}</p>
        <button type="button" className="primary" disabled={busy || !session.license} onClick={connect}>
          Anslut OpenPLC
        </button>
      </section>
    </div>
  );
}
