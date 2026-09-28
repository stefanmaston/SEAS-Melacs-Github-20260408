function tickLabel(row) {
  const raw = String(row.t || row.TimeStamp || "");
  const parts = raw.split(" ");
  return parts[1] || parts[0];
}

function extent(rows, keys) {
  let lo = Infinity;
  let hi = -Infinity;
  for (const row of rows) {
    for (const key of keys) {
      const n = Number(row[key]);
      if (Number.isNaN(n)) continue;
      lo = Math.min(lo, n);
      hi = Math.max(hi, n);
    }
  }
  if (!Number.isFinite(lo) || !Number.isFinite(hi)) return [0, 1];
  if (lo === hi) return [lo - 1, hi + 1];
  const pad = (hi - lo) * 0.12;
  return [lo - pad, hi + pad];
}

function pathFor(rows, key, xOf, yOf) {
  return rows
    .map((row, i) => `${i === 0 ? "M" : "L"} ${xOf(i).toFixed(1)} ${yOf(Number(row[key])).toFixed(1)}`)
    .join(" ");
}

export function TrendChart({ title, note, rows, series, extra }) {
  const width = 720;
  const height = 280;
  const left = 48;
  const right = 56;
  const top = 16;
  const bottom = 28;
  const plotW = width - left - right;
  const plotH = height - top - bottom;
  const leftKeys = series.filter((s) => s.axis !== "right").map((s) => s.key);
  const rightKeys = series.filter((s) => s.axis === "right").map((s) => s.key);
  const [y0, y1] = extent(rows, leftKeys);
  const [r0, r1] = rightKeys.length ? extent(rows, rightKeys) : [0, 1];
  const xOf = (i) => left + (rows.length < 2 ? plotW / 2 : (i / (rows.length - 1)) * plotW);
  const yLeft = (v) => top + ((y1 - v) / (y1 - y0)) * plotH;
  const yRight = (v) => top + ((r1 - v) / (r1 - r0)) * plotH;
  const ticks = 4;

  return (
    <figure className="chart">
      <figcaption>
        <strong>{title}</strong>
        <span className="chart-side">
          {rows.length >= 2 && note ? <span>{note}</span> : null}
          {extra}
        </span>
      </figcaption>
      <svg viewBox={`0 0 ${width} ${height}`} role="img" aria-label={title}>
          {Array.from({ length: ticks + 1 }, (_, i) => {
            const y = top + (plotH / ticks) * i;
            const value = y1 - ((y1 - y0) / ticks) * i;
            return (
              <g key={y}>
                <line x1={left} x2={width - right} y1={y} y2={y} className="grid" />
                <text x={left - 8} y={y + 4} textAnchor="end" className="axis">
                  {Math.round(value)}
                </text>
              </g>
            );
          })}
          {rightKeys.length > 0
            ? Array.from({ length: ticks + 1 }, (_, i) => {
                const y = top + (plotH / ticks) * i;
                const value = r1 - ((r1 - r0) / ticks) * i;
                return (
                  <text key={`r${y}`} x={width - right + 8} y={y + 4} className="axis right">
                    {Math.round(value)}
                  </text>
                );
              })
            : null}
          {rows.length >= 2
            ? series.map((item) => (
              <path
                key={item.key}
                d={pathFor(rows, item.key, xOf, item.axis === "right" ? yRight : yLeft)}
                fill="none"
                stroke={item.color}
                strokeWidth="2.4"
              />
            ))
            : (
              <text x={left + plotW / 2} y={top + plotH / 2} textAnchor="middle" className="axis">
                {note || "Väntar på fler mätpunkter."}
              </text>
            )}
          {rows.length >= 2 ? (
            <text x={left} y={height - 6} className="axis">
              {tickLabel(rows[0])}
            </text>
          ) : null}
          {rows.length >= 2 ? (
            <text x={width - right} y={height - 6} textAnchor="end" className="axis">
              {tickLabel(rows[rows.length - 1])}
            </text>
          ) : null}
        </svg>
      <ul className="legend">
        {series.map((item) => (
          <li key={item.key}>
            <i style={{ background: item.color }} />
            {item.label}
            {rows.length > 0 ? <b>{rows[rows.length - 1][item.key]}</b> : null}
          </li>
        ))}
      </ul>
    </figure>
  );
}
