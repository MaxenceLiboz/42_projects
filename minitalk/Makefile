SRCS		=	./srcs/ft_itoa_base.c				\
				./srcs/signal_handlers.c
				
OBJS		=	${SRCS:.c=.o}

INCLUDES	=	./libft/includes/libft.h			\
				./includes/minitalk.h

CC			= 	gcc

CFLAGS		= 	-Wall -Wextra -Werror #-g -fsanitize=address

LIBINCLUDES	=	-Iincludes  -Ilibft/includes

LIBS		=	libft.a 							\
				${LIB}

LIB			=	libmtlk.a

CLIENT		=	client

SERVER		=	server

RM			=	rm -f

all:		libft server client

%.o: 		%.c	${INCLUDES}
			${CC} ${CFLAGS} ${LIBINCLUDES} -c $< -o $@

$(LIB):		${OBJS} ${INCLUDES}
			ar rcs ${LIB} ${OBJS}

libft:		${INCLUDES}
			make -C libft
			cp libft/libft.a ./

client:		client.c ${LIBS}
			$(CC) ${CFLAGS} ${LIBINCLUDES} client.c ${LIBS} -o ${CLIENT}

server:		server.c ${LIBS}
			$(CC) ${CFLAGS} ${LIBINCLUDES} server.c ${LIBS} -o ${SERVER}

clean:
			${RM} ${OBJS}
			make clean -C libft

fclean:		clean
			make fclean -C libft
			${RM} ${LIB} ${CLIENT} ${SERVER} ${LIBS}

re:			fclean all

.PHONY: 	all clean fclean re run libft