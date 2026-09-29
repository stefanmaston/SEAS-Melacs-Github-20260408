function AdPort({ x, y, name, value }) {
  const missing = value == null || value === "";
  const n = missing ? 0 : Number(value) || 0;
  const fill = missing ? 0 : Math.max(2, Math.min(18, (n / 4095) * 18));
  return (
    <g>
      <rect x={x} y={y} width="44" height="30" rx="3" className="plug" />
      {fill > 0 ? <rect x={x + 6} y={y + 24 - fill} width="6" height={fill} className="fill" /> : null}
      <text x={x + 28} y={y + 20} textAnchor="middle" className="silk tiny">{name}</text>
      <text x={x + 22} y={y + 46} textAnchor="middle" className="silk tiny">{missing ? "—" : n}</text>
    </g>
  );
}

function IoPort({ x, y, name, on }) {
  return (
    <g>
      <rect x={x} y={y} width="44" height="30" rx="3" className="plug" />
      <text x={x + 22} y={y + 20} textAnchor="middle" className="silk tiny">{name}</text>
      <circle cx={x + 22} cy={y + 46} r="7" className={on ? "lamp on" : "lamp"} />
    </g>
  );
}

function Jack({ x, y, name, wide }) {
  const w = wide ? 78 : 36;
  return (
    <g>
      <rect x={x} y={y} width={w} height="28" rx="3" className="chip" />
      <text x={x + w / 2} y={y + 18} textAnchor="middle" className="silk tiny">{name}</text>
    </g>
  );
}

function SpiJack({ x, y, name, on, role }) {
  const w = 36;
  return (
    <g>
      <rect x={x} y={y} width={w} height="28" rx="3" className="chip" />
      <text x={x + w / 2} y={y + 18} textAnchor="middle" className="silk tiny">{name}</text>
      <circle cx={x + w / 2} cy={y + 44} r="7" className={on ? "lamp on" : "lamp"} />
      {role ? (
        <text x={x + w / 2} y={y + 66} textAnchor="middle" className="silk tiny">{role}</text>
      ) : null}
    </g>
  );
}

function RoleLamp({ x, y, on, role }) {
  return (
    <g>
      <circle cx={x + 18} cy={y + 44} r="7" className={on ? "lamp on" : "lamp"} />
      <text x={x + 18} y={y + 66} textAnchor="middle" className="silk tiny">{role}</text>
    </g>
  );
}

function Led({ x, y, on, label }) {
  return (
    <g>
      <circle cx={x} cy={y} r="7" className={on ? "lamp on" : "lamp"} />
      <text x={x + 14} y={y + 4} className="silk tiny">{label}</text>
    </g>
  );
}

function Bridge({ x, y, jp, led, ledOn, name, dis, ali, bli, ahi, bhi }) {
  const armed = !dis;
  return (
    <g>
      <rect x={x} y={y} width="230" height="132" rx="12" className={armed ? "block hot" : "block"} />
      <text x={x + 16} y={y + 24} className="silk strong">{jp}</text>
      <text x={x + 78} y={y + 24} className="silk">{name}</text>
      <Led x={x + 16} y={y + 50} on={ledOn} label={led} />
      <text x={x + 16} y={y + 78} className={armed ? "warn" : "safe"}>
        {armed ? "Drivning på" : "Spärr, bryggan av"}
      </text>
      <text x={x + 16} y={y + 100} className="silk tiny">
        ALI {ali ? "1" : "0"} · BLI {bli ? "1" : "0"}
      </text>
      <text x={x + 16} y={y + 118} className="silk tiny">
        AHI {ahi} · BHI {bhi}
      </text>
    </g>
  );
}

export function Schematic({ plant }) {
  const inp = plant.inputs;
  const out = plant.applied;
  const ad = inp.ad || [];
  const dio = [...(inp.dio || []), ...(out.dio || [])];
  const sip = out.sip || [];
  const ao = out.ao || [];
  const live = Boolean(plant.source);
  const err = Number(inp.error_code) || 0;
  const lanOn = live && Boolean(plant.link) && (err & 4) === 0;
  const spiChips = [
    { role: "A/D", on: live },
    { role: "RTC", on: live && (err & 2) === 0 },
  ];
  const spiBus = [
    { name: "JP12", role: "LAN", on: lanOn },
    { name: "JP31", role: "SD", on: Boolean(inp.sd_ok) },
  ];
  const spiExtra = [27, 28, 29, 30];
  const rails = ["3V3", "5V", "12V", "24V", "60V"];
  const da = [
    { jp: "JP7", led: "LED10", on: Boolean(sip[4]), value: "SIP4" },
    { jp: "JP8", led: "LED11", on: live && Number(ao[0]) > 0, value: live ? `AO0 ${ao[0] ?? 0}` : "—" },
    { jp: "JP9", led: "LED12", on: live && Number(ao[1]) > 0, value: live ? `AO1 ${ao[1] ?? 0}` : "—" },
    { jp: "JP10", led: "LED13", on: live && Number(ao[2]) > 0, value: live ? `AO2 ${ao[2] ?? 0}` : "—" },
  ];
  const relays = [
    { jp: "JP3", led: "LED1", on: Boolean(sip[0]) },
    { jp: "JP4", led: "LED2", on: Boolean(sip[1]) },
    { jp: "JP5", led: "LED3", on: Boolean(sip[2]) },
    { jp: "JP6", led: "LED4", on: Boolean(sip[3]) },
    { jp: "", led: "LED5", on: Boolean(sip[5]) },
  ];

  return (
    <figure className="board-wrap">
      <figcaption>
        Placering som på Melacs-kortet. Gröna lampor följer det kortet rapporterar.
      </figcaption>
      <svg viewBox="0 0 1100 760" role="img" aria-label="Melacs-kortets portar och lysdioder">
        <rect x="8" y="8" width="1084" height="744" rx="22" className="pcb" />

        <text x="24" y="36" className="silk tiny">A/D</text>
        {ad.slice(0, 8).map((value, i) => (
          <AdPort key={`ad${i}`} x={24 + i * 52} y={44} name={`AD${i}`} value={value} />
        ))}

        <text x="656" y="36" className="silk tiny">I/O</text>
        {Array.from({ length: 8 }, (_, i) => (
          <IoPort key={`dio${i}`} x={656 + i * 52} y={44} name={`DIO${i}`} on={Boolean(dio[i])} />
        ))}

        <rect x="456" y="44" width="180" height="62" rx="8" className="block" />
        <text x="546" y="70" textAnchor="middle" className="silk strong">JP32</text>
        <text x="546" y="90" textAnchor="middle" className="silk tiny">Display</text>

        <text x="24" y="118" className="silk tiny">SPI</text>
        {spiChips.map((item, i) => (
          <RoleLamp key={item.role} x={24 + i * 48} y={128} on={item.on} role={item.role} />
        ))}
        {spiBus.map((item, i) => (
          <SpiJack
            key={item.name}
            x={24 + (spiChips.length + i) * 48}
            y={128}
            name={item.name}
            on={item.on}
            role={item.role}
          />
        ))}
        {spiExtra.map((n, i) => (
          <SpiJack key={`jp${n}`} x={236 + i * 44} y={128} name={`JP${n}`} on={false} />
        ))}
        <text x={236 + (3 * 44 + 36) / 2} y={194} textAnchor="middle" className="silk tiny">
          Extra SPI
        </text>

        <rect x="640" y="168" width="240" height="156" rx="14" className="block cpu" />
        <text x="656" y="196" className="silk strong">PIC32MX795</text>
        <text x="656" y="220" className="silk">Modbus TCP slav 1</text>
        <text x="656" y="242" className="silk">{plant.host === "—" ? "Ingen länk" : `${plant.host}:502`}</text>
        <text x="656" y="268" className="silk">T_BOARD {live ? `${inp.t_board} °C` : "—"}</text>
        <text x="656" y="290" className="silk">T1 {live ? inp.t1 : "—"} · T2 {live ? inp.t2 : "—"}</text>
        <text x="656" y="310" className="silk tiny">Melacs 7</text>

        <SpiJack x={900} y={168} name="JP31" on={Boolean(inp.sd_ok)} role="SD" />
        <Led x={1030} y={212} on={Boolean(inp.sd_ok)} label="LED7" />

        <Bridge
          x={24}
          y={360}
          jp="JP18"
          led="LED8"
          ledOn={!out.h1_dis}
          name="H-brygga 1"
          dis={out.h1_dis}
          ali={out.h1_ali}
          bli={out.h1_bli}
          ahi={live ? out.h1_ahi : "—"}
          bhi={live ? out.h1_bhi : "—"}
        />
        <Bridge
          x={270}
          y={360}
          jp="JP19"
          led="LED9"
          ledOn={!out.h2_dis}
          name="H-brygga 2"
          dis={out.h2_dis}
          ali={out.h2_ali}
          bli={out.h2_bli}
          ahi={live ? out.h2_ahi : "—"}
          bhi={live ? out.h2_bhi : "—"}
        />

        <rect x="520" y="360" width="250" height="200" rx="12" className="block" />
        <text x="536" y="384" className="silk strong">D/A 0–10 V</text>
        {da.map((item, i) => (
          <g key={item.jp}>
            <Led x={540} y={414 + i * 34} on={item.on} label={item.led} />
            <text x={640} y={418 + i * 34} className="silk">{item.jp}</text>
            <text x={690} y={418 + i * 34} className="silk tiny">{item.value}</text>
          </g>
        ))}

        <rect x="790" y="360" width="286" height="230" rx="12" className="block" />
        <text x="806" y="384" className="silk strong">SIP relä</text>
        {relays.map((item, i) => (
          <g key={item.led}>
            {item.jp ? <text x={806} y={416 + i * 28} className="silk">{item.jp}</text> : null}
            <Led x={870} y={412 + i * 28} on={item.on} label={item.led} />
          </g>
        ))}
        <Led x={806} y={560} on={Boolean(sip[6])} label="SIP6" />
        <Led x={910} y={560} on={Boolean(sip[7])} label="SIP7" />

        <text x="24" y="640" className="silk tiny">Matning</text>
        {rails.map((name, i) => (
          <g key={name}>
            <circle cx={36 + i * 58} cy={668} r="7" className="supply" />
            <text x={48 + i * 58} y={672} className="silk tiny">{name}</text>
          </g>
        ))}
        <Jack x={340} y={652} name="60 V" wide />
        <Jack x={428} y={652} name="24 V" wide />
        <Jack x={516} y={652} name="12–24 V" wide />
        <SpiJack x={640} y={628} name="JP22" on={false} role="USB" />
        <SpiJack x={728} y={628} name="JP12" on={lanOn} role="LAN" />
        <text x="24" y="710" className="silk tiny">0 V</text>
      </svg>
    </figure>
  );
}
