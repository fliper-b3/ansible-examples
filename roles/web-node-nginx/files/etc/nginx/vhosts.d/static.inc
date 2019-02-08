access_log  /var/log/nginx/static-access.log advanced;
error_log   /var/log/nginx/static-error.log;

include conf.d/gzip.inc;
include conf.d/cf-real-ip.inc;

root /home/expert/apps/static;
add_header Access-Control-Allow-Origin *;
location / {
    try_files $uri @static;
}
location @static {
    proxy_pass https://10.176.2.221;
    proxy_set_header Host $host;
    proxy_set_header X-Real-IP $remote_addr;
    proxy_buffer_size 16k;
    proxy_buffers 32 16k;

    #proxy_store on;
    #proxy_store_access user:rw group:rw all:r;
    
    proxy_cache static;
    proxy_cache_use_stale error timeout updating http_404 http_500 http_502 http_503 http_504;
    proxy_cache_background_update on;
    proxy_cache_revalidate on;
    proxy_cache_valid 30s;
}
