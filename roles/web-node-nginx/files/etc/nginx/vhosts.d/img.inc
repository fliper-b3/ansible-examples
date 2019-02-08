#access_log  /var/log/nginx/img-access.log advanced;
access_log off;
error_log   /var/log/nginx/img-error.log;

root /home/expert/.cache/nginx/ava;
expires max;
add_header Access-Control-Allow-Origin $cors_header;

# Location below must be before any NOT rounded images
location ~* "/rounded/(.*\.(jpg|jpeg|png|gif|webp))$" {
    proxy_cache pcache;
    proxy_cache_use_stale error timeout updating http_500 http_502 http_503 http_504;
    proxy_cache_lock on;
    proxy_ignore_headers Cache-Control;
    proxy_cache_valid 7d;
    proxy_pass http://10.176.0.188:8080/$1$is_args$args;
    proxy_set_header Host $host;
    #proxy_hide_header Access-Control-Allow-Origin;
}
# For comaptibility do resize only if had "w" argument
# And this location must be BEFORE legacy
location ~* \.(jpg|jpeg|png|gif|webp)$ {
    if ($http_image_filter_resize = "Get Origin Image") { return 460; }
    error_page 460 = @ava;
    if ($http_image_filter_resize) { return 461; }
    error_page 461 = @resize;
    if ($arg_w) { return 462; }
    if ($arg_h) { return 462; }
    error_page 462 = @resize-cache;

    try_files $uri @ava;
}
location @resize-cache {
    proxy_cache pcache;
    proxy_cache_use_stale error timeout updating http_500 http_502 http_503 http_504;
    proxy_cache_lock on;
    proxy_ignore_headers Cache-Control;
    proxy_cache_valid 7d;
    proxy_pass https://127.0.0.1;
    proxy_set_header Host $host;
    proxy_set_header Image-Filter-Resize "$arg_w x $arg_h";
    proxy_hide_header Access-Control-Allow-Origin;
}
location @resize {
    if ($arg_w = "") { set $arg_w -; }
    if ($arg_h = "") { set $arg_h -; }
    image_filter resize $arg_w $arg_h;
    image_filter_buffer 16M;
    proxy_pass https://127.0.0.1;
    proxy_set_header Host $host;
    proxy_set_header Image-Filter-Resize "Get Origin Image";
    proxy_hide_header Access-Control-Allow-Origin;
}

location ~* \.(bmp|tiff|jpg|jpeg|png|gif|webp)$ {
    # This location must be deleted if log below is empty
    access_log  /var/log/nginx/img-legacy-access.log advanced;
    try_files $uri @ava;
}
location @ava {
    proxy_pass http://app-http;
    proxy_set_header Host $host;
    proxy_set_header X-Real-IP $remote_addr;
    proxy_buffer_size 16k;
    proxy_buffers 32 16k;
    proxy_ignore_headers "Cache-Control" "Expires";
    proxy_store on;
    proxy_store_access user:rw group:rw all:r;
}
include vhosts.d/counters-online.inc;
location / {
    return 301 https://expertoption.com;
}
