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

#ifndef PHILO_H
# define PHILO_H
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
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef int	t_bool;

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	int				var;
}	t_mutex;

typedef struct s_settings
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	struct s_mutex	min_eat;
}	t_settings;

typedef struct s_philo
{
	pthread_t			philo;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	int					id;
	struct s_table		*table;
	struct s_settings	settings;
	struct timeval		last_meal;
	struct timeval		time;
}	t_philo;

typedef struct s_table
{
	struct s_philo		*ph_tbl;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write;
	struct s_settings	settings;
	struct s_mutex		alive;
}	t_table;

int			ft_atoi(const char *nptr);
int			ft_putstr_fd(char *s, int fd);
int			ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
t_bool		ft_isdigit(char *str);

/************ Error handling **************/
int			ft_error(int error, char *str);
void		print_table(t_table table);
int			error_detach_threads(t_table *table, int index);
int			destroy_eat_mutexs(t_table *table, int index);
int			destroy_forks_mutexs(t_table *table, int index);
int			destroy_mutex(pthread_mutex_t *mutex);

/*************** T_PHILO *****************/
t_bool		init_philosophers(t_table *table);
void		wait_philosophers(t_table *table);

/*************** Routine *****************/
void		*routine(void *test);
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
t_bool		is_alive(t_philo *philo);
t_bool		check_death_time(t_philo *philo);
void		set_death(t_philo *philo);

/*************** Utils *****************/
void		ternary_bool(t_bool *to_change, t_bool condition, t_bool true,
				t_bool false);
void		ft_write(t_philo *philo, int status);
int			time_diff(struct timeval start);
void		my_usleep(long waiting);

#endif