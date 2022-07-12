/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:33:14 by mliboz            #+#    #+#             */
/*   Updated: 2022/03/09 13:01:23 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	ft_write(t_table *table, int status)
{
	sem_wait(table->write);
	if (status == EAT)
		printf("%d %d is eating\n", time_diff(table->time), table->index + 1);
	else if (status == SLEEP)
		printf("%d %d is sleeping\n", time_diff(table->time), table->index + 1);
	else if (status == THINK)
		printf("%d %d is thinking\n", time_diff(table->time), table->index + 1);
	else if (status == FORK)
		printf("%d %d has taken a fork\n",
			time_diff(table->time), table->index + 1);
	else if (status == DEAD)
	{
		printf("%d %d is dead\n", time_diff(table->time), table->index + 1);
		return ;
	}
	sem_post(table->write);
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
