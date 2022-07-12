/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rperror.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 09:15:26 by mliboz            #+#    #+#             */
/*   Updated: 2021/12/10 16:46:01 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*
	1: Use the perror function and return a selected value
*/
int	rperror(char *str, int return_value)
{
	perror(str);
	return (return_value);
}
