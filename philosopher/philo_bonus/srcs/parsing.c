/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:47:03 by mliboz            #+#    #+#             */
/*   Updated: 2022/03/10 13:30:46 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

/*
	Check if the args enter by the user are correct
	- Are digit
	- Are not more than int max or less than int min
	- Are not negative
*/
t_bool	check_args(t_settings settings, char **argv, int argc)
{
	if (ft_isdigit(argv[1]) == FAIL || settings.nb_philos <= 0)
		return (FAIL);
	else if (ft_isdigit(argv[2]) == FAIL || settings.time_to_die <= 0)
		return (FAIL);
	else if (ft_isdigit(argv[3]) == FAIL || settings.time_to_eat <= 0)
		return (FAIL);
	else if (ft_isdigit(argv[4]) == FAIL || settings.time_to_sleep <= 0)
		return (FAIL);
	else if (argc == 6 && (ft_isdigit(argv[2]) == FAIL
			|| settings.min_eat.var <= 0))
		return (FAIL);
	return (SUCCESS);
}
/*
	Init the defined stuct with argv, to get all the data we need
*/
t_bool	init_table(t_table *table, int argc, char **argv)
{
	table->index = 0;
	table->settings.nb_philos = ft_atoi(argv[1]);
	table->settings.time_to_die = ft_atoi(argv[2]);
	table->settings.time_to_eat = ft_atoi(argv[3]);
	table->settings.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->settings.min_eat.var = ft_atoi(argv[5]);
	else
		table->settings.min_eat.var = -2;
	if (check_args(table->settings, argv, argc) == FAIL)
		return (FAIL);
	table->pid = ft_malloc(table, sizeof(int) * table->settings.nb_philos);
	table->alive.var = TRUE;
	return (SUCCESS);
}
