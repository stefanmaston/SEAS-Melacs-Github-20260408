import { useCallback, useEffect, useState } from "react";

async function readJson(res) {
  const data = await res.json();
  if (!res.ok) {
    throw new Error(data.error || "Begäran misslyckades");
  }
  return data;
}

export function usePlant() {
  const [plant, setPlant] = useState(null);
  const [log, setLog] = useState([]);
  const [error, setError] = useState("");
  const [notice, setNotice] = useState("");
  const [busy, setBusy] = useState(false);

  useEffect(() => {
    let cancelled = false;

    const pullLive = async () => {
      try {
        const res = await fetch("/api/live", { cache: "no-store" });
        const data = await readJson(res);
        if (cancelled) return;
        setPlant(data);
        setError("");
      } catch (err) {
        if (!cancelled) setError(err.message);
      }
    };

    const pullLog = async () => {
      try {
        const res = await fetch("/api/log", { cache: "no-store" });
        const data = await readJson(res);
        if (!cancelled) setLog(data.rows || []);
      } catch (err) {
        if (!cancelled) setError(err.message);
      }
    };

    pullLive();
    pullLog();
    const liveId = setInterval(pullLive, 1000);
    const logId = setInterval(pullLog, 4000);
    return () => {
      cancelled = true;
      clearInterval(liveId);
      clearInterval(logId);
    };
  }, []);

  useEffect(() => {
    if (!notice) return undefined;
    const id = setTimeout(() => setNotice(""), 4000);
    return () => clearTimeout(id);
  }, [notice]);

  const command = useCallback(async (body, okText) => {
    setBusy(true);
    setError("");
    try {
      const res = await fetch("/api/command", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(body),
      });
      const data = await readJson(res);
      setPlant(data);
      if (okText) setNotice(okText);
      return true;
    } catch (err) {
      setError(err.message);
      return false;
    } finally {
      setBusy(false);
    }
  }, []);

  return { plant, log, error, notice, busy, command };
}
