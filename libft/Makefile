END=$'\x1b[0m
RED=$'\x1b[31m
GREEN=$'\x1b[32m
BLUE=$'\x1b[34m

SRCS		=	./ft_atoi.c ./ft_calloc.c ./ft_isalpha.c ./ft_isdigit.c ./ft_itoa.c\
      			./ft_memcmp.c ./ft_memmove.c ./ft_putchar_fd.c ./ft_putnbr_fd.c \
				./ft_split.c ./ft_strdup.c ./ft_strjoin.c ./ft_strlcpy.c \
				./ft_strmapi.c ./ft_strnstr.c ./ft_strtrim.c ./ft_tolower.c \
				./ft_bzero.c ./ft_isalnum.c ./ft_isascii.c ./ft_isprint.c \
				./ft_memchr.c ./ft_memcpy.c ./ft_memset.c ./ft_putendl_fd.c \
				./ft_putstr_fd.c ./ft_strchr.c ./ft_striteri.c ./ft_strlcat.c \
				./ft_strlen.c ./ft_strncmp.c ./ft_strrchr.c ./ft_substr.c \
				./ft_toupper.c 

SRCSBONUS	=	./ft_lstnew.c ./ft_lstadd_front.c ./ft_lstsize.c ./ft_lstlast.c\
				./ft_lstadd_back.c ./ft_lstdelone.c ./ft_lstclear.c \
				./ft_lstiter.c ./ft_lstmap.c


OBJS		=	${SRCS:.c=.o}

OBJSBONUS		=	${SRCSBONUS:.c=.o}

INCLUDES	=	./libft.h

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

NAME		=	libft.a

RM			=	rm -f

all:		${NAME}

%.o : 		%.c ${INCLUDES}
			@${CC} ${CFLAGS} -c $< -o $@
			@echo "${BLUE}[BUILD]${END} $@"

$(NAME):	${OBJS} ${INCLUDES}
			@ar rcs ${NAME} ${OBJS}
			@echo "${GREEN}[CREATE]${END} ${NAME}"

bonus:		${OBJS} ${OBJSBONUS} ${INCLUDES}
			@ar rcs ${NAME} ${OBJSBONUS} ${OBJS}
			@echo "${GREEN}[CREATE]${END} ${NAME}"

clean:
			@${RM} ${OBJS} ${OBJSBONUS}
			@echo "${RED}[DELETE]${END} *.o"

fclean:		clean
			@${RM} ${NAME}
			@echo "${RED}[DELETE]${END} ${NAME}"

re:			fclean all

.PHONY: 	all clean fclean re bonus