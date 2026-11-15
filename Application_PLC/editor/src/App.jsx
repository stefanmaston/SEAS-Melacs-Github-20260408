import { useEffect, useState } from "react";

function PouRow({ pou, onToggle }) {
  const safetyId = `pou-safety-${pou.path}`;
  const localId = `pou-local-${pou.path}`;
  return (
    <div className="row">
      <label className="mark" htmlFor={safetyId}>
        <input
          id={safetyId}
          type="checkbox"
          checked={pou.safetyRelated}
          onChange={(event) => onToggle(pou, "safety", event.target.checked)}
        />
        skydd
      </label>
      <label className="mark" htmlFor={localId}>
        <input
          id={localId}
          type="checkbox"
          checked={pou.localRelated}
          onChange={(event) => onToggle(pou, "local", event.target.checked)}
        />
        lokal
      </label>
      <span className="name">{pou.name}</span>
      <span className="kind">{pou.kind}</span>
      <span className="path">{pou.path}</span>
    </div>
  );
}

export function App() {
  const [pous, setPous] = useState([]);
  const [message, setMessage] = useState("");
  const [error, setError] = useState("");

  useEffect(() => {
    let gone = false;
    fetch("/api/pous")
      .then((response) => response.json())
      .then((data) => {
        if (!gone) {
          setPous(data);
        }
      })
      .catch(() => {
        if (!gone) {
          setError("Kunde inte läsa projektet.");
        }
      });
    return () => {
      gone = true;
    };
  }, []);

  async function toggle(pou, kind, value) {
    setError("");
    const response = await fetch("/api/pous", {
      method: "POST",
      headers: { "content-type": "application/json" },
      body: JSON.stringify({
        path: pou.path,
        safetyRelated: kind === "safety" ? value : undefined,
        localRelated: kind === "local" ? value : undefined,
      }),
    });
    if (!response.ok) {
      setError("Kunde inte spara märket.");
      return;
    }
    setPous(await response.json());
    if (kind === "safety") {
      setMessage(value
        ? `${pou.name} är säkerhetsrelaterad och följer med skyddsbilden.`
        : `${pou.name} är inte skydd.`);
      return;
    }
    setMessage(value
      ? `${pou.name} är lokal styrning och kompileras till MELACS.LOC.`
      : `${pou.name} är inte lokal styrning.`);
  }

  async function compile(kind) {
    setError("");
    setMessage("");
    const path = kind === "local" ? "/api/compile-local" : "/api/compile";
    const response = await fetch(path, { method: "POST" });
    const data = await response.json();
    if (!response.ok) {
      setError(data.error || "Kompileringen misslyckades.");
      return;
    }
    if (kind === "local") {
      const marked = data.marked === 1 ? "1 lokal POU" : `${data.marked} lokala POU:er`;
      setMessage(`Lokal bild ${data.bytes} byte. ${marked}. Spara som MELACS.LOC på SD-kortet.`);
      return;
    }
    const marked = data.marked === 1 ? "1 märkt POU" : `${data.marked} märkta POU:er`;
    setMessage(`Skyddsbild ${data.bytes} byte. ${marked}.`);
  }

  return (
    <main>
      <h1>Melacs POU-märkning</h1>
      <p>
        Skydd kompileras till skyddsbilden som bara kan spärra utgångar.
        Lokal styrning kompileras till MELACS.LOC och körs i PIC32 oberoende
        av OpenPLC Runtime. En POU kan inte vara båda.
      </p>
      {error ? <p className="error">{error}</p> : null}
      {message ? <p className="ok">{message}</p> : null}
      <div className="list">
        {pous.map((pou) => (
          <PouRow key={pou.path} pou={pou} onToggle={toggle} />
        ))}
      </div>
      <div className="actions">
        <button type="button" onClick={() => compile("safety")}>Skapa skyddsbild</button>
        <button type="button" onClick={() => compile("local")}>Skapa lokal bild</button>
      </div>
    </main>
  );
}
