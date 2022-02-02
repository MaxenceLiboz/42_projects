/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:41:12 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/02/02 08:43:15 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

static void	check_chevrons_p2(t_string *cmd, int i, int *chevrons, t_list **mem)
{
	if (cmd->str[i + 1] != ' '
		&& cmd->str[i + 1] != '>' && cmd->str[i + 1] != '<')
		add_string(cmd, " ", i + 1, mem);
	if (cmd->str[i - 1] != ' '
		&& cmd->str[i - 1] != '>' && cmd->str[i - 1] != '<')
		add_string(cmd, " ", i, mem);
	if (cmd->str[i] == '|' && cmd->str[i + 1] != ' ' && cmd->str[i + 1] != '|')
		add_string(cmd, " ", i + 1, mem);
	if (cmd->str[i] == '|' && cmd->str[i - 1] != ' ' && cmd->str[i - 1] != '|')
		add_string(cmd, " ", i, mem);
	if (cmd->str[i] == '<' || cmd->str[i] == '>')
		*chevrons += 1;
}

t_bool	check_chevrons(t_string *cmd, t_list **mem)

{
	int		i;
	int		chevrons;
	int		squotes;
	int		dquotes;

	i = -1;
	chevrons = 0;
	dquotes = -1;
	squotes = -1;
	while (cmd->str[++i])
	{
		if (cmd->str[i] == '\"' && squotes < 0)
			dquotes *= -1;
		if (cmd->str[i] == '\'' && dquotes < 0)
			squotes *= -1;
		if ((cmd->str[i] == '>' || cmd->str[i] == '<' || cmd->str[i] == '|')
			&& (dquotes < 0 || squotes < 0))
			check_chevrons_p2(cmd, i, &chevrons, mem);
		else if (cmd->str[i] != '>' && cmd->str[i] != '<'
			&& cmd->str[i] != ' ' && chevrons != 0
			&& squotes < 1 && dquotes < 1)
			chevrons = 0;
	}
	if (chevrons != 0)
		return (print_stderror(FAIL, 1, "syntax error"));
	return (SUCCESS);
}
