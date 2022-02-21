/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table_heredoc_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:26:33 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/21 14:32:43 by mliboz           ###   ########.fr       */
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

// static t_string	launch_heredoc(t_prg *prg, int expand,
// 	t_string prompt, char *delimiter)
// {
// 	char		*line;
// 	t_string	temp;
// 	t_string	final_str;

// 	line = NULL;
// 	init_string(&final_str, "", TRUE, prg);
// 	while (1)
// 	{
// 		if (*get_static_delimiter() == FALSE)
// 			break ;
// 		line = readline(prompt.str);
// 		if (!line)
// 			break ;
// 		init_string(&temp, line, TRUE, prg);
// 		free(line);
// 		if (ft_strncmp(delimiter, temp.str, ft_strlen(delimiter) + 1) == 0)
// 			break ;
// 		if (expand == TRUE)
// 			change_arg_command_heredoc(prg, &temp);
// 		add_string(&final_str, temp.str, final_str.size - 1, prg);
// 		add_string(&final_str, "\n", final_str.size - 1, prg);
// 	}
// 	*get_static_delimiter() = TRUE;
// 	return (final_str);
// }

// /*
// 	Add string to here_doc table
// */
// t_string	get_heredoc(t_prg *prg, int expand, int i)
// {
// 	char		*delimiter;
// 	t_string	prompt;

// 	init_string(&prompt, "here_doc \"\" > ", TRUE, prg);
// 	delimiter = get_delimiter(&prg->cmd.command.str[i], prg);
// 	add_string(&prompt, delimiter, 10, prg);
// 	return (launch_heredoc(prg, expand, prompt, delimiter));
// }

/*
	Check if filename already exist in heredoc
*/
t_bool	is_existing_heredoc(t_string file, t_prg *prg, int h_index)
{
	int		i;

	i = 0;
	while (i < prg->heredocs.size && prg->heredocs.table
		&& prg->heredocs.table[i].str)
	{
		if (i != h_index && ft_strncmp(file.str, prg->heredocs.table[i].str,
				file.size - 1) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/*
	Get the file name
*/
int	get_file_heredoc(t_string *file, t_prg *prg, int h_index)
{
	int			index;
	char		*index_char;
	int			fd;

	index = 0;
	fd = -1;
	while (fd < 0)
	{
		init_string(file, "/tmp/.heredoc", TRUE, prg);
		index_char = ft_itoa(index);
		if (index_char == NULL)
			ft_error_exit(prg, 1, "itoa: malloc error");
		add_string(file, index_char, file->size - 1, prg);
		if (is_existing_heredoc(*file, prg, h_index) == FALSE)
			fd = open(file->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
		index++;
	}
	return (fd);
}

static t_string	launch_heredoc(t_prg *prg, int expand, int fd, int i)
{
	char		*line;
	t_string	temp;
	char		*delimiter;
	t_string	prompt;

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

	file.str = NULL;
	fd = get_file_heredoc(&file, prg, h_index);
	prg->fd.pid = fork();
	if (prg->fd.pid == -1)
		return (file);
	if (prg->fd.pid == 0)
		launch_heredoc(prg, expand, fd, i);
	waitpid(-1, NULL, 0);
	ft_close(fd, prg);
	return (file);
}
