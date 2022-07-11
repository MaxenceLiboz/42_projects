/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 10:30:06 by mliboz            #+#    #+#             */
/*   Updated: 2022/03/09 13:42:07 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/*
	Send an error and return
*/
int	ft_error(int error, char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (error);
}

/*
	Print table variable
*/
void	print_table(t_table table)
{
	printf("Number of philos: %d\n", table.settings.nb_philos);
	printf("Time to die: %d\n", table.settings.time_to_die);
	printf("Time to eat: %d\n", table.settings.time_to_eat);
	printf("Time to sleep: %d\n", table.settings.time_to_sleep);
	printf("Minimum eat: %d\n", table.settings.min_eat.var);
}

/*
	If an error occurr while create the thread, detach the ones already created
*/
int	error_detach_threads(t_table *table, int index)
{
	int		i;

	i = 0;
	while (i < index)
		pthread_detach(table->ph_tbl[i].philo);
	return (destroy_forks_mutexs(table, table->settings.nb_philos));
}
