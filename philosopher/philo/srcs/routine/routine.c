/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 11:21:31 by mliboz            #+#    #+#             */
/*   Updated: 2022/03/10 13:12:49 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*unlock_all(t_philo *philo)
{
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	return (NULL);
}

t_bool	eat_enought(t_philo *philo)
{
	pthread_mutex_lock(&philo->settings.min_eat.mutex);
	if (philo->settings.min_eat.var == 0)
	{
		pthread_mutex_unlock(&philo->settings.min_eat.mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->settings.min_eat.mutex);
	return (FALSE);
}

/*
	Create the Routine of the philospher => eat, sleep, think
*/
void	*routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	gettimeofday(&philo->last_meal, NULL);
	gettimeofday(&philo->time, NULL);
	if (philo->id % 2 == 0)
		my_usleep(1000);
	while (is_alive(philo) == TRUE)
	{
		if (is_alive(philo) == TRUE)
			take_forks(philo);
		if (is_alive(philo) == TRUE)
			eating(philo);
		if (is_alive(philo) == TRUE)
			drop_forks(philo);
		if (eat_enought(philo) == TRUE)
			return (unlock_all(philo));
		if (is_alive(philo) == TRUE)
			sleeping(philo);
		if (is_alive(philo) == TRUE)
			ft_write(philo, THINK);
	}
	return (unlock_all(philo));
}
