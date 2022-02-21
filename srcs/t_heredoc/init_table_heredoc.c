/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 10:57:54 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/21 13:34:49 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	DOCUMENTATION:
	
	$PATH => $PATH
	$'PATH' or $"PATH" => PATH
	$qwerty"PATH" => $qwertyPATH

	Doesn't expand envp with quotes or double quotes
	Expand envp without quotes or double quotes
*/

/*
	Check if heredoc and return adress
	Also check if pipe to increment the index of the table
*/
int	check_heredoc(char *str, int i, int *index)
{
	int		pipe;

	pipe = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			while (str[i] && str[++i] != '\"')
				;
		if (str[i] == '\'')
			while (str[i] && str[++i] != '\'')
				;
		if (str[i] == '|' && pipe == 0)
		{
			*index += 1;
			pipe++;
		}
		if (ft_strncmp(&str[i], "<<", 2) == 0)
			return (i);
		i++;
	}
	return (-1);
}

/*
	1:	check delimiter syntax
	2:	trim if needed
	3:	return if expand or not
*/
static t_bool	delimiter_syntax(t_string *string, int *i, t_prg *prg)
{
	int		i_cpy;

	while (string->str[*i] == ' ' && string->str[*i])
			*i += 1;
	i_cpy = *i;
	if (string->str[*i] == '$' && (string->str[*i + 1] == '\"'
			|| string->str[*i + 1] == '\''))
		erase_string(string, "$", *i, prg);
	while (string->str[i_cpy] != ' ' && string->str[i_cpy])
	{
		if (string->str[i_cpy] == '\"' || string->str[i_cpy] == '\'')
			return (FALSE);
		i_cpy++;
	}
	return (TRUE);
}

/*
	1: Call check_heredoc();
	2: Call	delimiter_syntax();
*/
void	init_table_heredoc(t_prg *prg, int *save)
{
	int			i;
	int			expand;

	i = check_heredoc(prg->cmd.command.str, *save, &prg->heredocs.index) + 2;
	while (i != 1)
	{
		*save = i;
		expand = delimiter_syntax(&prg->cmd.command, save, prg);
		add_heredoc(&prg->heredocs,
			get_heredoc(prg, expand, *save, prg->heredocs.index),
			prg->heredocs.index, prg);
		i = check_heredoc(prg->cmd.command.str, *save, &prg->heredocs.index);
		i += 2;
	}
}
