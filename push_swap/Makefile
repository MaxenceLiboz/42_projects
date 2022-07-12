SRCS		=	srcs/arg_managment.c				\
				srcs/swap.c							\
				srcs/push.c							\
				srcs/rotate.c						\
				srcs/reverse_rotate.c				\
				srcs/ft_lstsorted.c					\
				srcs/index_functions.c				\
				srcs/small_sort.c					\
				srcs/mid_sort.c						\
				srcs/big_sort.c						\
				srcs/radix.c						\
				srcs/ft_atoll.c						\
				
OBJS		=	${SRCS:.c=.o}

INCLUDES	=	./includes/push_swap.h				\
				./libft/includes/libft.h			\

CC			= 	gcc

CFLAGS		= 	-Wall -Wextra -Werror #-g #-fsanitize=address

LIBINCLUDES	=	-Iincludes -Ilibft/includes

LIBS		=	libft.a								\
				${LIB}

LIB			=	libpswp.a

EXEC		=	push_swap

RM			=	rm -f


all:		libft ${EXEC} main.c

%.o: 		%.c	${INCLUDES}
			${CC} ${CFLAGS} ${LIBINCLUDES} -c $< -o $@

$(LIB):		${OBJS} ${INCLUDES}
			ar rcs ${LIB} ${OBJS}

libft:		${INCLUDES}
			make -C libft

${EXEC}:	main.c ${LIBS}
			$(CC) ${CFLAGS} ${LIBINCLUDES} main.c ${LIBS} -o ${EXEC}

clean:
			${RM} ${OBJS}
			make clean -C libft

fclean:		clean
			make fclean -C libft
			${RM} ${LIB} ${EXEC} ${LIBS}

re:			fclean all

.PHONY: 	all clean fclean re libft