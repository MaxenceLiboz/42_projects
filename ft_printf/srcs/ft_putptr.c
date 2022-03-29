/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 09:25:33 by mliboz            #+#    #+#             */
/*   Updated: 2021/11/18 09:44:05 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

/*
	Print the address of a pointer in hexadecimal and return the number of char
*/
int	ft_putptr(void *ptr)
{
	int		i;

	i = 2;
	ft_putstr("0x");
	ft_convert_hexa((unsigned long)ptr, ft_strlen(BASE), BASE, &i);
	if (i == 2)
	{
		ft_putchar('0');
		return (i + 1);
	}
	return (i);
}
