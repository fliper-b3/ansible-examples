include conf.d/gzip.inc;

keepalive_timeout   70;

rewrite ^/demo/(.*) /$1 redirect;

location / {
    try_files $uri @site-ng;
}
location @site-ng {
    proxy_pass  http://$site_ng_upstream;
    proxy_set_header Host $host;
    proxy_set_header X-Forwarded-Proto $scheme;
    proxy_set_header X-Forwarded-For $remote_addr;
    proxy_set_header X-Forwarded-Port $server_port;
    proxy_buffer_size 256k;
    proxy_buffers 16 256k;
    proxy_busy_buffers_size 256k;
    add_header Cache-Control "no-store";
}

location ^~ /images/trade_result/ {
    alias /home/expert/.cache/apps/site-ng/tr_cache/;
    try_files $uri @tr_cache;
}
location @tr_cache {
    # Prevent cycling through upstream
    if ($http_file_does_not_exist) {
        return 404;
    }
    proxy_set_header File-Does-Not-Exist True;
    proxy_set_header Host $host;
    proxy_pass https://web-https;
    proxy_next_upstream error timeout http_404;
}

location /ico/m {
    alias /home/expert/apps/ico-mobile;
}
location ^~ /amp {
    alias /home/expert/apps/amp/dist;
}
# facebook-domain-verification
location = /5eq4yewmg14vbem8ebhhxls6m5uh1e.html {
    return 200 "5eq4yewmg14vbem8ebhhxls6m5uh1e";
}
# nganloung billing QA
location = /nganluong_f4022c8f154c0216f5b13001b725eef0.html {
    return 200 "f4022c8f154c0216f5b13001b725eef0";
}
# nganloung billing
location = /nganluong_1b8f5e028fb03163735137360c4dcf61.html {
    return 200 "1b8f5e028fb03163735137360c4dcf61";
}
