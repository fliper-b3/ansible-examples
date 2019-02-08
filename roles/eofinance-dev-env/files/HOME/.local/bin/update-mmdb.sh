#!/bin/bash

################################## Config #####################################
DESTPATH="$HOME/.local/share/maxmind"
#DESTPATH="/tmp/maxmind/latest"
URL="https://download.maxmind.com/app/geoip_download?suffix=tar.gz&license_key=tj82yXb3Ws7W&edition_id="
###############################################################################

mkdir -p "${DESTPATH}.new"
cd "${DESTPATH}.new"
L=City
curl -s "${URL}GeoIP2-${L}" | tar -xz --wildcards --strip-components=1 "GeoIP2-${L}*/GeoIP2-${L}.mmdb"
RCCITY=$?
L=Country
curl -s "${URL}GeoIP2-${L}" | tar -xz --wildcards --strip-components=1 "GeoIP2-${L}*/GeoIP2-${L}.mmdb"
RCCOUNTRY=$?

if [ "$RCCITY" == 0 -a "$RCCOUNTRY" == 0 ] ; then
    [ -d "${DESTPATH}" ] && mv "${DESTPATH}" "${DESTPATH}.old"
    RCLATEST=$?
    mv "${DESTPATH}.new" "${DESTPATH}"
    [ "$RCLATEST" == 0 ] && rm -fr "${DESTPATH}.old"
fi
