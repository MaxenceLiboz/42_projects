DOCKER_IMAGE_LIST		=	$(shell docker images -aq)
DOCKER_CONTAINER_LIST	=	$(shell docker ps -aq)


up:
	docker-compose up --build -d 
run-m:
	docker-compose run mariadb

down:
	docker-compose down

clean:
	@if [ -n "$(DOCKER_CONTAINER_LIST)" ]; \
	then \
		docker rm -f $(DOCKER_CONTAINER_LIST); \
		echo "[ REMOVING CONTAINER ]"; \
	fi

	@if [ -n "$(DOCKER_IMAGE_LIST)" ]; \
	then \
		docker rmi $(DOCKER_IMAGE_LIST); \
		echo "[ REMOVING IAMGES ]"; \
	fi

	@# @if [ -n $(DOCKER_VOLUME_LIST) ]; \
	# then \
	# 	docker volume rm $(DOCKER_VOLUME_LIST); \
	# 	echo "[ REMOVING VOLUMES ]"; \
	# fi

	@# @if [ -n $(DOCKER_NETWORK_LIST) ]; \
	then \
		docker network rm $(DOCKER_NETWORK_LIST); \
		echo "[ REMOVING NETWORK ]"; \
	fi