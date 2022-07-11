/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:12:27 by mliboz            #+#    #+#             */
/*   Updated: 2022/03/09 13:26:04 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static int	close_forks_sems(t_table *table, sem_t **sems, int size)
{
	int		i;
	char	*name;

	i = 0;
	while (i < size)
	{
		name = ft_itoa(i);
		if (name == NULL)
			ft_error_exit(table, 1, "Itoa: malloc failed");
		sem_close(sems[i]);
		free(name);
		i++;
	}
	return (FAIL);
}

static t_bool	init_forks_sems(t_table *table)
{
	int			i;
	char		*name;

	table->forks
		= ft_malloc(table, sizeof(sem_t *) * table->settings.nb_philos);
	i = 0;
	while (i < table->settings.nb_philos)
	{
		name = ft_itoa(i);
		if (name == NULL)
		{
			close_forks_sems(table, table->forks, i);
			ft_error_exit(table, 1, "Itoa: malloc failed");
		}
		table->forks[i] = sem_open(name, O_CREAT, 0666, 1);
		sem_unlink(name);
		free(name);
		if (table->forks[i] == SEM_FAILED)
			return (close_forks_sems(table, table->forks, i));
		i++;
	}
	return (SUCCESS);
}

void	close_all_sems_opened(t_table *table)
{
	close_forks_sems(table, table->forks, table->settings.nb_philos);
	sem_close(table->write);
	sem_close(table->alive.sem);
	sem_close(table->settings.min_eat.sem);
	// sem_close(table->start);
}

/*
	Init all the fork with semaphores
*/
t_bool	init_semaphores(t_table *table)
{
	if (init_forks_sems(table) == FAIL)
		return (FAIL);
	table->write = sem_open("write", O_CREAT, 0666, 1);
	sem_unlink("write");
	if (table->write == SEM_FAILED)
		return (close_forks_sems(table, table->forks,
				table->settings.nb_philos));
	table->alive.sem = sem_open("alive", O_CREAT, 0666, 0);
	sem_unlink("alive");
	if (table->alive.sem == SEM_FAILED)
	{
		close_forks_sems(table, table->forks, table->settings.nb_philos);
		return (sem_close(table->write));
	}
	sem_unlink("eat");
	table->settings.min_eat.sem = sem_open("eat", O_CREAT, 0666, 1);
	if (table->alive.sem == SEM_FAILED)
	{
		close_forks_sems(table, table->forks, table->settings.nb_philos);
		sem_close(table->write);
		return (sem_close(table->alive.sem));
	}
	return (SUCCESS);
}
