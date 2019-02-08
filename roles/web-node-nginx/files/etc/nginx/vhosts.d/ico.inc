access_log  /var/log/nginx/ico-access.log advanced;
error_log   /var/log/nginx/ico-error.log;

location /web/ {
    proxy_pass http://eo-ico-fiat;
    proxy_http_version 1.1;
    proxy_set_header Host $host;
    proxy_set_header X-Real-IP $remote_addr;
}
location / {
    return 301 https://expertoption.com$request_uri;
}
