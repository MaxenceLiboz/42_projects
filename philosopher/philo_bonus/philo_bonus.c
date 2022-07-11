/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:30:24 by mliboz            #+#    #+#             */
/*   Updated: 2022/03/09 10:26:32 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	main(int argc, char **argv)
{
	t_table		table;

	if (argc < 5 || argc > 6)
		return (ft_error(FAIL, "Syntax error, not the right amount of args"));
	if (init_table(&table, argc, argv) == FAIL)
		return (ft_error(FAIL, "Syntax error"));
	if (init_semaphores(&table) == FAIL)
		return (ft_error(FAIL, "Semaphore error"));
	launch_philosophers(&table);
	close_all_sems_opened(&table);
	ft_lstclear(&table.mem);
	return (SUCCESS);
}
