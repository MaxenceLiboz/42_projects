/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mutexs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:42:14 by mliboz            #+#    #+#             */
/*   Updated: 2022/03/09 13:42:28 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/*
	Destroy all the mutex created or
	if error occurr in initialization of mutex, destroy the ones already init
*/
int	destroy_forks_mutexs(t_table *table, int index)
{
	int		i;

	i = 0;
	while (i < index)
		pthread_mutex_destroy(&table->forks[i++]);
	free(table->forks);
	return (FAIL);
}

/*
	Destroy all the mutex created or
	if error occurr in initialization of mutex, destroy the ones already init
*/
int	destroy_eat_mutexs(t_table *table, int index)
{
	int		i;

	i = 0;
	while (i < index)
		pthread_mutex_destroy(&table->ph_tbl[i++].settings.min_eat.mutex);
	free(table->ph_tbl);
	return (FAIL);
}

int	destroy_mutex(pthread_mutex_t *mutex)
{
	pthread_mutex_destroy(mutex);
	return (FAIL);
}
