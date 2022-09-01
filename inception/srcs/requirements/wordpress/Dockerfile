FROM debian:buster

RUN apt update
RUN apt upgrade -y
RUN apt install -y wget php7.3 php-fpm php-mysql mariadb-client

# Get the config files
COPY ./conf/php.ini /etc/php/7.3/fpm/
COPY ./conf/www.conf /etc/php/7.3/fpm/pool.d/

# Copy the wordpress-config script and give permission to run
COPY ./tools/wordpress-config.sh /tmp/
RUN chmod +x /tmp/wordpress-config.sh


# Download wordpress
RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
RUN	chmod +x wp-cli.phar
RUN mv wp-cli.phar /usr/local/bin/wp
RUN mkdir -p /var/www/
RUN	wp core download --path=/wordpress-install --allow-root

EXPOSE 9000

WORKDIR /var/www/mliboz.42.fr
ENTRYPOINT [ "/tmp/wordpress-config.sh" ]
# ENTRYPOINT [ "tail", "-f", "/dev/null" ]



