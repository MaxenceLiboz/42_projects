/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:26:58 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/03/09 13:25:55 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static void	set_death(t_table *table)
{
	sem_wait(table->alive.sem);
	table->alive.var = FALSE;
	sem_post(table->alive.sem);
	ft_write(table, DEAD);
}

/* Working on getting the right time for the philosopher*/
t_bool	check_death_time(t_table *table)
{
	sem_wait(table->settings.min_eat.sem);
	if (time_diff(table->lastmeal) >= table->settings.time_to_die
		&& table->settings.min_eat.var != 0)
	{
		sem_post(table->settings.min_eat.sem);
		set_death(table);
		drop_forks(table);
		return (FAIL);
	}
	sem_post(table->settings.min_eat.sem);
	sem_wait(table->alive.sem);
	if (table->alive.var == FALSE)
	{
		sem_post(table->alive.sem);
		return (FAIL);
	}
	sem_post(table->alive.sem);
	return (SUCCESS);
}