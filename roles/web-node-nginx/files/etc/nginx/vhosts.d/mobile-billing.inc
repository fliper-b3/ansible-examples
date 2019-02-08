access_log  /var/log/nginx/mobile-billing-access.log advanced;
error_log   /var/log/nginx/mobile-billing-error.log;

include conf.d/gzip.inc;
include conf.d/cf-real-ip.inc;

add_header Access-Control-Allow-Origin $cors_header;

index index.html;
expires epoch;

location /favicon.ico {
    error_log off;
    access_log off;
}
