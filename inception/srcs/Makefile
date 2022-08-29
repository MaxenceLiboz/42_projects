DOCKER_IMAGE_LIST		=	$(shell docker images -aq)
DOCKER_CONTAINER_LIST	=	$(shell docker ps -aq)
DOCKER_VOLUME_LIST		=	$(shell docker volume ls -q)
# DOCKER_NETWORK_LIST		=	$(shell docker network ls -q | tail -n +3)

all : up

up:
	docker-compose up --build -d 
run-mariadb:
	docker exec -it mariadb-container bash
run-wordpress:
	docker exec -it wordpress-container bash

run-nginx:
	docker exec -it nginx-container bash

down:
	docker-compose down

clean-volumes:
	@if [ -n "$(DOCKER_VOLUME_LIST)" ]; \
	then \
		echo "[ REMOVING VOLUMES ]"; \
		docker volume rm $(DOCKER_VOLUME_LIST); \
	fi

fclean:
	@if [ -n "$(DOCKER_CONTAINER_LIST)" ]; \
	then \
		echo "[ REMOVING CONTAINER ]"; \
		docker rm -f $(DOCKER_CONTAINER_LIST); \
	fi

	@if [ -n "$(DOCKER_IMAGE_LIST)" ]; \
	then \
		echo "[ REMOVING IAMGES ]"; \
		docker rmi $(DOCKER_IMAGE_LIST); \
	fi

	@if [ -n "$(DOCKER_VOLUME_LIST)" ]; \
	then \
		echo "[ REMOVING VOLUMES ]"; \
		docker volume rm $(DOCKER_VOLUME_LIST); \
	fi

	@# @if [ -n $(DOCKER_NETWORK_LIST) ]; \
	then \
		docker network rm $(DOCKER_NETWORK_LIST); \
		echo "[ REMOVING NETWORK ]"; \
	fi

re:	fclean all 