/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:41:12 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/01/12 16:55:39 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	check_quotes(t_string cmd)
{
	int		squotes;
	int		dquotes;
	int		i;

	squotes = 0;
	dquotes = 0;
	i = 0;
	while (cmd.str[i])
	{
		if (cmd.str[i] == '\"')
			dquotes += 1;
		if (cmd.str[i] == '\'')
			squotes += 1;
		i++;
	}
	if (squotes % 2 != 0 && dquotes % 2 != 0)
		printf("Missing both: \" and \'\n");
	else if (squotes % 2 != 0)
		printf("Missing: \'\n");
	else if (dquotes % 2 != 0)
		printf("Missing: \"\n");
	if (squotes % 2 != 0 || dquotes % 2 != 0)
		return (FALSE);
	return (TRUE);
}

t_bool	check_pipes(t_command cmd)
{
	int		pipes;
	int		i;

	pipes = 0;
	i = 0;
	while (i < cmd.size - 1)
	{
		if (ft_strncmp(cmd.array[i].str, "|", 2) == 0
			&& !cmd.array[i + 1].str)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
