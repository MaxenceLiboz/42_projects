END=$'\x1b[0m
RED=$'\x1b[31m
GREEN=$'\x1b[32m
BLUE=$'\x1b[34m

SRCS		=	./srcs/ft_printf.c 			\
				./srcs/ft_strlen.c 			\
				./srcs/ft_putchar.c 		\
				./srcs/ft_putstr.c 			\
				./srcs/ft_putptr.c			\
				./srcs/ft_putnbr.c 			\
				./srcs/ft_putunbr.c 		\
				./srcs/ft_putnbr_hexa.c 	\
				./srcs/ft_putnbr_uhexa.c	\
				./srcs/ft_convert_hexa.c 	\
				./srcs/ft_itop.c			\
				./srcs/ft_manage_args.c		\


OBJS		=	${SRCS:.c=.o}

INCLUDES	=	./includes/ft_printf.h

CC			= 	gcc

CFLAGS		= 	-Wall -Wextra -Werror

NAME		=	libftprintf.a

RM			=	rm -f

all:		${NAME}

%.o: 		%.c	${INCLUDES}
			@${CC} ${CFLAGS} -I includes -c $< -o $@
			@echo "${BLUE}[BUILD]${END} $@"

$(NAME):	${OBJS} ${INCLUDES}
			@ar rcs ${NAME} ${OBJS}
			@echo "${GREEN}[CREATE]${END} ${NAME}"

run:		all
			@gcc main.c lftprintf.a && ./a.out


clean:
			@${RM} ${OBJS}
			@echo "${RED}[DELETE]${END} *.o"

fclean:		clean
			@${RM} ${NAME}
			@echo "${RED}[DELETE]${END} ${NAME}"

re:			fclean all

.PHONY: 	all clean fclean re bonus