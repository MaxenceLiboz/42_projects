/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_uhexa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 09:42:50 by mliboz            #+#    #+#             */
/*   Updated: 2021/11/18 09:43:03 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

/*
	Print an unsigned int convert to hexadecimal upercase and return
	the number of char
*/
int	ft_putnbr_uhexa(unsigned int nbr)
{
	int		i;

	i = 0;
	if (nbr == 0)
	{
		ft_putchar(BASE_U[nbr % ft_strlen(BASE_U)]);
		return (1);
	}
	else
	{
		ft_convert_hexa(nbr, ft_strlen(BASE_U), BASE_U, &i);
		return (i);
	}
}
