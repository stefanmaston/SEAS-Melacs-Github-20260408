import { useState } from "react";

export function Login({ onSuccess }) {
  const [name, setName] = useState("");
  const [password, setPassword] = useState("");
  const [error, setError] = useState("");
  const [busy, setBusy] = useState(false);

  const submit = async (event) => {
    event.preventDefault();
    setBusy(true);
    setError("");
    try {
      const res = await fetch("/api/session", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ name, password }),
      });
      const data = await res.json();
      if (!res.ok) {
        setError(data.error || "Fel användarnamn eller lösenord.");
        return;
      }
      onSuccess(data);
    } catch {
      setError("Inloggningen svarade inte.");
    } finally {
      setBusy(false);
    }
  };

  return (
    <main className="shell">
      <form className="login-card" onSubmit={submit}>
        <h2>Logga in</h2>
        <label>
          Användarnamn
          <input
            name="username"
            autoComplete="username"
            value={name}
            onChange={(event) => setName(event.target.value)}
            required
          />
        </label>
        <label>
          Lösenord
          <input
            name="password"
            type="password"
            autoComplete="current-password"
            value={password}
            onChange={(event) => setPassword(event.target.value)}
            required
          />
        </label>
        {error ? (
          <p className="banner bad" role="alert">
            {error}
          </p>
        ) : null}
        <button type="submit" className="primary" disabled={busy}>
          Logga in
        </button>
      </form>
    </main>
  );
}
