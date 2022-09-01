FROM debian:buster

ARG DOMAIN_NAME=mliboz.42.fr

RUN apt update
RUN apt upgrade -y
RUN apt install -y nginx openssl

WORKDIR /etc/nginx

COPY ./conf/${DOMAIN_NAME} ./sites-available/
COPY ./conf/fastcgi_params /etc/nginx/

COPY ./conf/${DOMAIN_NAME}.conf /tmp/

RUN mkdir /etc/certs
RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/certs/${DOMAIN_NAME}.key -out /etc/certs/${DOMAIN_NAME}.crt -config /tmp/${DOMAIN_NAME}.conf

RUN ln -s /etc/nginx/sites-available/${DOMAIN_NAME} /etc/nginx/sites-enabled/

EXPOSE 443

ENTRYPOINT [ "nginx", "-g", "daemon off;" ]