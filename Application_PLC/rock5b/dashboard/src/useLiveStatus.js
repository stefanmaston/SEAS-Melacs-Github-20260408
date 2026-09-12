import { useEffect, useState } from "react";

const fallback = {
  source: "sim",
  plc_loaded: true,
  plc_running: true,
  logger_ok: true,
  sd_ok: true,
  heater_temp: 24,
  engine_temp: 22,
  board_temp: 26,
  engine_pressure: 12,
  error_code: 0,
};

export function useLiveStatus() {
  const [status, setStatus] = useState(fallback);

  useEffect(() => {
    let cancelled = false;

    const pull = async () => {
      try {
        const res = await fetch("/api/live", { cache: "no-store" });
        if (!res.ok) {
          throw new Error("no live api");
        }
        const data = await res.json();
        if (!cancelled) {
          setStatus({ ...fallback, ...data, source: "modbus" });
        }
      } catch {
        if (!cancelled) {
          setStatus((prev) => ({
            ...prev,
            source: "sim",
            heater_temp: 20 + ((prev.heater_temp + 1) % 8),
          }));
        }
      }
    };

    pull();
    const id = setInterval(pull, 2000);
    return () => {
      cancelled = true;
      clearInterval(id);
    };
  }, []);

  return status;
}
