function level(value, max) {
  const n = Number(value) || 0;
  return Math.max(0.08, Math.min(1, n / max));
}

function Channel({ x, y, name, value, max }) {
  const h = 54;
  const fill = level(value, max) * h;
  return (
    <g>
      <rect x={x} y={y} width="28" height={h} rx="3" className="well" />
      <rect x={x} y={y + h - fill} width="28" height={fill} className="fill" />
      <text x={x + 14} y={y + h + 16} textAnchor="middle" className="silk tiny">
        {name}
      </text>
      <text x={x + 14} y={y - 6} textAnchor="middle" className="silk tiny">
        {value}
      </text>
    </g>
  );
}

function Lamp({ x, y, on, label }) {
  return (
    <g>
      <circle cx={x} cy={y} r="8" className={on ? "lamp on" : "lamp"} />
      <text x={x + 16} y={y + 4} className="silk">
        {label}
      </text>
    </g>
  );
}

function Bridge({ x, y, name, dis, ali, bli, ahi, bhi }) {
  const armed = !dis;
  return (
    <g>
      <rect x={x} y={y} width="250" height="132" rx="12" className={armed ? "block hot" : "block"} />
      <text x={x + 16} y={y + 24} className="silk strong">
        {name}
      </text>
      <text x={x + 16} y={y + 46} className={armed ? "warn" : "safe"}>
        {armed ? "Drivning på" : "Spärr, bryggan av"}
      </text>
      <text x={x + 16} y={y + 72} className="silk">
        ALI {ali ? "1" : "0"} · BLI {bli ? "1" : "0"}
      </text>
      <text x={x + 16} y={y + 96} className="silk">
        AHI {ahi}
      </text>
      <text x={x + 16} y={y + 116} className="silk">
        BHI {bhi}
      </text>
    </g>
  );
}

export function Schematic({ plant }) {
  const inp = plant.inputs;
  const out = plant.applied;
  return (
    <figure className="board-wrap">
      <figcaption>
        Schematisk bild av Melacs. Lampor och staplar följer det som ligger på korten just nu.
      </figcaption>
      <svg viewBox="0 0 980 640" role="img" aria-label="Schematisk bild av Melacs">
        <rect x="16" y="16" width="948" height="608" rx="22" className="pcb" />
        <text x="40" y="50" className="silk title">
          MELACS
        </text>
        <text x="210" y="50" className="silk sub">
          SEAS · PIC32MX795F512L
        </text>
        <text x="40" y="84" className="silk tiny">
          Yttre analogt AD0–AD7
        </text>
        {inp.ad.map((value, i) => (
          <Channel key={`ad${i}`} x={40 + i * 46} y={108} name={`AD${i}`} value={value} max={4095} />
        ))}
        <text x="430" y="84" className="silk tiny">
          Inbyggd analog AI10–AI15
        </text>
        {inp.ai.map((value, i) => (
          <Channel key={`ai${i}`} x={430 + i * 46} y={108} name={`AI${10 + i}`} value={value} max={4095} />
        ))}

        <rect x="360" y="210" width="250" height="150" rx="14" className="block cpu" />
        <text x="384" y="242" className="silk strong">
          PIC32
        </text>
        <text x="384" y="266" className="silk">
          Modbus TCP slav 1
        </text>
        <text x="384" y="290" className="silk">
          {plant.host}:502
        </text>
        <text x="384" y="318" className="silk">
          T_BOARD {inp.t_board} °C
        </text>
        <text x="384" y="340" className="silk">
          T1 {inp.t1} · T2 {inp.t2}
        </text>

        <text x="40" y="210" className="silk tiny">
          Ingångar
        </text>
        {inp.dio.map((on, i) => (
          <Lamp key={`in${i}`} x={52} y={236 + i * 28} on={on} label={`DIO${i}`} />
        ))}

        <text x="760" y="210" className="silk tiny">
          Utgångar
        </text>
        {out.dio.map((on, i) => (
          <Lamp key={`out${i}`} x={772} y={236 + i * 28} on={on} label={`DIO${4 + i}`} />
        ))}

        <Bridge
          x={40}
          y={400}
          name="H-brygga 1"
          dis={out.h1_dis}
          ali={out.h1_ali}
          bli={out.h1_bli}
          ahi={out.h1_ahi}
          bhi={out.h1_bhi}
        />
        <Bridge
          x={680}
          y={400}
          name="H-brygga 2"
          dis={out.h2_dis}
          ali={out.h2_ali}
          bli={out.h2_bli}
          ahi={out.h2_ahi}
          bhi={out.h2_bhi}
        />

        <rect x="320" y="400" width="340" height="150" rx="12" className="block" />
        <text x="338" y="426" className="silk strong">
          SPI
        </text>
        <g>
          <rect x="338" y="444" width="92" height="44" rx="6" className="chip" />
          <text x="384" y="470" textAnchor="middle" className="silk">
            RTC
          </text>
          <rect x="444" y="444" width="92" height="44" rx="6" className={inp.sd_ok ? "chip ok" : "chip"} />
          <text x="490" y="470" textAnchor="middle" className="silk">
            SD
          </text>
          <rect x="550" y="444" width="92" height="44" rx="6" className={plant.link ? "chip ok" : "chip"} />
          <text x="596" y="470" textAnchor="middle" className="silk">
            ETH
          </text>
        </g>
        <text x="338" y="516" className="silk tiny">
          SIP {out.sip.map((on, i) => `${i}${on ? "●" : "○"}`).join(" ")}
        </text>
        <text x="338" y="534" className="silk tiny">
          AO {out.ao.map((n, i) => `${i}:${n}`).join("  ")}
        </text>
      </svg>
    </figure>
  );
}
