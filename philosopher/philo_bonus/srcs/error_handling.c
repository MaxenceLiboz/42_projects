/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 10:30:06 by mliboz            #+#    #+#             */
/*   Updated: 2022/03/03 12:46:01 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

/*
	Send an error and return
*/
int	ft_error(int error, char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (error);
}
