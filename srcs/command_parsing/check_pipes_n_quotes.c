/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes_n_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:52:31 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/16 17:54:06 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Check if both single and double quotes are closed or return error
*/
t_bool	check_quotes(t_string cmd)
{
	int		squotes;
	int		dquotes;
	int		i;

	squotes = -1;
	dquotes = -1;
	i = 0;
	while (cmd.str[i])
	{
		if (cmd.str[i] == '\"' && squotes < 0)
			dquotes *= -1;
		if (cmd.str[i] == '\'' && dquotes < 0)
			squotes *= -1;
		i++;
	}
	if (squotes > 0 && dquotes > 0)
		return (print_stderror(FAIL, 1, "Missing: both: \', \""));
	else if (squotes > 0)
		return (print_stderror(FAIL, 1, "Missing: \'"));
	else if (dquotes > 0)
		return (print_stderror(FAIL, 1, "Missing: \""));
	return (SUCCESS);
}

/*
	If return:
		Fail => need to ask for the following of the command
		Success => Command is finished
		-1 => Syntaxe error with pipe
	
*/
t_bool	check_pipes(t_command cmd)
{
	int		i;
	int		pipes;

	i = 0;
	pipes = 0;
	if (!cmd.command.str || cmd.size == 0)
		return (FAIL);
	if (ft_strncmp(cmd.array[0].str, "|", 2) == 0)
		return (print_stderror(-1, 1,
				"syntax error near unexpected token `|'"));
	while (i < cmd.size)
	{
		if (ft_strncmp(cmd.array[i].str, "|", 2) == 0
			&& i == cmd.size - 1)
			return (FAIL);
		if (ft_strncmp(cmd.array[i].str, "|", 2) == 0
			&& i < cmd.size && ft_strncmp(cmd.array[i + 1].str, "|", 2) == 0)
			return (print_stderror(-1, 1,
					"syntax error near unexpected token `|'"));
		i++;
	}
	return (SUCCESS);
}
