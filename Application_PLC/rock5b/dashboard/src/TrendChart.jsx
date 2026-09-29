function tickLabel(row) {
  const raw = String(row.t || row.TimeStamp || "");
  const parts = raw.split(" ");
  return parts[1] || parts[0];
}

function pathFor(rows, key, xOf, yOf) {
  let pen = false;
  let path = "";
  rows.forEach((row, i) => {
    const value = Number(row[key]);
    if (!Number.isFinite(value)) {
      pen = false;
      return;
    }
    path += `${pen ? "L" : "M"} ${xOf(i).toFixed(1)} ${yOf(value).toFixed(1)} `;
    pen = true;
  });
  return path;
}

export function TrendChart({ title, note, rows, series, extra, yMaxLeft = 3300, yMaxRight = 3300, controls }) {
  const width = 720;
  const height = 280;
  const left = 52;
  const right = 58;
  const top = 16;
  const bottom = 28;
  const plotW = width - left - right;
  const plotH = height - top - bottom;
  const y0 = 0;
  const y1 = Math.max(1, Number(yMaxLeft) || 1);
  const r0 = 0;
  const r1 = Math.max(1, Number(yMaxRight) || 1);
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
          <defs>
            <clipPath id="chart-plot">
              <rect x={left} y={top} width={plotW} height={plotH} />
            </clipPath>
          </defs>
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
          {Array.from({ length: ticks + 1 }, (_, i) => {
                const y = top + (plotH / ticks) * i;
                const value = r1 - ((r1 - r0) / ticks) * i;
                return (
                  <text key={`r${y}`} x={width - right + 8} y={y + 4} className="axis right">
                    {Math.round(value)}
                </text>
              );
            })}
          {rows.length >= 2
            ? series.map((item) => (
              <path
                key={item.id || item.key}
                d={pathFor(rows, item.key, xOf, item.axis === "right" ? yRight : yLeft)}
                fill="none"
                stroke={item.color}
                strokeWidth="2.4"
                clipPath="url(#chart-plot)"
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
      {controls}
      <ul className="legend">
        {series.map((item) => (
          <li key={item.id || item.key}>
            <i style={{ background: item.color }} />
            {item.label}
            <b>{rows.length > 0 && Number.isFinite(Number(rows[rows.length - 1][item.key])) ? rows[rows.length - 1][item.key] : "—"}</b>
          </li>
        ))}
      </ul>
    </figure>
  );
}
