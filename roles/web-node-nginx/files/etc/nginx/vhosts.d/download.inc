access_log  /var/log/nginx/download-access.log advanced;
error_log   /var/log/nginx/download-error.log;

include conf.d/gzip.inc;

root /home/expert/apps/download;
limit_conn addr 2;
#limit_rate_after 10m;
limit_rate 1m;

location / {
    try_files $uri @download;
}
location @download {
    # Prevent cycling through upstream
    if ($http_file_does_not_exist) {
        return 404;
    }
    proxy_set_header File-Does-Not-Exist True;
    proxy_set_header Host $host;
    proxy_pass https://web-https;
    proxy_next_upstream error timeout http_404;
}
