/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 09:40:28 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/19 10:04:28 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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

int	ft_atoi(const char *nptr)
{
	int		neg;
	int		str_i;
	long	nb;

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
	nb *= neg;
	if (nb > INT_MAX || nb < INT_MIN)
		return (0);
	return (nb);
}
