/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 10:57:54 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/09 15:42:05 by mliboz           ###   ########.fr       */
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
static t_bool	delimiter_syntax(t_string *string, int *i, t_list **mem)
{
	int		i_cpy;

	while (string->str[*i] == ' ' && string->str[*i])
			*i += 1;
	i_cpy = *i;
	if (string->str[*i] == '$' && (string->str[*i + 1] == '\"'
			|| string->str[*i + 1] == '\''))
		erase_string(string, "$", *i, mem);
	while (string->str[i_cpy] != ' ' && string->str[i_cpy])
	{
		if (string->str[i_cpy] == '\"' || string->str[i_cpy] == '\'')
			return (FALSE);
		i_cpy++;
	}
	return (TRUE);
}

/*
	Get delimiter size
*/
static int	get_delimiter_size(char *str)
{
	int		size;
	int		quotes;

	size = 0;
	quotes = 0;
	while (str[size] && str[size] != ' '
		&& str[size] != '>' && str[size] != '<' && str[size] != '|')
	{
		if (str[size] == '\"')
		{
			while (str[++size] != '\"')
				;
			quotes += 2;
		}
		if (str[size] == '\'')
		{
			while (str[++size] != '\'')
				;
			quotes += 2;
		}
		size++;
	}
	return (size - quotes);
}

/*
	Get delimiter
*/
static char	*get_delimiter(char *str, t_list **mem)
{
	int			i;
	int			y;
	int			size;
	t_string	delimiter;

	i = 0;
	y = 0;
	size = get_delimiter_size(str);
	delimiter.str = ft_malloc(mem, sizeof(char) * size + 1);
	while (i < size)
	{
		while (str[y] == '\'' || str[y] == '\"')
			y++;
		delimiter.str[i++] = str[y++];
	}
	return (delimiter.str);
}

/*
	Add string to here_doc table
*/
static t_string	get_heredoc(t_prg *prg, int expand, int i)
{
	char		*delimiter;
	t_string	temp;
	t_string	final_str;
	t_string	prompt;
	char		*line;

	line = NULL;
	init_string(&final_str, "", TRUE, &prg->mem);
	init_string(&prompt, "here_doc \"\" > ", TRUE, &prg->mem);
	delimiter = get_delimiter(&prg->cmd.command.str[i], &prg->mem);
	add_string(&prompt, delimiter, 10, &prg->mem);
	while (1)
	{
		line = readline(prompt.str);
		init_string(&temp, line, TRUE, &prg->mem);
		if (!line)
			break ;
		if (ft_strncmp(delimiter, temp.str, ft_strlen(delimiter) + 1) == 0)
			break ;
		if (expand == TRUE)
			change_arg_command(prg, &temp);
		add_string(&final_str, temp.str, final_str.size - 1, &prg->mem);
		add_string(&final_str, "\n", final_str.size - 1, &prg->mem);
	}
	return (final_str);
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
		expand = delimiter_syntax(&prg->cmd.command, save, &prg->mem);
		add_heredoc(&prg->heredocs,
			get_heredoc(prg, expand, *save), prg->heredocs.index, &prg->mem);
		i = check_heredoc(prg->cmd.command.str, *save, &prg->heredocs.index);
		i += 2;
	}
}
