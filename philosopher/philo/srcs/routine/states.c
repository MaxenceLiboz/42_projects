/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:24:47 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/03/10 13:26:28 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	eating(t_philo *philo)
{
	ft_write(philo, EAT);
	pthread_mutex_lock(&philo->settings.min_eat.mutex);
	philo->settings.min_eat.var -= 1;
	pthread_mutex_unlock(&philo->settings.min_eat.mutex);
	gettimeofday(&philo->last_meal, NULL);
	if (time_diff(philo->last_meal) + philo->settings.time_to_eat
		> philo->settings.time_to_die)
		my_usleep((philo->settings.time_to_die
				- time_diff(philo->last_meal)) * 1000 + 1000);
	else
		my_usleep(philo->settings.time_to_eat * 1000);
}

void	sleeping(t_philo *philo)
{
	ft_write(philo, SLEEP);
	if (time_diff(philo->last_meal) + philo->settings.time_to_sleep
		> philo->settings.time_to_die)
		my_usleep((philo->settings.time_to_die
				- time_diff(philo->last_meal)) * 1000 + 1000);
	else
		my_usleep(philo->settings.time_to_sleep * 1000);
}

void	take_forks(t_philo *philo)
{
	if (is_alive(philo) == TRUE)
	{
		if (is_alive(philo) == TRUE)
			pthread_mutex_lock(philo->left);
		ft_write(philo, FORK);
		if (is_alive(philo) == TRUE)
			pthread_mutex_lock(philo->right);
		ft_write(philo, FORK);
	}
}

void	drop_forks(t_philo *philo)
{
	if (is_alive(philo) == TRUE)
	{
		if (is_alive(philo) == TRUE)
			pthread_mutex_unlock(philo->left);
		if (is_alive(philo) == TRUE)
			pthread_mutex_unlock(philo->right);
	}
}
