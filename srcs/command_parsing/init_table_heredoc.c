/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 10:57:54 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/02 11:58:49 by mliboz           ###   ########.fr       */
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
*/
static int	check_heredoc(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == "\"")
			while (str[i] != "\"")
				i++;
		if (str[i] == "\'")
			while (str[i] != "\'")
				i++;
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
	int		i;
	int		expand;

	while (string->str[*i] == ' ' && string->str[*i])
			*i += 1;
	if (string->str[*i] == '$' && (string->str[*i + 1] == '\"'
			|| string->str[*i + 1] == '\''))
		erase_string(string, "$", i, mem);
	while (string->str[*i] != ' ' && string->str[*i])
		if (string->str[*i] == '\"' || string->str[*i] == '\'')
			return (FALSE);
	return (TRUE);
}

/*
	Get delimiter
*/
static char	*get_delimiter(char *str, t_list **mem)
{
	int			end;
	t_string	delimiter;

	end = 0;
	while (str[end] && str[end] != " ")
	{
		if (str[end] == "\"")
			while (str[end] != "\"")
				end++;
		if (str[end] == "\'")
			while (str[end] != "\'")
				end++;
		end++;
	}
	return ((delimiter = sub_string(str, 0, end, mem)).str);
}

/*
	Add string to here_doc table
*/
static t_string	get_heredoc(t_prg *prg, int expand, int i)
{
	char		*delimiter;
	t_string	temp;
	t_string	final_str;

	init_string(&final_str, "", TRUE, &prg->mem);
	delimiter = get_delimiter(&prg->cmd.command.str[i], &prg->mem);
	while (1)
	{
		init_string(&temp, readline("here_doc > "), TRUE, &prg->mem);
		if (check_limiter(delimiter, temp.str) == SUCCESS)
			break ;
		if (expand == TRUE)
			change_arg_command(prg, &temp);
		add_string(&final_str, temp.str, final_str.size - 1, &prg->mem);
	}
	return (final_str);
}

/*
	1: Call check_heredoc();
	2: Call	delimiter_syntax();
*/
void	init_table_heredoc(t_prg *prg)
{
	int		i;
	int		expand;

	i = 0;
	while (check_heredoc(prg->cmd.command.str, i) != -1)
	{
		i = check_heredoc(prg->cmd.command.str, i) + 2;
		expand = delimiter_syntax(&prg->cmd.command, &i, &prg->mem);
		add_heredoc(&prg->heredocs,
			get_heredoc(prg, expand, i), &prg->mem);
	}
}
