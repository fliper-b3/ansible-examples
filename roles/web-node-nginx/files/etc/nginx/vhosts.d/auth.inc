add_header Access-Control-Allow-Origin *;
access_log  /var/log/nginx/auth-access.log advanced;

error_log   /var/log/nginx/auth-error.log;

include conf.d/gzip.inc;
include conf.d/cf-real-ip.inc;

keepalive_timeout   300s;

location    / {
    expires epoch;

    proxy_pass http://app-gunicorn;
    proxy_http_version 1.1;
    proxy_buffering on;
    proxy_buffer_size 64k;
    proxy_buffers 8 32k;
    proxy_busy_buffers_size 128k;
    proxy_set_header X-Real-IP $remote_addr;
    proxy_set_header Host $host;
    proxy_set_header X-Forwarded-Proto $scheme;
    proxy_set_header X-Forwarded-For $remote_addr;
    proxy_set_header X-Forwarded-Port $server_port;
    proxy_read_timeout 180s;
    client_max_body_size 100m;
}
