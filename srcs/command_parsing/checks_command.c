/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:41:12 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/02/04 16:19:31 by mliboz           ###   ########.fr       */
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

static void	add_space_after_special_char(t_string *cmd, int i, t_list **mem)
{
	if (cmd->str[i + 1] != ' '
		&& cmd->str[i + 1] != '>' && cmd->str[i + 1] != '<')
		add_string(cmd, " ", i + 1, mem);
	if (i != 0 && cmd->str[i - 1] != ' '
		&& cmd->str[i - 1] != '>' && cmd->str[i - 1] != '<')
		add_string(cmd, " ", i, mem);
	if (cmd->str[i] == '|' && cmd->str[i + 1] != ' ' && cmd->str[i + 1] != '|')
		add_string(cmd, " ", i + 1, mem);
	if (i != 0 && cmd->str[i] == '|' && cmd->str[i - 1] != ' '
		&& cmd->str[i - 1] != '|')
		add_string(cmd, " ", i, mem);
}

static void	add_space_after_db_chevrons(t_string *cmd, t_list **mem)
{
	int		i;

	i = -1;
	while (cmd->str[++i])
	{
		if (cmd->str[i] == '\"')
			while (cmd->str[i] && cmd->str[++i] != '\"')
				;
		if (cmd->str[i] == '\'')
			while (cmd->str[i] && cmd->str[++i] != '\'')
				;
		if (ft_strncmp(&cmd->str[i], "<<", 2) == 0
			|| ft_strncmp(&cmd->str[i], ">>", 2) == 0)
			if (cmd->str[i + 2] == '<' || cmd->str[i + 2] == '>'
				|| cmd->str[i + 2] == '|')
				add_string(cmd, " ", i + 2, mem);
	}
}

static t_bool	is_delimiter_heredoc(t_string *cmd, int i)
{
	if (ft_strncmp(&cmd->str[i], "<<", 2) == 0
		|| ft_strncmp(&cmd->str[i], ">>", 2) == 0)
	{
		i += 2;
		while (cmd->str[i] && cmd->str[i] == ' ')
			i++;
		if (cmd->str[i] == '>' || cmd->str[i] == '<' || cmd->str[i] == '|')
			return (FALSE);
	}
	else if (cmd->str[i] == '<' || cmd->str[i] == '>')
	{
		i += 1;
		while (cmd->str[i] && cmd->str[i] == ' ')
			i++;
		if (cmd->str[i] == 0
			|| cmd->str[i] == '>' || cmd->str[i] == '<' || cmd->str[i] == '|')
			return (FALSE);
	}
	return (TRUE);
}

t_bool	syntax_special_char(t_string *cmd, t_list **mem)
{
	int		i;
	int		chevrons;

	i = -1;
	chevrons = 0;
	add_space_after_db_chevrons(cmd, mem);
	while (cmd->str[++i])
	{
		if (cmd->str[i] == '\"')
			while (cmd->str[i] && cmd->str[++i] != '\"')
				;
		if (cmd->str[i] == '\'')
			while (cmd->str[i] && cmd->str[++i] != '\'')
				;
		if ((cmd->str[i] == '>' || cmd->str[i] == '<' || cmd->str[i] == '|'))
			add_space_after_special_char(cmd, i, mem);
		if (is_delimiter_heredoc(cmd, i) == FALSE)
			return (print_stderror(FAIL, 1, "syntax error"));
	}	
	return (SUCCESS);
}
