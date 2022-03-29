/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:34:21 by mliboz            #+#    #+#             */
/*   Updated: 2021/11/18 09:43:12 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

/*
	Print an unsigned int convert to hexadecimal lowercase and return
	the number of char
*/
int	ft_putnbr_hexa(unsigned int nbr)
{
	int		i;

	i = 0;
	if (nbr == 0)
	{
		ft_putchar(BASE[nbr % ft_strlen(BASE)]);
		return (1);
	}
	else
	{
		ft_convert_hexa(nbr, ft_strlen(BASE), BASE, &i);
		return (i);
	}
}
