/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:41:12 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/01/28 08:17:27 by maxencelibo      ###   ########.fr       */
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
		return (print_stderror(FALSE, 1, "Missing: both: \', \""));
	else if (squotes > 0)
		return (print_stderror(FALSE, 1, "Missing: \'"));
	else if (dquotes > 0)
		return (print_stderror(FALSE, 1, "Missing: \""));
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
			return (print_stderror(0, 1, "Missing: command after |"));
		i++;
	}
	return (TRUE);
}

static void	check_chevrons_p2(t_string *cmd, int i, int *chevrons, t_list **mem)
{
	if (cmd->str[i - 1] != ' ')
		add_string(cmd, " ", i, mem);
	*chevrons = 0;
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
		if ((cmd->str[i] == '>' || cmd->str[i] == '<')
			&& (dquotes < 0 || squotes < 0))
			chevrons++;
		else if (cmd->str[i] != '>' && cmd->str[i] != '<'
			&& cmd->str[i] != ' ' && chevrons != 0
			&& squotes < 1 && dquotes < 1)
			check_chevrons_p2(cmd, i, &chevrons, mem);
	}
	if (chevrons != 0)
		return (print_stderror(FALSE, 1, "syntax error"));
	return (TRUE);
}
