/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freestrs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 10:33:11 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/13 13:53:29 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_free(char **str)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (str[i])
	{
		while (str[i][y])
		{
			str[i][y] = 0;
			y++;
		}
		free(str[i]);
		i++;
	}
	free(str);
}
