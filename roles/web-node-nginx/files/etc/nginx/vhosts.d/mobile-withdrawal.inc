access_log  /var/log/nginx/mobile-withdrawal-access.log advanced;
error_log   /var/log/nginx/mobile-withdrawal-error.log;

include conf.d/gzip.inc;

add_header Cache-Control "no-cache, no-store, must-revalidate";
