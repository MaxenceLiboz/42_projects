/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_split_wog.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:54:28 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/17 13:41:27 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Count the malloc size for the split_wog function
*/
int	count_split_wog(const char *str, char charset)
{
	int		i;
	int		count;
	int		dquotes;
	int		squotes;

	count = 0;
	i = -1;
	dquotes = 1;
	squotes = 1;
	while (str[++i] && str[i] == charset)
		;
	if (str[i] != 0)
		count++;
	while (str[i])
	{
		if (str[i] == '"')
			dquotes *= -1;
		if (str[i] == '\'')
			squotes *= -1;
		if (str[i] == charset && str[i + 1]
			&& (str[i + 1] != charset && str[i + 1] != 0)
			&& dquotes > 0 && squotes > 0)
			count++;
		i++;
	}
	return (count);
}
