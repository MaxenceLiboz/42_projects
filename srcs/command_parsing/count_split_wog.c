/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_split_wog.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 10:46:26 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/07 10:46:34 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_split_wog(const char *str, char charset)
{
	int		i;
	int		count;
	int		dquotes;
	int		squotes;

	count = 0;
	i = 0;
	dquotes = 1;
	squotes = 1;
	while (str[i] && str[i] == charset)
		i++;
	if (str[i] != 0)
		count++;
	while (str[i])
	{
		if (str[i] == '"')
			dquotes *= -1;
		if (str[i] == '\'')
			squotes *= -1;
		if (str[i] == charset
			&& (str[i + 1] != charset && str[i + 1] != 0)
			&& dquotes > 0 && squotes > 0)
			count++;
		i++;
	}
	return (count);
}