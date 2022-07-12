/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 09:19:12 by mliboz            #+#    #+#             */
/*   Updated: 2022/03/10 13:18:51 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
	if (pthread_mutex_init(&table->alive.mutex, NULL) != 0)
		return (FAIL);
	if (pthread_mutex_init(&table->write, NULL) != 0)
		return (destroy_mutex(&table->alive.mutex));
	table->alive.var = TRUE;
	table->settings.nb_philos = ft_atoi(argv[1]);
	table->settings.time_to_die = ft_atoi(argv[2]);
	table->settings.time_to_eat = ft_atoi(argv[3]);
	table->settings.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->settings.min_eat.var = ft_atoi(argv[5]);
	else
		table->settings.min_eat.var = -1;
	return (check_args(table->settings, argv, argc));
}

/*
	Main function
	- Check number of args, and return error if needed
*/
int	main(int argc, char **argv)
{
	t_table			table;

	if (argc < 5 || argc > 6)
		return (ft_error(FAIL, "Syntax error, not the right amount of args\n"));
	if (init_table(&table, argc, argv) == FAIL)
		return (ft_error(FAIL, "Syntax error"));
	if (init_philosophers(&table) == FAIL)
		return (FAIL);
	wait_philosophers(&table);
	destroy_forks_mutexs(&table, table.settings.nb_philos);
	destroy_eat_mutexs(&table, table.settings.nb_philos);
	return (SUCCESS);
}
