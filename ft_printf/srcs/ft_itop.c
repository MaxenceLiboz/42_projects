/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:59:19 by mliboz            #+#    #+#             */
/*   Updated: 2021/11/18 09:40:50 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

/*
	Print a interger number
*/
void	ft_itop(int n)
{
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n *= (-1);
	}
	if (n > 9)
		ft_itop(n / 10);
	ft_putchar(n % 10 + '0');
}

/*
	Print a unsigned interger number
*/
void	ft_uitop(unsigned int n)
{
	if (n > 9)
		ft_uitop(n / 10);
	ft_putchar(n % 10 + '0');
}
