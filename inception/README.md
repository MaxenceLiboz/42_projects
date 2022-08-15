Notes about: https://www.youtube.com/watch?v=2lU9zdrs9bM

FROM command:
It define the base image to use to start building the process
ex: FROM alpine:latest

RUN command:
Take as argument a command that is going to be run to the image
Can be use to run shell command, but it is run while building the image
ex: RUN apt-get update

CMD command:
Take as argument a command that is going to be run in the docker, but this one
is not executed while building the image
ex: CMD echo "Hello world"

ENTRYPOINT command:
Take as argument a command that is going to be run instantly after the image is build
It can overwrite a CMD command
ex: ENTRYPOINT hello_world.sh

ADD or COPY command:
Use to add or copy files from the source on the host into the container's filesystem at the set destination
ex: COPY app/ container_app/

ENV command:
it is used to set the environment variables, these variable consist of "key value" 
pairs which can be accessed within the container by scripts and application
ex: ENV CONTAINER 4

WORKDIR command:
it is used to set where the command defined with CMD is gonna be executed
ex: WORKDIR ~/path WORKDIR ~/

EXPOSE command:
it is used to associate a specified port to enable networking between the running process
inside the container and the outside world
ex: EXPOSE 8080

MAINTAINER command:
Non-excuting command that declares the author of the image
Must be used after the FROM command
ex: MAINTAINER mliboz

USER command:
didn't really understand the use cases

VOLUME command:
Access from the container to a directory on the host machine in order for the container to store his files
Can be share with multiple container
ex: VOLUME ["~/container_holder"]

EXAMPLE DOCKERFILE for APACHE:

FROM ubuntu:12.04

MAINTAINER mliboz

RUN apt-get update && apt-get install -y apache2 && apt-get clean && rm -rf /var/lib/apt/lists/*

ENV APACHE_RUN_USER www-data
ENV APACHE_RUN_GROUP www-data
ENV APACHE_LOG_DIR /var/log/apache2

EXPOSE 80

CMD ["/usr/sbin/apache2", "-D", "FOREGROUND"]


TO BUILD A DOCKER IMAGE:
docker build -t DOCKER_NAME PATH

TO RUN THE APPLICATION CREATED WITH THE DOCKER CREATED:
docker run -p PORT DOCKER_NAME