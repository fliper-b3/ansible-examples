access_log  /var/log/nginx/verification-access.log advanced;
error_log   /var/log/nginx/verification-error.log;

include conf.d/gzip.inc;

location / {
    proxy_pass  http://nodsg-gunicorn;
    proxy_set_header Host $host;
    proxy_set_header X-Forwarded-For $remote_addr;
    proxy_set_header X-Forwarded-Port $server_port;
}
