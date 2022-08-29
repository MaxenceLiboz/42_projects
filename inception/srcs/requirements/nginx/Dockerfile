FROM debian:buster

RUN apt update
RUN apt upgrade -y
RUN apt install -y nginx

WORKDIR /etc/nginx

COPY ./conf/default ./sites-available/
COPY ./conf/fastcgi_params /etc/nginx/

EXPOSE 443

ENTRYPOINT [ "nginx", "-g", "daemon off;" ]