/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:33:14 by mliboz            #+#    #+#             */
/*   Updated: 2022/03/07 12:26:31 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_write(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->table->write);
	if (status == EAT && is_alive(philo) == TRUE)
		printf("%d %d is eating\n", time_diff(philo->time), philo->id);
	else if (status == SLEEP && is_alive(philo) == TRUE)
		printf("%d %d is sleeping\n", time_diff(philo->time), philo->id);
	else if (status == THINK && is_alive(philo) == TRUE)
		printf("%d %d is thinking\n", time_diff(philo->time), philo->id);
	else if (status == FORK && is_alive(philo) == TRUE)
		printf("%d %d has taken a fork\n",
			time_diff(philo->time), philo->id);
	else if (status == DEAD && is_alive(philo) != -1)
		printf("%d %d is dead\n", time_diff(philo->time), philo->id);
	pthread_mutex_unlock(&philo->table->write);
}

int	time_diff(struct timeval start)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return ((end.tv_sec - start.tv_sec) * 1000
		+ 1e-3 * (end.tv_usec - start.tv_usec));
}

void	my_usleep(long waiting)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	usleep(waiting * 0.95);
	while (time_diff(start) < waiting / 1000)
		usleep(50);
}
