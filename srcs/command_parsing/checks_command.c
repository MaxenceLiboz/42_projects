/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:41:12 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/02/17 09:35:33 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	If we have a special char and no space after check the next char:
		- If special add space between
		- Else next
*/
static void	add_space_after_special_char(t_string *cmd, int i, t_list **mem)
{
	if (cmd->str[i] != '|' && cmd->str[i + 1] != ' '
		&& cmd->str[i + 1] != '>' && cmd->str[i + 1] != '<')
		add_string(cmd, " ", i + 1, mem);
	if (cmd->str[i] != '|' && i != 0 && cmd->str[i - 1] != ' '
		&& cmd->str[i - 1] != '>' && cmd->str[i - 1] != '<')
		add_string(cmd, " ", i, mem);
	if (cmd->str[i] == '|' && cmd->str[i + 1] != ' ' && cmd->str[i + 1] != '|')
		add_string(cmd, " ", i + 1, mem);
	if (i != 0 && cmd->str[i] == '|' && cmd->str[i - 1] != ' '
		&& cmd->str[i - 1] != '|')
		add_string(cmd, " ", i, mem);
}

/*
	Add a space after << or >>
*/
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

/*
	Check if their is a delimiter
*/
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

/*
	Find special char < > || and add space if needed
*/
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
			while (cmd->str[++i] && cmd->str[i] != '\"')
				;
		if (cmd->str[i] == '\'')
			while (cmd->str[++i] && cmd->str[i] != '\'')
				;
		if ((cmd->str[i] == '>' || cmd->str[i] == '<' || cmd->str[i] == '|'))
			add_space_after_special_char(cmd, i, mem);
		if (is_delimiter_heredoc(cmd, i) == FALSE)
			return (print_stderror(FAIL, 1, "syntax error"));
	}	
	return (SUCCESS);
}
