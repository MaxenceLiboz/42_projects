/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:27:42 by mliboz            #+#    #+#             */
/*   Updated: 2021/11/18 09:39:28 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

/*
	Return the index number corresponding to the index of 
	the pointer to functions initialize bellow
*/
int	ft_check_args(char arg)
{
	if (arg == 'c')
		return (0);
	if (arg == 's')
		return (1);
	if (arg == 'p')
		return (2);
	if (arg == 'd' || arg == 'i')
		return (3);
	if (arg == 'u')
		return (4);
	if (arg == 'x')
		return (5);
	if (arg == 'X')
		return (6);
	if (arg == '%')
		return (7);
	return (-1);
}

/*
	Init all the functions need to print an arg inside an tab of pointer
	to function
*/
void	ft_init_f(int (**f)(void *))
{
	f[0] = (int (*)(void *))ft_putchar;
	f[1] = (int (*)(void *))ft_putstr;
	f[2] = (int (*)(void *))ft_putptr;
	f[3] = (int (*)(void *))ft_putnbr;
	f[4] = (int (*)(void *))ft_putunbr;
	f[5] = (int (*)(void *))ft_putnbr_hexa;
	f[6] = (int (*)(void *))ft_putnbr_uhexa;
}
