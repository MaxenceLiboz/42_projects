/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:34:21 by mliboz            #+#    #+#             */
/*   Updated: 2021/11/18 09:42:45 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

/*
	Print an int and return the number of char
*/
int	ft_putnbr(int n)
{
	int		i;

	i = 0;
	ft_itop(n);
	if (n < 0)
		i++;
	if (n == 0)
		i++;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}
