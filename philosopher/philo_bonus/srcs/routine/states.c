/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:28:21 by mliboz            #+#    #+#             */
/*   Updated: 2022/03/10 13:33:08 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	take_forks(t_table *table)
{
	sem_wait(table->forks[table->index]);
	ft_write(table, FORK);
	if (table->index + 1 < table->settings.nb_philos)
		sem_wait(table->forks[table->index + 1]);
	else
		sem_wait(table->forks[0]);
	ft_write(table, FORK);
}

void	drop_forks(t_table *table)
{
	sem_post(table->forks[table->index]);
	if (table->index + 1 < table->settings.nb_philos)
		sem_post(table->forks[table->index + 1]);
	else
		sem_post(table->forks[0]);
}

void	eating(t_table *table)
{
	ft_write(table, EAT);
	sem_wait(table->settings.min_eat.sem);
	table->settings.min_eat.var -= 1;
	sem_post(table->settings.min_eat.sem);
	gettimeofday(&table->lastmeal, NULL);
	if (time_diff(table->lastmeal) + table->settings.time_to_eat
		> table->settings.time_to_die)
		my_usleep((table->settings.time_to_die
				- time_diff(table->lastmeal)) * 1000 + 1000);
	else
		my_usleep(table->settings.time_to_eat * 1000);
}

void	sleeping(t_table *table)
{
	ft_write(table, SLEEP);
	if (time_diff(table->lastmeal) + table->settings.time_to_sleep
		> table->settings.time_to_die)
		my_usleep((table->settings.time_to_die
				- time_diff(table->lastmeal)) * 1000 + 1000);
	else
		my_usleep(table->settings.time_to_sleep * 1000);
}
