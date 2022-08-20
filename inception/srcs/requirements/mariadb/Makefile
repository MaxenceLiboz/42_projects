DOCKER_IMAGE_LIST		=	$(shell docker images -a -q)
DOCKER_CONTAINER_LIST	=	$(shell docker ps -a -q)
# DOCKER_VOLUME_LIST		=	$(shell docker volume ls -q)
# DOCKER_NETWORK_LIST		=	$(shell docker network ls -q | tail -n +3)

all: build run

build:
	docker build -t mariadb_v1 .

run:
	docker run -it mariadb_v1

clean:
	@if [ -n $(DOCKER_CONTAINER_LIST) ]; \
	then \
		docker rm -f $(DOCKER_CONTAINER_LIST); \
		echo "[ REMOVING CONTAINER ]"; \
	fi

	@if [ -n $(DOCKER_IMAGE_LIST) ]; \
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

re: clean all