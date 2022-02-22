/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table_heredoc_utils2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:55:44 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/22 11:00:43 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Check if filename already exist in heredoc
*/
static t_bool	is_existing_heredoc(t_string file, t_prg *prg, int h_index)
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
		init_string(file, "/private/tmp/.heredoc", TRUE, prg);
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
