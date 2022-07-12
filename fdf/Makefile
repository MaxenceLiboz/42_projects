SRCS		=	./srcs/map_parser.c					\
				./srcs/malloc_functions.c			\
				./srcs/convert_to_iso.c				\
				./srcs/hooks.c						\
				./srcs/map_tracing.c				\
				./srcs/rperror.c					\
				
OBJS		=	${SRCS:.c=.o}

INCLUDES	=	./includes/fdf.h					\
				./libft/includes/libft.h			\
				./minilibx/mlx.h 					\

CC			= 	gcc

CFLAGS		= 	-Wall -Wextra -Werror #-g -fsanitize=address

LIBINCLUDES	=	-Iincludes -Iminilibx -Ilibft/includes

LIBFLAGS	=	-framework OpenGL -framework AppKit

LIBS		=	libmlx.dylib libft.a

LIB			=	libfdf.a

EXEC		=	fdf

RM			=	rm -f

all:		${LIBS} ${LIB}

%.o: 		%.c	${INCLUDES}
			${CC} ${CFLAGS} ${LIBINCLUDES} -c $< -o $@

$(LIB):		${OBJS} ${INCLUDES}
			ar rcs ${LIB} ${OBJS}

$(LIBS):	${INCLUDES}
			make -C minilibx
			make -C libft

run:		all
			$(CC) ${CFLAGS} ${LIBINCLUDES} main.c ${LIB} ${LIBS} -o ${EXEC}

clean:
			${RM} ${OBJS}
			make clean -C minilibx
			make clean -C libft

fclean:		clean
			${RM} ${LIB} ${EXEC} ${LIBS}

re:			fclean all

.PHONY: 	all clean fclean re run