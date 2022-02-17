/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table_heredoc_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:26:33 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/17 12:31:09 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
static char	*get_delimiter(char *str, t_prg *prg)
{
	int			i;
	int			y;
	int			size;
	t_string	delimiter;

	i = 0;
	y = 0;
	size = get_delimiter_size(str);
	delimiter.str = ft_malloc(prg, sizeof(char) * size + 1);
	while (i < size)
	{
		while (str[y] == '\'' || str[y] == '\"')
			y++;
		delimiter.str[i++] = str[y++];
	}
	delimiter.str[i] = '\0';
	return (delimiter.str);
}

static t_string	launch_heredoc(t_prg *prg, int expand,
	t_string prompt, char *delimiter)
{
	char		*line;
	t_string	temp;
	t_string	final_str;

	line = NULL;
	init_string(&final_str, "", TRUE, prg);
	while (1)
	{
		line = readline(prompt.str);
		if (!line)
			break ;
		init_string(&temp, line, TRUE, prg);
		free(line);
		if (ft_strncmp(delimiter, temp.str, ft_strlen(delimiter) + 1) == 0)
			break ;
		if (expand == TRUE)
			change_arg_command(prg, &temp);
		add_string(&final_str, temp.str, final_str.size - 1, prg);
		add_string(&final_str, "\n", final_str.size - 1, prg);
	}
	return (final_str);
}

/*
	Add string to here_doc table
*/
t_string	get_heredoc(t_prg *prg, int expand, int i)
{
	char		*delimiter;
	t_string	prompt;

	init_string(&prompt, "here_doc \"\" > ", TRUE, prg);
	delimiter = get_delimiter(&prg->cmd.command.str[i], prg);
	add_string(&prompt, delimiter, 10, prg);
	return (launch_heredoc(prg, expand, prompt, delimiter));
}
