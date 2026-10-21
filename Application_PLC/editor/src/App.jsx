import { useEffect, useState } from "react";

function PouRow({ pou, onToggle }) {
  const id = `pou-${pou.path}`;
  return (
    <div className="row">
      <input
        id={id}
        type="checkbox"
        checked={pou.safetyRelated}
        onChange={(event) => onToggle(pou, event.target.checked)}
      />
      <label htmlFor={id}>
        <span className="name">{pou.name}</span>
        <span className="kind">{pou.kind}</span>
        <span className="path">{pou.path}</span>
      </label>
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

  async function toggle(pou, safetyRelated) {
    setError("");
    const response = await fetch("/api/pous", {
      method: "POST",
      headers: { "content-type": "application/json" },
      body: JSON.stringify({ path: pou.path, safetyRelated }),
    });
    if (!response.ok) {
      setError("Kunde inte spara märket.");
      return;
    }
    setPous(await response.json());
    setMessage(safetyRelated
      ? `${pou.name} är säkerhetsrelaterad och följer med nedladdningen.`
      : `${pou.name} är vanlig styrning.`);
  }

  async function compile() {
    setError("");
    setMessage("");
    const response = await fetch("/api/compile", { method: "POST" });
    const data = await response.json();
    if (!response.ok) {
      setError(data.error || "Kompileringen misslyckades.");
      return;
    }
    const marked = data.marked === 1 ? "1 märkt POU" : `${data.marked} märkta POU:er`;
    setMessage(`Skyddsbild ${data.bytes} byte. ${marked}.`);
  }

  return (
    <main>
      <h1>Melacs skyddsmärkning</h1>
      <p>
        Kryssrutan märker en POU som säkerhetsrelaterad. Märket sparas i POU-filen
        och i projektets lista, och följer med när projektet laddas till lådan.
        Märkta POU:er kompileras till skyddsbilden som PIC32 kör.
      </p>
      {error ? <p className="error">{error}</p> : null}
      {message ? <p className="ok">{message}</p> : null}
      <div className="list">
        {pous.map((pou) => (
          <PouRow key={pou.path} pou={pou} onToggle={toggle} />
        ))}
      </div>
      <button type="button" onClick={compile}>Skapa skyddsbild</button>
    </main>
  );
}
