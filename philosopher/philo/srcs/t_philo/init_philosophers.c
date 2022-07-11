/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 10:18:33 by mliboz            #+#    #+#             */
/*   Updated: 2022/03/07 10:02:08 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_bool	init_forks(t_table *table)
{
	int		i;

	i = 0;
	table->forks = malloc(sizeof(t_mutex) * table->settings.nb_philos + 1);
	if (table->forks == NULL)
		return (FAIL);
	while (i < table->settings.nb_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			destroy_forks_mutexs(table, i);
			return (destroy_eat_mutexs(table, table->settings.nb_philos));
		}
		i++;
	}
	i = -1;
	while (++i < table->settings.nb_philos - 1)
	{
		table->ph_tbl[i].left = &table->forks[i];
		table->ph_tbl[i].right = &table->forks[i + 1];
	}
	table->ph_tbl[i].left = &table->forks[i];
	table->ph_tbl[i].right = &table->forks[0];
	return (SUCCESS);
}

/*
	Init one thread by philosopher
*/
t_bool	init_threads(t_table *table)
{
	int		index;

	index = -1;
	while (++index < table->settings.nb_philos)
	{
		if (pthread_create(&table->ph_tbl[index].philo,
				NULL, &routine, &table->ph_tbl[index]) != 0)
			return (error_detach_threads(table, index));
	}
	return (SUCCESS);
}

/*
	Init the alive variable of philosophers
*/
t_bool	init_philosophers_varaibles(t_table *table)
{
	int		index;

	index = -1;
	while (++index < table->settings.nb_philos)
	{
		table->ph_tbl[index].table = table;
		table->ph_tbl[index].id = index + 1;
		table->ph_tbl[index].settings.nb_philos = table->settings.nb_philos;
		table->ph_tbl[index].settings.time_to_die = table->settings.time_to_die;
		table->ph_tbl[index].settings.time_to_eat = table->settings.time_to_eat;
		table->ph_tbl[index].settings.time_to_sleep
			= table->settings.time_to_sleep;
		table->ph_tbl[index].settings.min_eat.var
			= table->settings.min_eat.var;
		if (pthread_mutex_init(&table->ph_tbl[index].settings.min_eat.mutex,
				NULL) != 0)
			return (destroy_eat_mutexs(table, index));
	}
	return (SUCCESS);
}

/*
	Init the philosopher structure
*/
t_bool	init_philosophers(t_table *table)
{
	table->ph_tbl = malloc(sizeof(t_philo) * table->settings.nb_philos);
	if (table->ph_tbl == NULL)
		return (ft_error(FAIL, "malloc: error allocating memory"));
	if (init_philosophers_varaibles(table) == FAIL)
		return (FAIL);
	if (init_forks(table) == FAIL)
		return (FAIL);
	if (init_threads(table) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
