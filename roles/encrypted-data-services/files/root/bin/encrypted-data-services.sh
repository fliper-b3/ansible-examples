#!/bin/bash

CONFIG="$HOME/.config/encrypted-data-services"

if ! [ -r "$CONFIG" ] ; then
echo "No config file '$CONFIG'"
mkdir -vp "$HOME/.config"
cat <<EOF > "$CONFIG"
# Config for encrypted-data-services.sh
# Services list as array
SRVLIST=(
"service"
"second-service"
)

# Comma separated filelds:
# "Encrypted device","Opened device","Mountpoint","mount options"
MNTLIST=(
"vg/home","home","/home","-o noatime"
)
EOF
echo "Default one created. Please edit it."
exit 1
fi

# shellcheck source=/dev/null
. "$CONFIG"

# Previous version compatibility
[ "$SRVLIST" == "" ] && read -r -a SRVLIST <<< "$SERVICES"
[ "$MNTLIST" == "" ] && MNTLIST=("${LIST[@]}")

open() {
    for V in "${MNTLIST[@]}" ; do
        IFS="," read -r CRYPTDEV DMNAME MOUNTPOINT OPTIONS <<<"$V"
        MOUNTDEV="/dev/mapper/$DMNAME"
        echo "Open encrypted partition"
        cryptsetup luksOpen "/dev/$CRYPTDEV" "$DMNAME" || exit 1
        echo "Mount $MOUNTDEV => $MOUNTPOINT"
        # shellcheck disable=SC2086
        mount $OPTIONS "$MOUNTDEV" "$MOUNTPOINT" || exit 1
    done
    echo "Starting services: ${SRVLIST[*]}"
    for SRV in "${SRVLIST[@]}" ; do
        service "$SRV" start || exit 1
    done
}
close() {
    for (( i=${#SRVLIST[@]}-1 ; i>=0 ; i-- )) ; do
        systemctl disable "${SRVLIST[i]}"
        service "${SRVLIST[i]}" stop || exit 1
    done
    for (( i=${#MNTLIST[@]}-1 ; i>=0 ; i-- )) ; do
        IFS="," read -r CRYPTDEV DMNAME MOUNTPOINT OPTIONS <<<"${MNTLIST[i]}"
        MOUNTDEV="/dev/mapper/$DMNAME"
        echo "Umount $MOUNTPOINT"
        umount "$MOUNTPOINT"
        echo "Close encrypted partition"
        cryptsetup close "$MOUNTDEV"
    done
}
usage() {
    echo "Usage: $0 <start|stop>"
}

case $1 in
    start)
        open
    ;;
    stop)
        close
    ;;
    *)
        usage
    ;;
esac
