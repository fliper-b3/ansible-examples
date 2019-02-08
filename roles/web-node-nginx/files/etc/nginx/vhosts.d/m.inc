access_log  /var/log/nginx/m-access.log advanced;
error_log   /var/log/nginx/m-error.log;

include conf.d/gzip.inc;

add_header Access-Control-Allow-Origin $cors_header;

location / {
    try_files $uri @m;
}
location @m {
    proxy_pass  http://$m_upstream;
    proxy_set_header Host $host;
    proxy_set_header X-Real-IP $remote_addr;
    proxy_buffer_size 256k;
    proxy_buffers 16 256k;
    proxy_busy_buffers_size 256k;
    add_header Cache-Control "no-store";
}
