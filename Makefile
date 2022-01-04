SRCS		=	srcs/create_prompt.c
				
OBJS		=	${SRCS:.c=.o}

INCLUDES	=	./includes/minishell.h				\
				./libft/includes/libft.h			\

CC			= 	gcc

CFLAGS		= 	-Wall -Wextra -Werror -g #-fsanitize=address

LIBINCLUDES	=	-Iincludes -Ilibft/includes

EXECINCLUDES =	-lreadline

LIBS		=	libft.a								\
				${LIB}

LIB			=	libminishell

EXEC		=	minishell

RM			=	rm -f

all:		libft ${EXEC}

%.o: 		%.c	${INCLUDES}
			${CC} ${CFLAGS} ${LIBINCLUDES} -c $< -o $@

$(LIB):		${OBJS} ${INCLUDES}
			ar rcs ${LIB} ${OBJS}

libft:		${INCLUDES}
			make -C libft

${EXEC}:	${EXEC}.c ${LIBS}
			$(CC) ${CFLAGS} ${LIBINCLUDES} ${EXEC}.c ${EXECINCLUDES} ${LIBS} -o ${EXEC}

clean:
			${RM} ${OBJS}
			make clean -C libft

fclean:		clean
			make fclean -C libft
			${RM} ${LIB} ${EXEC} ${LIBS}

re:			fclean all

.PHONY: 	all clean fclean re libft