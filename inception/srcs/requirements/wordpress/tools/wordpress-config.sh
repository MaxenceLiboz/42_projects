#!/bin/bash

if [ ! -f "/var/www/wordpress/wp-config.php" ]; then
	# wait for mariadb to be configured and ready to use
	while ! mariadb --host=${MARIADB_HOST} --user=${MARIADB_USERNAME} --password=${MARIADB_PASSWORD} ${MARIADB_DATABASE} &> /dev/null; do
		echo "Waiting on mariadb config"
		sleep 2
	done

	echo "Start wordpress config"
	mkdir -p /var/www/mliboz.42.fr && mv /wordpress-install/* /var/www/mliboz.42.fr/ && rm -rf /wordpress-install
	wp core config --dbname=${MARIADB_DATABASE} --dbuser=${MARIADB_USERNAME} --dbpass=${MARIADB_PASSWORD} --dbhost=${MARIADB_HOST}:${MARIADB_PORT} --allow-root --skip-check
	wp core install --url=${DOMAIN_NAME} --title=Inception --admin_user=${WORDPRESS_ADMIN_USER} --admin_password=${WORDPRESS_ADMIN_PASSWORD} --admin_email=${WORDPRESS_ADMIN_EMAIL} --allow-root
	wp user create ${WORDPRESS_CORRECTOR_USER} ${WORDPRESS_CORRECTOR_EMAIL} --user_pass=${WORDPRESS_CORRECTOR_PASSWORD} --role=author --allow-root
	wp theme activate twentytwenty --allow-root

	echo "Wordpress config done"
else
	echo "Wordpress already configured"
fi

# Have to first initilize php-fpm
/etc/init.d/php7.3-fpm start
/etc/init.d/php7.3-fpm stop

php-fpm7.3 -F
