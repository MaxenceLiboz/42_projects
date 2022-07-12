/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:17:35 by mliboz            #+#    #+#             */
/*   Updated: 2022/03/09 13:29:23 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static void	wait_start(t_table *table)
{
	sem_wait(table->alive.sem);
	sem_post(table->alive.sem);
}

void	*routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	wait_start(table);
	gettimeofday(&table->lastmeal, NULL);
	gettimeofday(&table->time, NULL);
	if ((table->index + 1) % 2 == 0)
		my_usleep(500);
	while (1)
	{
		take_forks(table);
		eating(table);
		drop_forks(table);
		sem_wait(table->settings.min_eat.sem);
		if (table->settings.min_eat.var == 0)
		{
			table->settings.min_eat.var = -1;
			sem_post(table->settings.min_eat.sem);
			return (NULL);
		}
		sem_post(table->settings.min_eat.sem);
		sleeping(table);
		ft_write(table, THINK);
	}
	return (arg);
}
