access_log  /var/log/nginx/promo-access.log advanced;
error_log   /var/log/nginx/promo-error.log;

include conf.d/gzip.inc;

root /home/expert/apps/promo;

location = / {
    return 301 /easy/$is_args$args;
}
# Make request to wapi backend - hitcount
location / {
    if ( $arg_refid = "20313" ) { return 301 "http://404.com"; }
    add_header 'Access-Control-Allow-Origin' '*';
    if ($args ~ refid) {
         post_action /set_landing_hit;
    }
}
location = /set_landing_hit {
    proxy_pass http://r01sg-wapi/set_landing_hit$request_uri;
    proxy_set_header Host "wapi.expertoption.com";
    internal;
}
error_page 404 /;
location /birthday/ {
    proxy_pass http://front-assets-image/;
}
