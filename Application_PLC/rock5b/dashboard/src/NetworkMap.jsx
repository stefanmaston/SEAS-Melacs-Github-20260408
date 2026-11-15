import { useEffect, useState } from "react";

const KINDS = ["Rock 5B", "Melacs7", "Challenger", "Annan"];

const CHAIN = ["seas-central", "seas-edge", "melacs7", "challenger"];

function liveBoard(board, plant) {
  if (board.id === "seas-central") {
    const local = typeof window !== "undefined" && board.host === window.location.hostname;
    return { ...board, link: local || Boolean(board.link) };
  }
  if (board.id === "seas-edge") return { ...board, link: true };
  if (board.id === "melacs7") return { ...board, link: Boolean(plant?.link) };
  if (board.id === "challenger") {
    const live = (plant?.systems || []).find((item) => item.id === "challenger");
    return { ...board, link: Boolean(live?.link) };
  }
  return board;
}

function ordered(boards) {
  const rank = (board) => {
    const index = CHAIN.indexOf(board.id);
    return index === -1 ? CHAIN.length : index;
  };
  return [...boards].sort((a, b) => rank(a) - rank(b));
}

function Node({ board, x, y, wide }) {
  const w = wide ? 320 : 210;
  const h = 74;
  return (
    <g transform={`translate(${x - w / 2}, ${y - h / 2})`}>
      <rect width={w} height={h} rx="12" className={board.link ? "net-node on" : "net-node"} />
      <circle cx="18" cy="22" r="5" className={board.link ? "net-dot on" : "net-dot"} />
      <text x="30" y="26" className="net-title">{board.name}</text>
      <text x="16" y="48" className="net-sub">{board.kind}{board.detail ? ` · ${board.detail}` : ""}</text>
      <text x="16" y="64" className="net-sub">{board.host}{board.port ? `:${board.port}` : ""}</text>
    </g>
  );
}

function Schema({ boards }) {
  const chain = ordered(boards);
  if (!chain.length) return null;
  const cx = 450;
  const boxH = 74;
  const gap = 44;
  const pad = 24;
  const pitch = boxH + gap;
  const height = pad * 2 + chain.length * boxH + Math.max(0, chain.length - 1) * gap;
  const yOf = (index) => pad + boxH / 2 + index * pitch;
  return (
    <svg className="netmap" viewBox={`0 0 900 ${height}`} role="img" aria-label="Systemschema">
      {chain.slice(0, -1).map((board, index) => {
        const lower = chain[index + 1];
        return (
          <line
            key={`${board.id}-${lower.id}`}
            x1={cx}
            y1={yOf(index) + boxH / 2}
            x2={cx}
            y2={yOf(index + 1) - boxH / 2}
            className={board.link && lower.link ? "net-line on" : "net-line"}
          />
        );
      })}
      {chain.map((board, index) => (
        <Node key={board.id} board={board} x={cx} y={yOf(index)} wide={board.id === "seas-central"} />
      ))}
    </svg>
  );
}

function BoardEditor({ board, onSave, onRemove }) {
  const [name, setName] = useState(board.name);
  const [host, setHost] = useState(board.host);
  const [port, setPort] = useState(String(board.port || 502));
  const [detail, setDetail] = useState(board.detail || "");
  const [error, setError] = useState("");

  const save = async () => {
    setError("");
    const message = await onSave(board.id, { name, host, port: Number(port), detail });
    setError(message || "");
  };

  return (
    <div className="board-edit">
      <label>
        Namn
        <input value={name} onChange={(event) => setName(event.target.value)} />
      </label>
      <label>
        Adress
        <input value={host} onChange={(event) => setHost(event.target.value)} />
      </label>
      <label>
        Port
        <input value={port} inputMode="numeric" onChange={(event) => setPort(event.target.value)} />
      </label>
      <label>
        Text
        <input value={detail} onChange={(event) => setDetail(event.target.value)} />
      </label>
      <div className="actions">
        <button type="button" className="primary" onClick={save}>Spara</button>
        {board.builtin ? null : (
          <button type="button" className="danger" onClick={() => onRemove(board.id)}>Ta bort</button>
        )}
      </div>
      {error ? <p className="banner bad">{error}</p> : null}
    </div>
  );
}

export function NetworkMap({ plant, canControl }) {
  const [boards, setBoards] = useState([]);
  const [editing, setEditing] = useState(false);
  const [draft, setDraft] = useState({ name: "", kind: "Challenger", host: "", port: "502", detail: "" });
  const [error, setError] = useState("");

  const pull = async () => {
    const res = await fetch("/api/boards", { cache: "no-store" });
    if (!res.ok) return;
    const data = await res.json();
    setBoards(data.boards || []);
  };

  useEffect(() => {
    let stop = false;
    const run = async () => {
      const res = await fetch("/api/boards", { cache: "no-store" });
      if (!res.ok || stop) return;
      const data = await res.json();
      if (!stop) setBoards(data.boards || []);
    };
    run();
    const id = setInterval(run, 3000);
    return () => {
      stop = true;
      clearInterval(id);
    };
  }, []);

  const shown = boards.map((board) => liveBoard(board, plant));

  const saveBoard = async (id, body) => {
    const res = await fetch(`/api/boards/${encodeURIComponent(id)}`, {
      method: "PATCH",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(body),
    });
    const data = await res.json();
    if (!res.ok) return data.error || "Kunde inte spara.";
    await pull();
    return "";
  };

  const removeBoard = async (id) => {
    const res = await fetch(`/api/boards/${encodeURIComponent(id)}`, { method: "DELETE" });
    const data = await res.json();
    if (!res.ok) {
      setError(data.error || "Kunde inte ta bort.");
      return;
    }
    setError("");
    await pull();
  };

  const addBoard = async (event) => {
    event.preventDefault();
    setError("");
    const res = await fetch("/api/boards", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ ...draft, port: Number(draft.port) }),
    });
    const data = await res.json();
    if (!res.ok) {
      setError(data.error || "Kunde inte lägga till kortet.");
      return;
    }
    setDraft({ name: "", kind: "Challenger", host: "", port: "502", detail: "" });
    await pull();
  };

  return (
    <div className="stack">
      <div className="section-head">
        <h2>Systemschema</h2>
        {canControl ? (
          <button type="button" className={editing ? "primary" : ""} onClick={() => setEditing(!editing)}>
            {editing ? "Klar" : "Redigera"}
          </button>
        ) : null}
      </div>
      <Schema boards={shown} />
      {editing ? (
        <section className="panel">
          <h3>Länka in kretskort</h3>
          <form className="board-add" onSubmit={addBoard}>
            <label>
              Namn
              <input value={draft.name} onChange={(event) => setDraft({ ...draft, name: event.target.value })} />
            </label>
            <label>
              Typ
              <select value={draft.kind} onChange={(event) => setDraft({ ...draft, kind: event.target.value })}>
                {KINDS.map((kind) => <option key={kind}>{kind}</option>)}
              </select>
            </label>
            <label>
              Adress
              <input value={draft.host} onChange={(event) => setDraft({ ...draft, host: event.target.value })} placeholder="192.168.50.30" />
            </label>
            <label>
              Port
              <input value={draft.port} inputMode="numeric" onChange={(event) => setDraft({ ...draft, port: event.target.value })} />
            </label>
            <label>
              Text
              <input value={draft.detail} onChange={(event) => setDraft({ ...draft, detail: event.target.value })} />
            </label>
            <button type="submit" className="primary">Lägg till</button>
          </form>
          {error ? <p className="banner bad">{error}</p> : null}
          {shown.map((board) => (
            <BoardEditor key={board.id} board={board} onSave={saveBoard} onRemove={removeBoard} />
          ))}
        </section>
      ) : null}
    </div>
  );
}
