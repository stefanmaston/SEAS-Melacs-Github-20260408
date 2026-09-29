#!/bin/sh
# Lägg Modbus-kartan mot Melacs i en OpenPLC Runtime v4 som redan kör.
# Kartan skrivs inte över ett program som editorn senare laddar upp.
set -eu
HERE=$(CDPATH= cd -- "$(dirname "$0")" && pwd)
SRC="$HERE/modbus_master.json"
COPIED=0

copy_into() {
    dest=$1
    mkdir -p "$(dirname "$dest")"
    cp "$SRC" "$dest"
    echo "skrev $dest"
    COPIED=1
}

if command -v docker >/dev/null 2>&1; then
    for name in openplc-runtime openplc; do
        if docker ps --format '{{.Names}}' | grep -qx "$name"; then
            docker exec "$name" mkdir -p /workdir/core/generated/conf
            docker cp "$SRC" "$name:/workdir/core/generated/conf/modbus_master.json"
            echo "skrev $name:/workdir/core/generated/conf/modbus_master.json"
            COPIED=1
        fi
    done
fi

for dest in \
    /var/lib/openplc-runtime/conf/modbus_master.json \
    /var/lib/openplc-runtime/core/generated/conf/modbus_master.json \
    /workdir/core/generated/conf/modbus_master.json
do
    if [ -d "$(dirname "$dest")" ]; then
        copy_into "$dest"
    fi
done

if [ "$COPIED" -eq 0 ]; then
    echo "Ingen runtime-katalog hittades. Kör skriptet på Rock 5B när runtime är igång." >&2
    exit 1
fi
