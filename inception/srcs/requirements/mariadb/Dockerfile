FROM debian:buster

RUN apt update
RUN apt upgrade -y
RUN apt install mariadb-server -y

COPY ./tools/mariadb-config.sh /tmp/
COPY ./conf/50-server.cnf /etc/mysql/mariadb.conf.d/

RUN chmod +x /tmp/mariadb-config.sh

# EXPOSE 3306

ENTRYPOINT [ "/tmp/mariadb-config.sh" ]
