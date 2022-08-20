FROM debian:buster

RUN apt update
RUN apt upgrade -y

COPY ./entrypoint.sh /
RUN chmod +x /entrypoint.sh

EXPOSE 9000

ENTRYPOINT [ "/entrypoint.sh" ]

