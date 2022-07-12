/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:16:09 by mliboz            #+#    #+#             */
/*   Updated: 2022/03/10 13:02:49 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

t_bool	launch_thread(t_table *table)
{
	int		index;

	index = 0;
	if (pthread_create(&table->philo, NULL, &routine, (void *)table) != 0)
		return (FAIL);
	pthread_detach(table->philo);
	while (1)
	{
		sem_wait(table->settings.min_eat.sem);
		if (table->settings.min_eat.var == -1)
		{
			sem_post(table->settings.min_eat.sem);
			break ;
		}
		sem_post(table->settings.min_eat.sem);
		if (check_death_time(table) == FAIL)
			break ;
		index++;
		if (index == table->settings.nb_philos)
		{
			index = 0;
			my_usleep(100);
		}
	}
	return (SUCCESS);
}

static void	ft_fork(t_table *table, int index)
{
	int		pid;

	pid = fork();
	if (pid < 0)
		ft_error_exit(table, 1, "Exit: Fork error");
	else if (pid == 0)
	{
		launch_thread(table);
		if (table->alive.var == TRUE)
			exit(TRUE);
		else
			exit (FALSE);
	}
	else
		table->pid[index] = pid;
}

void	launch_philosophers(t_table *table)
{
	int		i;
	int		status;

	i = 0;
	while (i < table->settings.nb_philos)
	{
		ft_fork(table, i);
		table->index += 1;
		i++;
	}
	sem_post(table->alive.sem);
	while (waitpid(-1, &status, 0) != -1 && WEXITSTATUS(status) != FALSE)
		;
	if (WEXITSTATUS(status) == FALSE)
	{
		i = 0;
		while (i < table->settings.nb_philos)
			kill(table->pid[i++], SIGINT);
	}
}
