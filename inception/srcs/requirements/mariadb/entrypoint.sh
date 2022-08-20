#!/bin/bash

# Start the mysql to configure it
service mysql start

# SCRIPT TO CREATE THE DATABASE AND CREATE A PASSWORD FOR ROOT
# CREATE A DATABASE
mysql -uroot -e "CREATE DATABASE ${MARIADB_DATABASE};"
# CREATE A DATABASE USER
mysql -uroot -e "CREATE USER ${MARIADB_USERNAME}@localhost IDENTIFIED BY '${MARIADB_PASSWORD}';"
# ALLOW ACCESS TO ANY OTHER COMPUTER/DOCKER WITH % DOCS => https://www.daniloaz.com/en/how-to-create-a-user-in-mysql-mariadb-and-grant-permissions-on-a-specific-database/
mysql -uroot -e "GRANT USAGE ON *.* TO '${MARIADB_USERNAME}'@'%' IDENTIFIED BY '${MARIADB_PASSWORD}';"
# SET A PASSWORD FOR THE ROOT USER
mysql -uroot -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${MARIADB_ROOT_PASSWORD}';"

# COPY THE ROOT PASSWORD INTO THE CONF TO BE ABLE TO STOP AND RUN MYSQL SERVICES
sed -i "s/password =/password = ${MARIADB_ROOT_PASSWORD}/" /etc/mysql/debian.cnf

# STOP MYSQL SERVICE TO RUN MYSQLD_SAFE INSTEAD
service mysql stop

# FOR NOW I AM USING BASH TO BE ABLE TO ACCESS THE CONTAINER, WILL HAVE TO USE MYSQLD_SAFE LATER ON
# mysqld_safe
bash


# NOTES
# TO SHOW USER USE => SELECT User FROM mysql.user;
# TO SHOW USER GRANTS => SHOW GRANTS FOR [ username ];
