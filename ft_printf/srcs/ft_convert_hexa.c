/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_hexa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 09:49:34 by mliboz            #+#    #+#             */
/*   Updated: 2021/11/18 09:36:54 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

/*
	Convert a number to hexa, print it and assign to pointer i the number of
	chars print
*/
void	ft_convert_hexa(unsigned long nbr, int baselen, char *base, int *i)
{
	if (nbr != 0)
	{
		*i += 1;
		ft_convert_hexa(nbr / baselen, baselen, base, i);
	}
	if (nbr < 0)
		ft_putchar(base[-(nbr % baselen)]);
	else if (nbr != 0)
		ft_putchar(base[nbr % baselen]);
}
