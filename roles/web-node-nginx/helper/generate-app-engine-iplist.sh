#!/bin/bash

## Config #######
PREFIX="allow "
POSTFIX=";"
#################

ADDPP=$1

parse_txt_response() {
    SEARCHKEY=$1
    STRING=$2
    ADDPP=$3
    for V in $STRING ; do
        KEY=${V%%:*}
        VAL=${V##*:}
        if [ "$KEY" == "$SEARCHKEY" ] ; then
            if [ "$ADDPP" != "" ] ; then
                echo "${PREFIX}$VAL${POSTFIX}"
            else
                echo "$VAL"
            fi
        fi
    done
}

CURRENT_CLOUD_NETBLOCKS=$(dig +short _cloud-netblocks.googleusercontent.com @8.8.8.8 TXT)
CLOUD_NETBLOCK_DOMAINS=$(parse_txt_response include "$CURRENT_CLOUD_NETBLOCKS")

for V in $CLOUD_NETBLOCK_DOMAINS ; do
    CURRENT_CLOUD_NETLIST=$(dig +short "$V" @8.8.8.8 TXT)
    parse_txt_response ip4 "$CURRENT_CLOUD_NETLIST" $ADDPP
done
