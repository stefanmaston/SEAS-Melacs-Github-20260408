import { WEEKDAYS } from "../shared/columns.js";

export function pad(n) {
  return String(n).padStart(2, "0");
}

export function formatRtc(rtc) {
  if (!rtc) return "—";
  const day = WEEKDAYS[rtc.weekday] || "";
  return `${rtc.year}-${pad(rtc.month)}-${pad(rtc.day)} ${pad(rtc.hour)}:${pad(rtc.minute)}:${pad(rtc.second)} ${day}`;
}

export function alarmText(message) {
  const text = String(message || "");
  if (/ECONNRESET/i.test(text)) return "Kortet bröt länken";
  if (/ECONNREFUSED/i.test(text)) return "Ingen kontakt med kortet";
  if (/ETIMEDOUT|svarade inte/i.test(text)) return "Kortet svarade inte";
  return text;
}

export function errorText(code) {
  const n = Number(code) || 0;
  if (n === 0) return "Inga fel";
  const parts = [];
  if (n & 1) parts.push("SD");
  if (n & 2) parts.push("RTC");
  if (n & 4) parts.push("nät");
  if (n & ~7) parts.push(`övrigt ${n}`);
  return parts.join(", ");
}

export function fieldsFromRtc(rtc) {
  return {
    year: rtc.year,
    month: rtc.month,
    day: rtc.day,
    hour: rtc.hour,
    minute: rtc.minute,
    second: rtc.second,
    weekday: rtc.weekday,
  };
}

export function dateValue(fields) {
  return `${fields.year}-${pad(fields.month)}-${pad(fields.day)}`;
}

export function timeValue(fields) {
  return `${pad(fields.hour)}:${pad(fields.minute)}:${pad(fields.second)}`;
}
