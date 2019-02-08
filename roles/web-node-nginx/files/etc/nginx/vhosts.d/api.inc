access_log  /var/log/nginx/api-access.log advanced;
error_log   /var/log/nginx/api-error.log;

include conf.d/cf-real-ip.inc;
#expires off;
location    / {
    return 301 https://expertoptionasia.com;
}
location /d/ {
    proxy_pass http://transman/;
    proxy_set_header Host $host;
    proxy_set_header X-Real-IP $remote_addr;
    proxy_hide_header Access-Control-Allow-Origin;
    add_header Access-Control-Allow-Origin '*';
}
location /data/ {
    proxy_pass http://transman/data/;
    proxy_set_header Host $host;
    proxy_set_header X-Real-IP $remote_addr;
}
location /format/ {
    add_header Access-Control-Allow-Origin $cors_header;
    root /home/expert/apps/microservice;
    proxy_pass  http://127.0.0.1:8003;
    proxy_set_header Host $host;
    proxy_set_header X-Forwarded-For $remote_addr;
}
location /w/ {
    proxy_pass http://r01sg-wapi/;
    proxy_http_version 1.1;
    proxy_set_header Connection "";
    proxy_set_header Host $host;
    proxy_set_header X-Forwarded-For $remote_addr;
}
location /ico/ {
    limit_req zone=blue burst=5;
    limit_req_status 429;
    proxy_pass http://eo-ico-api/api/ico/;
    proxy_http_version 1.1;
    proxy_set_header Host $host;
    proxy_set_header X-Real-IP $remote_addr;
    client_max_body_size 50m;
}
location /ico/auth/ {
    limit_req zone=blue burst=5;
    limit_req_status 429;
    proxy_pass http://eo-ico-api/api/auth/;
    proxy_http_version 1.1;
    proxy_set_header Host $host;
    proxy_set_header X-Real-IP $remote_addr;
    client_max_body_size 50m;
}
location /ico/docs/ {
    limit_req zone=blue burst=5;
    limit_req_status 429;
    proxy_pass http://eo-ico-api/api/docs/;
    proxy_http_version 1.1;
    proxy_set_header Host $host;
    proxy_set_header X-Real-IP $remote_addr;
    client_max_body_size 50m;
}
location ~ "^/ico/(state|currency)/(.*)" {
    limit_req zone=blue burst=5;
    limit_req_status 429;
    proxy_cache pcache;
    #proxy_hide_header Expires;
    proxy_set_header Host $host;
    proxy_set_header X-Real-IP $remote_addr;
    proxy_pass http://eo-ico-api/api/ico/$1/$2;
}

location /flog/ {
    allow 10.0.0.0/8;
    allow 213.133.88.121;
    allow 81.4.145.214;
    allow 185.106.142.64/28;
    deny all;
    proxy_pass http://r01sg-flog/;
    proxy_set_header Host $host;
    proxy_set_header X-Forwarded-For $remote_addr;
}
error_page 429 @TooManyRequests;
location @TooManyRequests {
    add_header Retry-After 30;
    return 429 "Too Many Requests";
}
