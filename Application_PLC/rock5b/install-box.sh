#!/bin/sh
# Installera Melacs-stacken på en DietPi som redan har gjort sin första start.
# Anropas av melacs-install.sh från den release som ska installeras.
set -eu

HERE=$(CDPATH= cd -- "$(dirname "$0")" && pwd)
export DEBIAN_FRONTEND=noninteractive
export GIT_TERMINAL_PROMPT=0

if [ "$(id -u)" -ne 0 ]; then
  echo "Kör install-box.sh som root." >&2
  exit 1
fi
if [ "$(uname)" != "Linux" ]; then
  echo "Kör install-box.sh på DietPi." >&2
  exit 1
fi
if [ "$(uname -m)" != "aarch64" ]; then
  echo "Melacs-paketet är för Rock 5B (aarch64)." >&2
  exit 1
fi
if [ ! -f "$HERE/versions.env" ]; then
  echo "versions.env saknas bredvid install-box.sh." >&2
  exit 1
fi
# shellcheck disable=SC1091
. "$HERE/versions.env"

missing=""
for name in NODE_MAJOR NODE_VERSION NODE_INSTALLER_REF OPENPLC_RUNTIME_VERSION OPENPLC_INSTALLER_REF OPENPLC_BOOTLOADER_VERSION FUXA_IMAGE RUSTDESK_VERSION; do
  eval "value=\${$name:-}"
  if [ -z "$value" ]; then
    missing="$missing $name"
  fi
done
if [ -n "$missing" ]; then
  echo "versions.env saknar:$missing" >&2
  exit 1
fi

tag=${MELACS_RELEASE_TAG:-}
sha=${MELACS_RELEASE_SHA:-}
if [ -z "$tag" ]; then
  tag=$(git -C "$HERE" describe --tags --exact-match 2>/dev/null || true)
fi
if [ -z "$tag" ]; then
  echo "Ingen release-tagg. Kör melacs-install.sh." >&2
  exit 1
fi
if [ -z "$sha" ]; then
  sha=$(git -C "$HERE" rev-parse HEAD 2>/dev/null || true)
fi

updated=0
apt_install() {
  if [ "$updated" -eq 0 ]; then
    apt-get update -qq
    updated=1
  fi
  apt-get install -y "$@"
}

run_dietpi_software() {
  if [ -x /boot/dietpi/dietpi-software ]; then
    /boot/dietpi/dietpi-software "$@" </dev/null
    return
  fi
  if [ -x /DietPi/dietpi/dietpi-software ]; then
    /DietPi/dietpi/dietpi-software "$@" </dev/null
    return
  fi
  echo "dietpi-software saknas." >&2
  return 1
}

echo "Installerar grundpaket."
base=""
command -v git >/dev/null 2>&1 || base="$base git"
command -v curl >/dev/null 2>&1 || base="$base curl"
command -v python3 >/dev/null 2>&1 || base="$base python3"
dpkg -s ca-certificates >/dev/null 2>&1 || base="$base ca-certificates"
if [ -n "$base" ]; then
  # shellcheck disable=SC2086
  apt_install $base
fi

node_is_old() {
  first=$(printf '%s\n%s\n' "$1" "$2" | sort -V | head -n 1)
  [ "$first" != "$2" ]
}

if [ -x /usr/local/bin/node ] && [ ! -x /usr/bin/node ]; then
  ln -sf /usr/local/bin/node /usr/bin/node
fi
current_node=""
if [ -x /usr/bin/node ]; then
  current_node=$(/usr/bin/node -p 'process.versions.node')
fi
wanted_node=${NODE_VERSION#v}
if [ -z "$current_node" ] || node_is_old "$current_node" "$wanted_node"; then
  echo "Installerar Node $NODE_VERSION."
  installer=$(mktemp)
  curl -fsSL "https://raw.githubusercontent.com/MichaIng/nodejs-linux-installer/${NODE_INSTALLER_REF}/node-install.sh" -o "$installer"
  bash "$installer" --version "$NODE_VERSION"
  rm -f "$installer"
  if [ -x /usr/local/bin/node ]; then
    ln -sf /usr/local/bin/node /usr/bin/node
  fi
  if [ -x /usr/local/bin/npm ]; then
    ln -sf /usr/local/bin/npm /usr/bin/npm
  fi
fi
if [ ! -x /usr/bin/node ]; then
  echo "Node saknas på /usr/bin/node." >&2
  exit 1
fi

if ! command -v docker >/dev/null 2>&1; then
  echo "Installerar Docker."
  run_dietpi_software install 162
fi
if ! docker info >/dev/null 2>&1; then
  systemctl enable --now docker.socket 2>/dev/null || true
  systemctl enable --now docker 2>/dev/null || true
fi
if ! docker info >/dev/null 2>&1; then
  echo "Docker startade inte." >&2
  exit 1
fi

if ! dpkg -s avahi-daemon >/dev/null 2>&1; then
  echo "Installerar Avahi."
  if [ -x /boot/dietpi/dietpi-software ] || [ -x /DietPi/dietpi/dietpi-software ]; then
    run_dietpi_software install 152
  else
    apt_install avahi-daemon
  fi
fi

if ! dpkg -s cockpit >/dev/null 2>&1; then
  echo "Installerar Cockpit."
  apt_install cockpit
fi
if ! grep -Rqs '^[[:space:]]*UrlRoot[[:space:]]*=' /etc/cockpit 2>/dev/null; then
  python3 - << 'PY'
from pathlib import Path
path = Path("/etc/cockpit/cockpit.conf")
text = path.read_text() if path.exists() else ""
lines = text.splitlines()
if any(line.strip().startswith("UrlRoot") for line in lines):
    raise SystemExit(0)
out = []
inserted = False
for line in lines:
    out.append(line)
    if line.strip() == "[WebService]" and not inserted:
        out.append("UrlRoot = /console")
        out.append("ProtocolHeader = X-Forwarded-Proto")
        inserted = True
if not inserted:
    if out and out[-1] != "":
        out.append("")
    out.append("[WebService]")
    out.append("UrlRoot = /console")
    out.append("ProtocolHeader = X-Forwarded-Proto")
path.parent.mkdir(parents=True, exist_ok=True)
path.write_text("\n".join(out) + "\n")
PY
fi
systemctl enable --now cockpit.socket
systemctl try-restart cockpit.socket >/dev/null 2>&1 || true

installed_rustdesk=$(dpkg-query -W -f '${Version}' rustdesk 2>/dev/null || true)
case $installed_rustdesk in
  "$RUSTDESK_VERSION"|"$RUSTDESK_VERSION"-*) ;;
  *)
    echo "Installerar RustDesk $RUSTDESK_VERSION."
    debdir=$(mktemp -d)
    deb=$debdir/rustdesk.deb
    curl -fsSL "https://github.com/rustdesk/rustdesk/releases/download/${RUSTDESK_VERSION}/rustdesk-${RUSTDESK_VERSION}-aarch64.deb" -o "$deb" || {
      rm -rf "$debdir"
      exit 1
    }
    apt_install --allow-downgrades "$deb"
    rm -rf "$debdir"
    ;;
esac

echo "Installerar OpenPLC Runtime $OPENPLC_RUNTIME_VERSION."
plc=$(mktemp)
curl -fsSL "https://raw.githubusercontent.com/Autonomy-Logic/openplc-runtime/${OPENPLC_INSTALLER_REF}/scripts/install-docker.sh" -o "$plc"
bash "$plc" --runtime-version "$OPENPLC_RUNTIME_VERSION" --bootloader-version "$OPENPLC_BOOTLOADER_VERSION" --yes
rm -f "$plc"

sh "$HERE/install.sh"

mkdir -p /etc/melacs /usr/local/sbin
printf '%s\n%s\n' "$tag" "$sha" > /etc/melacs/release
cat > /usr/local/sbin/melacs-update << 'EOF'
#!/bin/sh
set -eu
tmp=$(mktemp)
trap 'rm -f "$tmp"' EXIT
curl -fsSL https://raw.githubusercontent.com/stefanmaston/SEAS-Melacs-Github-20260408/main/Application_PLC/rock5b/melacs-install.sh -o "$tmp"
bash "$tmp"
EOF
chmod 755 /usr/local/sbin/melacs-update

echo
echo "Melacs $tag är installerad."
echo "Uppdatera senare med melacs-update."
