SRCS		=	command_parsing/create_prompt.c		\
				command_parsing/split_wog.c			\
				command_parsing/create_command.c	\
				command_parsing/count_split_wog.c	\
				command_parsing/checks_command.c	\
				t_command/command_functions.c		\
				t_string/string_functions.c			\
				t_string/string_functions2.c		\
				t_lst_env/lst_env_functions.c		\
				t_lst_env/lst_env_functions2.c		\
				builtins/set_export.c				\
				builtins/export.c					\
				builtins/error.c					\
				builtins/env.c						\
				t_lst_cmd/lst_cmd_functions.c		\
				freestrs.c							\
				
OBJS		=	$(addprefix ${OBJS_DIR}/, ${SRCS:.c=.o})

OBJS_DIR	=	objects
SRCS_DIR	=	srcs

INCLUDES	=	./includes/minishell.h				\
				./libft/includes/libft.h			\

CC			= 	gcc

CFLAGS		= 	-Wall -Wextra -Werror -g #-fsanitize=address

LIBINCLUDES	=	-Iincludes -Ilibft/includes

EXECINCLUDES =	-lreadline

LIBS		=	libft.a								\
				${LIB}

LIB			=	libminishell.a

EXEC		=	minishell

RM			=	rm -rf	

MKDIR		=	mkdir -p

all:		libft ${EXEC}

${OBJS_DIR}/%.o: 	${SRCS_DIR}/%.c	${INCLUDES} $(OBJDIRS)
			${MKDIR} $(@D) $(DMPDIR)$(@D)
			${CC} ${CFLAGS} ${LIBINCLUDES} -c $< -o $@

$(LIB):		${OBJS} ${INCLUDES}
			ar rcs ${LIB} ${OBJS}

libft:		${INCLUDES}
			make -C libft

${EXEC}:	${EXEC}.c ${LIBS}
			$(CC) ${CFLAGS} ${LIBINCLUDES} ${EXEC}.c ${EXECINCLUDES} ${LIBS} -o ${EXEC}

clean:
			${RM} ${OBJS} $(OBJS_DIR)
			make clean -C libft

fclean:		clean
			make fclean -C libft
			${RM} ${LIB} ${EXEC} ${LIBS} ${EXEC}.dSYM

re:			fclean all

.PHONY: 	all clean fclean re libft object