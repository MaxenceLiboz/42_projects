#!/bin/bash

if [ ! -f "/var/www/wordpress/wp-config.php" ]; then
	# wait for mariadb to be configured and ready to use
	while ! mariadb --host=${MARIADB_HOST} --user=${MARIADB_USERNAME} --password=${MARIADB_PASSWORD} ${MARIADB_DATABASE} > /dev/null; do
		echo "Waiting on mariadb config"
		sleep 2
	done

	echo "Start wordpress config"

	mv /wordpress/ ./
	cd wordpress
	wp core config --dbname=${MARIADB_DATABASE} --dbuser=${MARIADB_USERNAME} --dbpass=${MARIADB_PASSWORD} --dbhost=${MARIADB_HOST}:${MARIADB_PORT} --allow-root --skip-check
	wp core install --url=localhost --title=Inception --admin_user=${WORDPRESS_ADMIN_USER} --admin_password=${WORDPRESS_ADMIN_PASSWORD} --admin_email=${WORDPRESS_ADMIN_EMAIL} --allow-root

	echo "Wordpress config done"
else
	echo "Wordpress already configured"
fi

# Have to first initilize php-fpm
/etc/init.d/php7.3-fpm start
/etc/init.d/php7.3-fpm stop

php-fpm7.3 -F
