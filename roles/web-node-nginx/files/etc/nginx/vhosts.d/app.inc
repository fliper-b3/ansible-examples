access_log  /var/log/nginx/app-access.log advanced;
error_log   /var/log/nginx/app-error.log;

include conf.d/gzip.inc;
include conf.d/cf-real-ip.inc;

keepalive_timeout   70;
add_header Access-Control-Allow-Origin $cors_header;

location / {
    if ( $arg_refid = "20313" ) { return 301 "http://404.com"; }
    try_files $uri @app;
}
location @app {
    proxy_pass  http://$app_upstream;
    proxy_http_version 1.1;
    proxy_set_header Host $host;
    proxy_set_header X-Forwarded-For $remote_addr;
    proxy_set_header X-Real-IP $msec;
}
# Safari push
location /v1/pushPackages/ {
    proxy_pass  http://nodsg-gunicorn;
    proxy_set_header Host $host;
    proxy_set_header X-Forwarded-Proto $scheme;
    proxy_set_header X-Forwarded-For $remote_addr;
    proxy_set_header X-Forwarded-Port $server_port;
}
location /billing/card-payment {
    alias /home/expert/apps/card-payment;
}
location /web/payment/ {
    proxy_pass http://eo-ico-fiat;
    proxy_http_version 1.1;
    proxy_set_header Host $host;
    proxy_set_header X-Real-IP $remote_addr;
}
