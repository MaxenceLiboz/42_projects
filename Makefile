SRCS		=	command_parsing/create_prompt.c			\
				command_parsing/split_wog.c				\
				command_parsing/create_command.c		\
				command_parsing/count_split_wog.c		\
				command_parsing/checks_command.c		\
				command_parsing/check_pipes_n_quotes.c	\
				t_command/command_functions.c			\
				t_string/string_functions.c				\
				t_string/string_functions2.c			\
				t_string/split_string.c					\
				t_lst_env/lst_env_functions.c			\
				t_lst_env/lst_env_functions2.c			\
				builtins/unset.c						\
				builtins/export/export.c				\
				builtins/export/export_utils.c			\
				builtins/echo.c							\
				builtins/cd/cd.c						\
				builtins/cd/set_old_n_new_pwd.c			\
				builtins/cd/set_new_path.c				\
				builtins/cd/set_paths.c					\
				builtins/pwd.c							\
				builtins/exit.c							\
				builtins/env.c							\
				error_handling/error.c					\
				custom/custom.c							\
				init_term/init_term.c					\
				init_term/set_export_utils.c			\
				init_term/set_export.c					\
				init_term/signal.c						\
				builtins/exec_builtin.c					\
				t_lst_cmd/lst_cmd_functions.c			\
				malloc/malloc_functions.c				\
				exec_command/exec_command.c				\
				exec_command/get_redirections.c			\
				exec_command/create_final_command.c		\
				exec_command/ft_pipex.c					\
				exec_command/ft_pipex_utils.c			\
				exec_command/trim_quotes_uneeded.c		\
				exec_command/rm_heredoc_files.c			\
				error_handling/utils.c					\
				args/args_functions.c					\
				t_heredoc/heredoc_functions.c			\
				t_heredoc/init_table_heredoc.c			\
				t_heredoc/init_table_heredoc_utils.c	\
			
OBJS		=	$(addprefix ${OBJS_DIR}/, ${SRCS:.c=.o})

OBJS_DIR	=	objects
SRCS_DIR	=	srcs

INCLUDES	=	./includes/minishell.h					\
				./libft/includes/libft.h				\

CC			= 	gcc
CFLAGS		= 	-Wall -Wextra -Werror -g -fsanitize=address

LIBINCLUDES	=	-Iincludes -Ilibft/includes

EXECINCLUDES =	-lreadline -I./readline/include -L./readline/lib -lncurses

LIBS		=	libft.a									\
				${LIB}									\

LIB			=	libminishell.a						

NAME		=	minishell

RM			=	rm -rf	

MKDIR		=	mkdir -p

all:		libft ${NAME}

${OBJS_DIR}/%.o: 	${SRCS_DIR}/%.c	${INCLUDES} $(OBJDIRS)
			${MKDIR} $(@D) $(DMPDIR)$(@D)
			${CC} ${CFLAGS} ${LIBINCLUDES} -c $< -o $@

$(LIB):		${OBJS} ${INCLUDES}
			ar rcs ${LIB} ${OBJS}

libft:		${INCLUDES}
			make -C libft

${NAME}:	${NAME}.c ${LIBS}
			$(CC) ${CFLAGS} ${LIBINCLUDES} ${NAME}.c ${EXECINCLUDES} ${LIBS} -o ${NAME}

clean:
			${RM} ${OBJS} $(OBJS_DIR)
			make clean -C libft

fclean:		clean
			make fclean -C libft
			${RM} ${LIB} ${NAME} ${LIBS} ${NAME}.dSYM

re:			fclean all

.PHONY: 	all clean fclean re libft object