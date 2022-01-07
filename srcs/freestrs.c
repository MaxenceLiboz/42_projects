/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freestrs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 10:33:11 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/07 10:35:07 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_free(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		freestr(str[i]);
		i++;
	}
	free(str);
	exit(-1);
}
