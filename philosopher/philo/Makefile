SRCS		=	ft_atoi.c								\
				ft_putstr_fd.c							\
				ft_strlen.c								\
				ft_strncmp.c							\
				ft_isdigit.c							\
				error_handling.c						\
				destroy_mutexs.c						\
				routine/routine.c						\
				routine/states.c						\
				routine/is_alive.c						\
				utils.c									\
				t_philo/init_philosophers.c				\
				t_philo/wait_philosophers.c				\
				
OBJS		=	$(addprefix ${OBJS_DIR}/, ${SRCS:.c=.o})

OBJS_DIR	=	objects
SRCS_DIR	=	srcs

INCLUDES	=	./includes/philo.h						\

CC			= 	gcc

CFLAGS		= 	-Wall -Wextra -Werror

LIBINCLUDES	=	-Iincludes

EXECINCLUDES =	-pthread					

NAME		=	philo

RM			=	rm -rf	

MKDIR		=	mkdir -p

all:		${NAME}

${OBJS_DIR}/%.o: 	${SRCS_DIR}/%.c	${INCLUDES} $(OBJDIRS) Makefile
			${MKDIR} $(@D) $(DMPDIR)$(@D)
			${CC} ${CFLAGS} ${LIBINCLUDES} -c $< -o $@

${NAME}:	${NAME}.c ${OBJS}
			$(CC) ${CFLAGS} ${LIBINCLUDES} ${NAME}.c ${EXECINCLUDES} ${OBJS} -o ${NAME}

run:		all
			./philo 2 100 100 100 5
clean:
			${RM} ${OBJS} $(OBJS_DIR)

fclean:		clean
			${RM} ${LIB} ${NAME} ${NAME}.dSYM

re:			fclean all

.PHONY: 	all clean fclean re run object