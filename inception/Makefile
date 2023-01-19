DOCKER_NETWORK		=	$(shell docker network ls -q | grep inception-network)

all : up

############################## TO DO LIST #####################################
#
# Add change for the /etc/hosts => localhost to mliboz.42.fr
# Make sure the volumes point as the subject demand 
# Make sure it is working on a vm 
#
#
############################## TO DO LIST #####################################
up:
	docker compose -f ./srcs/docker-compose.yml up --build -d 

run-mariadb:
	docker exec -it mariadb-container bash

run-wordpress:
	docker exec -it wordpress-container bash

run-nginx:
	docker exec -it nginx-container bash

down:
	docker compose -f ./srcs/docker-compose.yml down

stop:
	docker compose -f ./srcs/docker-compose.yml stop

reload: down up

clean-volumes:
	# Cleaning volumes
	@docker volume rm -f mariadb-volume 2> /dev/null
	@docker volume rm -f wordpress-volume 2> /dev/null

clean:
	# Cleaning containers
	@docker rm -f mariadb-container 2> /dev/null
	@docker rm -f wordpress-container 2> /dev/null
	@docker rm -f nginx-container 2> /dev/null

	# Cleaning images
	@docker rmi -f mariadb-image 2> /dev/null
	@docker rmi -f wordpress-image 2> /dev/null
	@docker rmi -f nginx-image 2> /dev/null

fclean: clean

	# Cleaning volumes
	@docker volume rm -f mariadb-volume 2> /dev/null
	@docker volume rm -f wordpress-volume 2> /dev/null

	# Cleaning network
	@if [ -n "$(DOCKER_NETWORK)" ]; then\
		docker network rm inception-network; \
	fi

re:	fclean all 