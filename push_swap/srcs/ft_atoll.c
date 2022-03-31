/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 10:52:04 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/10 11:20:13 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

static int	ft_checkstr(const char *str, int *neg, int *str_i)
{
	while (str[*str_i] && (str[*str_i] != '-' && str[*str_i] != '+')
		&& (str[*str_i] < '0' || str[*str_i] > '9'))
	{
		if ((str[*str_i] != '\t' && str[*str_i] != '\n' && str[*str_i] != '\v'
				&& str[*str_i] != '\f' && str[*str_i] != '\r'
				&& str[*str_i] != ' '))
			return (1);
		*str_i += 1;
	}
	if (str[*str_i] == '-' || str[*str_i] == '+')
	{
		if (str[*str_i] == '-')
			*neg *= -1;
		*str_i += 1;
	}
	if (str[*str_i] < '0' || str[*str_i] > '9')
		return (1);
	return (0);
}

long long	ft_atoll(const char *nptr)
{
	int				neg;
	int				str_i;
	long double		nb;

	neg = 1;
	str_i = 0;
	nb = 0;
	if (ft_checkstr(nptr, &neg, &str_i))
		return (0);
	while (nptr[str_i] >= '0' && nptr[str_i] <= '9')
	{
		nb = nb * 10 + (nptr[str_i] - '0');
		str_i++;
	}
	if (nb * neg > LLONG_MAX || nb * neg < LLONG_MIN)
		return (0);
	return (nb * neg);
}
