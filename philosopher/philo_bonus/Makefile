SRCS		=	ft_atoi.c								\
				ft_itoa.c 								\
				ft_strdup.c 							\
				ft_putstr_fd.c							\
				ft_strlen.c								\
				ft_isdigit.c							\
				error_handling.c						\
				utils.c									\
				parsing.c								\
				launch_philosophers.c					\
				semaphore.c								\
				routine/routine.c						\
				routine/death.c						\
				routine/states.c						\
				garbage_collector/ft_lstadd_front.c		\
				garbage_collector/ft_lstclear.c			\
				garbage_collector/ft_lstnew.c			\
				garbage_collector/malloc_functions.c	\
				
OBJS		=	$(addprefix ${OBJS_DIR}/, ${SRCS:.c=.o})

OBJS_DIR	=	objects
SRCS_DIR	=	srcs

INCLUDES	=	./includes/philo_bonus.h				\

CC			= 	gcc

CFLAGS		= 	-Wall -Wextra -Werror

LIBINCLUDES	=	-Iincludes

EXECINCLUDES =					

NAME		=	philo_bonus

RM			=	rm -rf	

MKDIR		=	mkdir -p

all:		${NAME}

${OBJS_DIR}/%.o: 	${SRCS_DIR}/%.c	${INCLUDES} $(OBJDIRS) Makefile
			${MKDIR} $(@D) $(DMPDIR)$(@D)
			${CC} ${CFLAGS} ${LIBINCLUDES} -c $< -o $@

${NAME}:	${NAME}.c ${OBJS}
			$(CC) ${CFLAGS} ${LIBINCLUDES} ${NAME}.c ${EXECINCLUDES} ${OBJS} -o ${NAME}

run:		all
			./philo_bonus 2 100 100 100 5
clean:
			${RM} ${OBJS} $(OBJS_DIR)

fclean:		clean
			${RM} ${LIB} ${NAME} ${NAME}.dSYM

re:			fclean all

.PHONY: 	all clean fclean re run object