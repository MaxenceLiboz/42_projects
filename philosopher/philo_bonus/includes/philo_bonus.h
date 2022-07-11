/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 09:12:05 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/09 10:07:58 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# define FAIL 1
# define SUCCESS 0
# define TRUE 1
# define FALSE 0
# define EAT 100
# define SLEEP 101
# define DEAD 102
# define FORK 103
# define THINK 104

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>

typedef int	t_bool;

typedef struct s_sem
{
	sem_t			*sem;
	int				var;
}	t_sem;

typedef struct s_list
{
	void			*ptr;
	struct s_list	*next;
}	t_list;

typedef struct s_settings
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	struct s_sem	min_eat;
}	t_settings;

typedef struct s_table
{
	struct s_settings	settings;
	struct s_list		*mem;
	int					index;
	sem_t				**forks;
	int					*pid;
	struct s_sem		alive;
	struct timeval		time;
	struct timeval		lastmeal;
	sem_t				*write;
	pthread_t			philo;
}	t_table;

int			ft_atoi(const char *nptr);
char		*ft_itoa(int n);
int			ft_putstr_fd(char *s, int fd);
int			ft_strlen(const char *s);
char		*ft_strdup(const char *src);
t_bool		ft_isdigit(char *str);

/************ Garbage Collector **********/
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstclear(t_list **lst);
t_list		*ft_lstnew(void *ptr);
void		*ft_malloc(t_table *table, size_t size);
int			ft_error_exit(t_table *table, int size, char *s1, ...);

/************ Parsing *********************/
t_bool		check_args(t_settings settings, char **argv, int argc);
t_bool		init_table(t_table *table, int argc, char **argv);

/************* Semaphore *****************/
t_bool		init_semaphores(t_table *table);
void		close_all_sems_opened(t_table *table);

/************ Error handling **************/
int			ft_error(int error, char *str);

/************ Routine ********************/
// void		routine(t_table *table);
void		*routine(void *arg);
void		take_forks(t_table *table);
void		drop_forks(t_table *table);
void		eating(t_table *table);
void		sleeping(t_table *table);
t_bool		check_death_time(t_table *table);
t_bool		is_alive(t_table *table);

/************ Launch philosopher ********/
void		launch_philosophers(t_table *table);

/*************** T_PHILO *****************/

/*************** Utils *****************/
void		ft_write(t_table *table, int status);
int			time_diff(struct timeval start);
void		my_usleep(long waiting);

#endif