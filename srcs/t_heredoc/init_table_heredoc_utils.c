/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table_heredoc_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:26:33 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/22 10:55:30 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Find envp varaible or $? and replace it by its value
*/
void	change_arg_command_heredoc(t_prg *prg, t_string *str)
{
	int			index;

	index = 0;
	while (str->str[index])
	{
		if (is_arg(str->str, &index) == TRUE)
			find_arg_and_replace(prg, index, str);
		index++;
	}
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

static t_string	launch_heredoc(t_prg *prg, int expand, int fd, int i)
{
	char		*line;
	t_string	temp;
	char		*delimiter;
	t_string	prompt;

	signal(SIGINT, (void (*)(int))handler_heredoc);
	init_string(&prompt, "here_doc \"\" > ", TRUE, prg);
	delimiter = get_delimiter(&prg->cmd.command.str[i], prg);
	add_string(&prompt, delimiter, 10, prg);
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
			change_arg_command_heredoc(prg, &temp);
		write(fd, temp.str, temp.size - 1);
		write(fd, "\n", 1);
	}
	ft_close(fd, prg);
	exit(0);
}

/*
	Add string to here_doc table
*/
t_string	get_heredoc(t_prg *prg, int expand, int i, int h_index)
{
	t_string	file;
	int			fd;
	int			status;

	signal(SIGINT, SIG_IGN);
	file.str = NULL;
	fd = get_file_heredoc(&file, prg, h_index);
	prg->fd.pid = fork();
	if (prg->fd.pid == -1)
		return (file);
	if (prg->fd.pid == 0)
		launch_heredoc(prg, expand, fd, i);
	else
	{	
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		if (status == 1)
			file.str = NULL;
		ft_close(fd, prg);
		return (file);
	}
	return (file);
}
