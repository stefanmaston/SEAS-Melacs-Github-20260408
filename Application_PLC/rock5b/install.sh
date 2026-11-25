#!/bin/sh
# Installera Melacs SEAS PLC på en DietPi så lådan startar vid strömmen.
# Kör som root i den här katalogen: ./install.sh
set -eu

HERE=$(CDPATH= cd -- "$(dirname "$0")" && pwd)
if [ -f "$HERE/versions.env" ]; then
  # shellcheck disable=SC1091
  . "$HERE/versions.env"
fi
: "${FUXA_IMAGE:=frangoteam/fuxa:1.3.5}"
HUB_HOST=194.103.95.171
HUB_KEY='OvhWAmGh3TvGgrQ7ZGq3+bvm0wa1HJc2gOL7jo4qov4='
OPT=/opt/melacs-dashboard

if [ "$(uname)" != "Linux" ]; then
  echo "Kör install.sh på DietPi." >&2
  exit 1
fi
if [ "$(id -u)" -ne 0 ]; then
  echo "Kör install.sh som root." >&2
  exit 1
fi
if [ ! -x /usr/bin/node ]; then
  echo "Node saknas på /usr/bin/node. Installera Node och kör install.sh igen." >&2
  exit 1
fi

if [ ! -f "$HERE/dashboard/dist/index.html" ]; then
  if ! command -v npm >/dev/null 2>&1; then
    echo "dashboard/dist saknas och npm finns inte. Bygg på en dator med npm run build." >&2
    exit 1
  fi
  (cd "$HERE/dashboard" && npm ci && npm run build)
fi

free_http_port() {
  if systemctl cat "$1.service" >/dev/null 2>&1 && systemctl is-active --quiet "$1"; then
    systemctl disable --now "$1"
    echo "Stängde $1. Dashboarden tar port 80."
  fi
}

free_http_port lighttpd
free_http_port nginx
free_http_port apache2

busy=0
for pid in $(ss -ltnp 'sport = :80' 2>/dev/null | sed -n 's/.*pid=\([0-9][0-9]*\).*/\1/p' | sort -u); do
  cmd=$(tr '\0' ' ' < "/proc/$pid/cmdline" 2>/dev/null || true)
  case $cmd in
    *serve.mjs*|*melacs-dashboard*) ;;
    *)
      echo "Port 80 är upptagen: $cmd" >&2
      busy=1
      ;;
  esac
done
if [ "$busy" -ne 0 ]; then
  exit 1
fi

allow_lan_http() {
  if ! command -v iptables >/dev/null 2>&1; then
    return 0
  fi
  policy=$(iptables -S INPUT 2>/dev/null | awk '/^-P INPUT / { print $3; exit }')
  if [ "$policy" != "DROP" ] && [ "$policy" != "REJECT" ]; then
    echo "Brandväggen släpper in trafik till port 80."
    return 0
  fi
  for net in 10.0.0.0/8 172.16.0.0/12 192.168.0.0/16; do
    if ! iptables -C INPUT -p tcp --dport 80 -s "$net" -j ACCEPT 2>/dev/null; then
      iptables -I INPUT -p tcp --dport 80 -s "$net" -j ACCEPT
    fi
  done
  if [ -d /etc/iptables ]; then
    iptables-save > /etc/iptables/rules.v4
  fi
  echo "Brandväggen släpper in TCP 80 från lokala nät."
}

allow_lan_http

mkdir -p "$OPT/server" "$OPT/shared" /etc/melacs /var/lib/melacs /usr/local/sbin
rm -rf "$OPT/dist"
cp -a "$HERE/dashboard/dist" "$OPT/dist"
cp -a "$HERE/dashboard/server/." "$OPT/server/"
cp -a "$HERE/dashboard/shared/columns.js" "$OPT/shared/columns.js"
install -m 755 "$HERE/dashboard/melacs-plc-net" /usr/local/sbin/melacs-plc-net
install -m 755 "$HERE/dashboard/melacs-guard" /usr/local/sbin/melacs-guard
install -m 644 "$HERE/dashboard/melacs-net.service" /etc/systemd/system/melacs-net.service
install -m 644 "$HERE/dashboard/melacs-modbus-proxy.service" /etc/systemd/system/melacs-modbus-proxy.service
install -m 644 "$HERE/dashboard/melacs-dashboard.service" /etc/systemd/system/melacs-dashboard.service
install -m 644 "$HERE/dashboard/melacs-guard.service" /etc/systemd/system/melacs-guard.service
install -m 644 "$HERE/dashboard/melacs-guard.timer" /etc/systemd/system/melacs-guard.timer
install -m 644 "$HERE/dashboard/melacs-discover.service" /etc/systemd/system/melacs-discover.service
install -m 644 "$HERE/dashboard/melacs-discover.timer" /etc/systemd/system/melacs-discover.timer
if [ ! -f /etc/melacs/discover.allow ]; then
  install -m 644 "$HERE/dashboard/discover.allow.example" /etc/melacs/discover.allow
fi
install -m 755 "$HERE/datalogger-backup/melacs-datalogger-backup" /usr/local/sbin/melacs-datalogger-backup
install -m 644 "$HERE/datalogger-backup/melacs-datalogger-backup.service" /etc/systemd/system/melacs-datalogger-backup.service
install -m 644 "$HERE/datalogger-backup/melacs-datalogger-backup.timer" /etc/systemd/system/melacs-datalogger-backup.timer
if [ ! -f /etc/melacs/datalogger-cards ]; then
  install -m 644 "$HERE/datalogger-backup/datalogger-cards.example" /etc/melacs/datalogger-cards
  mkdir -p /var/lib/melacs/cards/kort-1
fi

mkdir -p /etc/systemd/system.conf.d
cat > /etc/systemd/system.conf.d/melacs-watchdog.conf << 'EOF'
[Manager]
RuntimeWatchdogSec=60s
RebootWatchdogSec=10min
EOF

systemctl daemon-reload
systemctl enable --now melacs-net.service melacs-modbus-proxy.service melacs-dashboard.service
systemctl enable --now melacs-datalogger-backup.timer
systemctl enable --now melacs-guard.timer
systemctl enable --now melacs-discover.timer
systemctl daemon-reexec || true

python3 - << 'PY'
from pathlib import Path
path = Path("/etc/fstab")
if not path.exists():
    raise SystemExit(0)
out = []
for line in path.read_text().splitlines():
    if not line.strip() or line.lstrip().startswith("#") or "nofail" not in line:
        out.append(line)
        continue
    if "x-systemd.mount-timeout=" in line:
        out.append(line)
        continue
    parts = line.split()
    if len(parts) < 4:
        out.append(line)
        continue
    parts[3] = parts[3] + ",x-systemd.device-timeout=10,x-systemd.mount-timeout=15"
    out.append(" ".join(parts))
path.write_text("\n".join(out) + "\n")
PY

python3 - << 'PY'
from pathlib import Path
path = Path("/etc/avahi/avahi-daemon.conf")
text = path.read_text() if path.exists() else "[server]\n"
lines = text.splitlines()
out = []
in_server = False
seen = False
for line in lines:
    if line.startswith("["):
        if in_server and not seen:
            out.append("host-name=melacs")
            seen = True
        in_server = line.strip() == "[server]"
    if in_server and (line.startswith("host-name=") or line.startswith("#host-name=")):
        if not seen:
            out.append("host-name=melacs")
            seen = True
        continue
    out.append(line)
if not seen:
    if not any(line.strip() == "[server]" for line in out):
        out.insert(0, "[server]")
    inserted = False
    rewritten = []
    for line in out:
        rewritten.append(line)
        if not inserted and line.strip() == "[server]":
            rewritten.append("host-name=melacs")
            inserted = True
    out = rewritten
path.parent.mkdir(parents=True, exist_ok=True)
path.write_text("\n".join(out) + "\n")
PY

python3 - << 'PY'
from pathlib import Path
path = Path("/etc/avahi/avahi-daemon.conf")
text = path.read_text() if path.exists() else "[server]\n"
lines = text.splitlines()
out = []
in_server = False
seen = False
for line in lines:
    if line.startswith("["):
        if in_server and not seen:
            out.append("deny-interfaces=plc0")
            seen = True
        in_server = line.strip() == "[server]"
    if in_server and (line.startswith("deny-interfaces=") or line.startswith("#deny-interfaces=")):
        if not seen:
            out.append("deny-interfaces=plc0")
            seen = True
        continue
    out.append(line)
if not seen:
    if not any(line.strip() == "[server]" for line in out):
        out.insert(0, "[server]")
    rewritten = []
    inserted = False
    for line in out:
        rewritten.append(line)
        if not inserted and line.strip() == "[server]":
            rewritten.append("deny-interfaces=plc0")
            inserted = True
    out = rewritten
path.write_text("\n".join(out) + "\n")
hosts = Path("/etc/avahi/hosts")
if hosts.exists():
    kept = [line for line in hosts.read_text().splitlines() if "dietpi-share.local" not in line]
    hosts.write_text("\n".join(kept) + ("\n" if kept else ""))
PY

if ! command -v avahi-daemon >/dev/null 2>&1; then
  DEBIAN_FRONTEND=noninteractive apt-get update -qq
  DEBIAN_FRONTEND=noninteractive apt-get install -y avahi-daemon
fi
systemctl enable --now avahi-daemon
systemctl restart avahi-daemon

if command -v docker >/dev/null 2>&1; then
  if docker ps -a --format '{{.Names}}' | grep -qx melacs-fuxa; then
    docker update --restart unless-stopped melacs-fuxa >/dev/null
    docker start melacs-fuxa >/dev/null 2>&1 || true
  else
    if ! docker run -d --name melacs-fuxa --restart unless-stopped \
      -p 127.0.0.1:1881:1881 "$FUXA_IMAGE"; then
      echo "FUXA startade inte. Dashboarden svarar ändå på port 80."
    fi
  fi
  found_plc=0
  for name in openplc-runtime openplc; do
    if docker ps -a --format '{{.Names}}' | grep -qx "$name"; then
      found_plc=1
      docker update --restart unless-stopped "$name" >/dev/null
      docker start "$name" >/dev/null 2>&1 || true
    fi
  done
  if [ "$found_plc" -eq 1 ]; then
    sh "$HERE/openplc/prepare-runtime.sh" || echo "OpenPLC kör, men Modbus-kartan skrevs inte om."
  else
    echo "OpenPLC-containern saknas. Installera OpenPLC Runtime v4 och kör openplc/prepare-runtime.sh."
  fi
else
  echo "Docker saknas. OpenPLC och FUXA installeras inte av det här skriptet."
fi

pub=""
if [ -f /mnt/dietpi_userdata/rustdesk/id_ed25519.pub ]; then
  pub=$(tr -d ' \r\n' < /mnt/dietpi_userdata/rustdesk/id_ed25519.pub)
fi
role=client
if [ "$pub" = "$HUB_KEY" ]; then
  role=hub
fi
if [ -n "${MELACS_RUSTDESK_ROLE:-}" ]; then
  role=$MELACS_RUSTDESK_ROLE
fi

unit_exists() {
  systemctl cat "$1" >/dev/null 2>&1
}

if [ "$role" = "hub" ]; then
  if unit_exists rustdesksignal.service; then
    systemctl enable --now rustdesksignal.service
  fi
  if unit_exists rustdeskrelay.service; then
    systemctl enable --now rustdeskrelay.service
  fi
  lan_ip=$(ip -4 -o addr show dev eth0 | awk '{ split($4, a, "/"); if (a[1] != "192.168.1.10") print a[1] }' | head -n 1)
  if ! command -v upnpc >/dev/null 2>&1; then
    DEBIAN_FRONTEND=noninteractive apt-get update -qq
    DEBIAN_FRONTEND=noninteractive apt-get install -y miniupnpc || true
  fi
  if command -v upnpc >/dev/null 2>&1 && [ -n "$lan_ip" ] && upnpc -s >/dev/null 2>&1; then
    map_port() {
      if ! upnpc -e "Melacs RustDesk" -a "$lan_ip" "$1" "$1" "$2" 0 >/dev/null; then
        echo "Routern tog inte emot $2 $1. Vidarebefordra den till $lan_ip."
      fi
    }
    map_port 21115 TCP
    map_port 21116 TCP
    map_port 21117 TCP
    map_port 21118 TCP
    map_port 21119 TCP
    map_port 21116 UDP
    map_port 21119 UDP
  else
    echo "Routern tar inte emot UPnP. Vidarebefordra TCP 21115-21119 och UDP 21116 och 21119 till ${lan_ip:-lådans adress}."
  fi
else
  for svc in rustdesksignal.service rustdeskrelay.service hbbs.service hbbr.service; do
    if unit_exists "$svc"; then
      systemctl disable --now "$svc" || true
      echo "Stängde $svc. Den här lådan ringer kontorets RustDesk-server."
    fi
  done
fi

if command -v rustdesk >/dev/null 2>&1; then
  systemctl stop rustdesk.service 2>/dev/null || true
  mkdir -p /root/.config/rustdesk
  python3 - "$HUB_HOST" "$HUB_KEY" << 'PY'
import pathlib, sys
host, key = sys.argv[1], sys.argv[2]
path = pathlib.Path("/root/.config/rustdesk/RustDesk2.toml")
lines = path.read_text().splitlines() if path.exists() else []
top = {"rendezvous_server": f"{host}:21116"}
opts = {
    "custom-rendezvous-server": host,
    "relay-server": host,
    "key": key,
}

def quote(value):
    return "'" + value.replace("'", "''") + "'"

out = []
section = ""
seen_top = set()
seen_opt = set()
for line in lines:
    stripped = line.strip()
    if stripped.startswith("[") and stripped.endswith("]"):
        if section == "options":
            for name, value in opts.items():
                if name not in seen_opt:
                    out.append(f"{name} = {quote(value)}")
                    seen_opt.add(name)
        section = stripped[1:-1]
        out.append(line)
        continue
    if section == "" and "=" in line:
        name = line.split("=", 1)[0].strip()
        if name in top:
            out.append(f"{name} = {quote(top[name])}")
            seen_top.add(name)
            continue
    if section == "options" and "=" in line:
        name = line.split("=", 1)[0].strip()
        if name in opts:
            out.append(f"{name} = {quote(opts[name])}")
            seen_opt.add(name)
            continue
    out.append(line)
if section == "options":
    for name, value in opts.items():
        if name not in seen_opt:
            out.append(f"{name} = {quote(value)}")
            seen_opt.add(name)
if "rendezvous_server" not in seen_top:
    out.insert(0, f"rendezvous_server = {quote(top['rendezvous_server'])}")
if "options" not in {line.strip()[1:-1] for line in out if line.strip().startswith("[") and line.strip().endswith("]")}:
    if out and out[-1] != "":
        out.append("")
    out.append("[options]")
    for name, value in opts.items():
        out.append(f"{name} = {quote(value)}")
path.write_text("\n".join(out) + "\n")
PY
  systemctl enable --now rustdesk.service
else
  echo "RustDesk-klienten är inte installerad. Installera den och kör install.sh igen."
fi

echo
echo "Melacs SEAS PLC är installerad."
ip -4 -o addr show dev eth0 | awk '{ split($4, a, "/"); if (a[1] != "192.168.1.10") print "Lokal adress  http://" a[1] "/" }'
if ! ip -4 -o addr show dev eth0 | awk '{ split($4, a, "/"); if (a[1] != "192.168.1.10") found=1 } END { exit !found }'; then
  echo "eth0 har ingen adress på platsens nät, bara kortlänken 192.168.1.10." >&2
fi
echo "Namn          http://melacs.local/"
if [ -f "$OPT/data/plant-id" ]; then
  echo "Anläggnings-id $(tr -d ' \r\n' < "$OPT/data/plant-id")"
fi
if [ -f "$OPT/data/owner-password.txt" ]; then
  echo "Service-lösenordet ligger i $OPT/data/owner-password.txt"
fi
echo "RustDesk       $HUB_HOST:21116"
echo "Roll           $role"
if command -v rustdesk >/dev/null 2>&1; then
  rid=$(timeout 5 rustdesk --get-id 2>/dev/null || true)
  if [ -n "$rid" ]; then
    echo "RustDesk-ID    $rid"
  fi
fi
