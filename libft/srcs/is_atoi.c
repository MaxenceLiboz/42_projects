/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:32:15 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/01/24 11:33:01 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	is_atoi(long long nb)
{
	if (nb > INT_MAX || nb < INT_MIN)
		return (0);
	return (1);
}

int	is_atoll(long double nb)
{
	if (nb > LLONG_MAX || nb < LLONG_MIN)
		return (0);
	return (1);
}