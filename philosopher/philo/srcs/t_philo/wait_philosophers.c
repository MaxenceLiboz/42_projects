/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 11:19:44 by mliboz            #+#    #+#             */
/*   Updated: 2022/03/10 13:27:52 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	waiting(t_table *table)
{
	int		index;

	index = 0;
	while (is_alive(&table->ph_tbl[0]) == TRUE)
	{
		pthread_mutex_lock(&table->ph_tbl[index].settings.min_eat.mutex);
		if (table->ph_tbl[index].settings.min_eat.var == 0)
		{
			pthread_mutex_unlock(&table->ph_tbl[index].settings.min_eat.mutex);
			break ;
		}
		pthread_mutex_unlock(&table->ph_tbl[index].settings.min_eat.mutex);
		check_death_time(&table->ph_tbl[index]);
		index++;
		if (index == table->settings.nb_philos)
		{
			index = 0;
			my_usleep(100);
		}
	}
}

/*
	Wait all the philosopher threads to end
*/
void	wait_philosophers(t_table *table)
{
	int		index;

	index = -1;
	waiting(table);
	while (++index < table->settings.nb_philos)
	{
		if (pthread_join(table->ph_tbl[index].philo, NULL) != 0)
			ft_error(FAIL, "One philosopher can't be waited");
	}
}
