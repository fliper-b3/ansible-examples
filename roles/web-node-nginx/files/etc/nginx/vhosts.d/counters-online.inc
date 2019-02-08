location /counters/online.json {
    access_log  off;
    error_log   /var/log/nginx/counter-online-error.log;

    proxy_pass http://app-http;
    #proxy_set_header Host $host;
    proxy_set_header Host "img.expertoption.com";
    proxy_set_header X-Real-IP $remote_addr;
    proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
}
