/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:32:15 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/02/17 11:44:25 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	is_atoi(int nb, char *str)
{
	if (nb == 0 && ft_strncmp(str, "0", 2) != 0)
		return (0);
	return (1);
}

int	is_atoll(long long nb, char *str)
{
	if (nb == 0 && ft_strncmp(str, "0", 2) != 0)
		return (0);
	return (1);
}
