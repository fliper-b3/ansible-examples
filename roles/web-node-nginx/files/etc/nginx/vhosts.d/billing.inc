access_log  /var/log/nginx/billing-access.log advanced;
error_log   /var/log/nginx/billing-error.log;

include conf.d/gzip.inc;
include conf.d/cf-real-ip.inc;

location  /web {
    add_header 'Access-Control-Allow-Origin' '*';
    add_header 'Access-Control-Allow-Credentials' 'true';
    add_header 'Access-Control-Allow-Methods' 'GET, POST, OPTIONS';
    add_header 'Access-Control-Allow-Headers' 'DNT,X-CustomHeader,Keep-Alive,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type';

    proxy_pass  http://app-gunicorn;
    proxy_http_version 1.1;
    proxy_set_header Upgrade $http_upgrade;
    proxy_set_header Connection "upgrade";
    proxy_set_header Host $host;
    proxy_set_header X-Forwarded-Proto $scheme;
    proxy_set_header X-Forwarded-For $remote_addr;
    proxy_set_header X-Forwarded-Port $server_port;
    proxy_set_header X-Request-Start $msec;

    client_max_body_size 100m;
}

location = /favicon.ico {
    alias /home/expert/apps/site-ng/dist/client/favicon.ico;
}
