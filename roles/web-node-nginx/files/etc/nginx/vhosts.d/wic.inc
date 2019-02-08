access_log  /var/log/nginx/wic-access.log advanced;
error_log   /var/log/nginx/wic-error.log;

location    / {
    proxy_pass http://wic-dl;
    proxy_http_version 1.1;
    proxy_set_header Connection "";
    proxy_set_header Host $host;
    proxy_set_header X-Forwarded-Proto $scheme;
    proxy_set_header X-Forwarded-For $remote_addr;
    proxy_set_header X-Forwarded-Port $server_port;
}
location /macos/ {
    proxy_pass http://wic-mac;
}
