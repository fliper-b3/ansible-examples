#!/bin/bash
databases=(electron erm ers ers_db ers_session minio_events_db)
hostname=`hostname`
# Dump DBs
date=`date +"%d.%m.%Y"`
rm -fr /var/lib/pgsql/10/backups/*
for db in "${databases[@]}"; do
    filename="/var/lib/pgsql/10/backups/${hostname}-${db}-${date}.sql"
    pg_dump -U postgres $1 >  $filename 
    if [[ $? -ne 0 ]]; then
        exit $?
    fi
done
exit 0