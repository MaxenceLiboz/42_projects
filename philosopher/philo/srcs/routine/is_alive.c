/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_alive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:26:58 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/03/09 13:49:05 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	set_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->alive.mutex);
	philo->table->alive.var = FALSE;
	pthread_mutex_unlock(&philo->table->alive.mutex);
	ft_write(philo, DEAD);
}

/* Working on getting the right time for the philosopher*/
t_bool	check_death_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->settings.min_eat.mutex);
	if (time_diff(philo->last_meal) >= philo->settings.time_to_die
		&& philo->settings.min_eat.var != 0)
	{
		pthread_mutex_unlock(&philo->settings.min_eat.mutex);
		set_death(philo);
		pthread_mutex_lock(&philo->table->alive.mutex);
		philo->table->alive.var = -1;
		pthread_mutex_unlock(&philo->table->alive.mutex);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		return (FAIL);
	}
	pthread_mutex_unlock(&philo->settings.min_eat.mutex);
	pthread_mutex_lock(&philo->table->alive.mutex);
	if (philo->table->alive.var == FALSE)
	{
		pthread_mutex_unlock(&philo->table->alive.mutex);
		return (FAIL);
	}
	pthread_mutex_unlock(&philo->table->alive.mutex);
	return (SUCCESS);
}

t_bool	is_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->alive.mutex);
	if (philo->table->alive.var == FALSE)
	{
		pthread_mutex_unlock(&philo->table->alive.mutex);
		return (FALSE);
	}
	else if (philo->table->alive.var == -1)
	{
		pthread_mutex_unlock(&philo->table->alive.mutex);
		return (-1);
	}
	pthread_mutex_unlock(&philo->table->alive.mutex);
	return (TRUE);
}
