/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:41:12 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/01/19 14:12:13 by tarchimb         ###   ########.fr       */
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
		print_stderror(0, 1, "Missing: both: \', \"\n");
	else if (squotes % 2 != 0)
		print_stderror(0, 1, "Missing: \'\n");
	else if (dquotes % 2 != 0)
		print_stderror(0, 1, "Missing: \"\n");
	if (squotes % 2 != 0 || dquotes % 2 != 0)
		return (FALSE);
	return (TRUE);
}

t_bool	check_pipes(t_command cmd)
{
	int		i;

	i = 0;
	while (i < cmd.size)
	{
		if (ft_strncmp(cmd.array[i].str, "|", 2) == 0
			&& i == cmd.size - 1)
			return (print_stderror(0, 1, "Missing: command after |\n"));
		i++;
	}
	return (TRUE);
}
