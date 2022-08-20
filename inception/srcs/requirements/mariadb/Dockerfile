FROM debian:buster

RUN apt update
RUN apt upgrade -y
RUN apt install mariadb-server -y

COPY ./entrypoint.sh /

RUN chmod +x /entrypoint.sh

EXPOSE 3306

ENTRYPOINT [ "/entrypoint.sh" ]
