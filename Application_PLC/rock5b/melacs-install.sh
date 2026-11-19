#!/bin/sh
# Installera eller uppdatera Melacs SEAS på DietPi.
# Körs som root efter DietPi:s vanliga första start:
#   curl -fsSL https://raw.githubusercontent.com/stefanmaston/SEAS-Melacs-Github-20260408/main/Application_PLC/rock5b/melacs-install.sh | bash
# Samma kommando hämtar en ny version när en GitHub-release är publicerad.
set -eu

REPO=stefanmaston/SEAS-Melacs-Github-20260408
SRC=/opt/melacs-src
STAMP=/etc/melacs/release

# Hela skriptet ligger i en funktion så att ett anrop via curl | bash
# läser färdigt filen innan något annat rör stdin.
main() {
  if [ "$(id -u)" -ne 0 ]; then
    echo "Kör kommandot som root." >&2
    exit 1
  fi
  if [ "$(uname)" != "Linux" ]; then
    echo "Melacs installeras på DietPi." >&2
    exit 1
  fi
  if [ "$(uname -m)" != "aarch64" ]; then
    echo "Melacs-paketet är för Rock 5B (aarch64)." >&2
    exit 1
  fi
  if [ ! -f /boot/dietpi/.version ] && [ ! -f /DietPi/dietpi/.version ]; then
    echo "Kör det här efter att DietPi är installerad med Balena Etcher och första starten är klar." >&2
    exit 1
  fi

  if ! command -v git >/dev/null 2>&1 || ! command -v curl >/dev/null 2>&1; then
    DEBIAN_FRONTEND=noninteractive apt-get update -qq
    DEBIAN_FRONTEND=noninteractive apt-get install -y git curl ca-certificates
  fi

  tmp=$(mktemp)
  code=$(curl -sS -o "$tmp" -w '%{http_code}' -H "Accept: application/vnd.github+json" \
    "https://api.github.com/repos/${REPO}/releases/latest") || {
    rm -f "$tmp"
    echo "Kunde inte nå GitHub." >&2
    exit 1
  }
  if [ "$code" = "404" ]; then
    rm -f "$tmp"
    echo "Ingen Melacs-release är publicerad. Det finns ingen version att installera." >&2
    exit 1
  fi
  if [ "$code" != "200" ]; then
    rm -f "$tmp"
    echo "GitHub svarade $code när Melacs-releasen skulle läsas." >&2
    exit 1
  fi
  tag=$(sed -n 's/.*"tag_name"[[:space:]]*:[[:space:]]*"\([^"]*\)".*/\1/p' "$tmp" | head -n 1)
  rm -f "$tmp"
  case $tag in
    v[0-9]*) ;;
    *)
      echo "GitHub lämnade inget versionsnummer." >&2
      exit 1
      ;;
  esac
  case $tag in
    *[!A-Za-z0-9._-]*)
      echo "Versionsnumret kan inte användas: $tag" >&2
      exit 1
      ;;
  esac

  current=""
  if [ -f "$STAMP" ]; then
    current=$(awk 'NR==1 { gsub(/[[:space:]]/, ""); print; exit }' "$STAMP")
  fi
  if [ "$current" = "$tag" ]; then
    echo "Melacs $tag är redan installerad."
    echo "http://melacs.local/"
    exit 0
  fi

  url="https://github.com/${REPO}.git"
  export GIT_TERMINAL_PROMPT=0
  if [ -d "$SRC" ] && [ ! -d "$SRC/.git" ]; then
    echo "$SRC finns redan och är inte en Melacs-hämtning. Flytta katalogen och kör kommandot igen." >&2
    exit 1
  fi
  if [ -d "$SRC/.git" ]; then
    origin=$(git -C "$SRC" remote get-url origin)
    case $origin in
      *"$REPO"*) ;;
      *)
        echo "$SRC pekar inte på $REPO. Flytta katalogen och kör kommandot igen." >&2
        exit 1
        ;;
    esac
    if [ -n "$(git -C "$SRC" status --porcelain)" ]; then
      echo "$SRC har lokala ändringar. Flytta dem innan uppdatering." >&2
      exit 1
    fi
    git -C "$SRC" fetch --depth 1 origin "refs/tags/${tag}:refs/tags/${tag}"
    git -C "$SRC" checkout --detach "$tag"
  else
    git clone --depth 1 --branch "$tag" "$url" "$SRC"
  fi

  export MELACS_RELEASE_TAG="$tag"
  MELACS_RELEASE_SHA=$(git -C "$SRC" rev-parse HEAD)
  export MELACS_RELEASE_SHA
  sh "$SRC/Application_PLC/rock5b/install-box.sh"
}

main "$@"
