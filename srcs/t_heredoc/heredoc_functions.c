/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:55:50 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/21 13:50:52 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Init the heredoc structure
*/
void	init_heredoc(t_heredoc *heredocs)
{
	heredocs->size = 0;
	heredocs->malloc_size = 0;
	heredocs->index = 0;
	heredocs->table = 0;
}

/*
	Realloc twice de size of the current heredoc table
*/
t_heredoc	realloc_heredoc(t_heredoc heredocs, t_prg *prg)
{
	t_heredoc	dst;

	init_heredoc(&dst);
	if (heredocs.malloc_size == 0)
	{
		dst.table = ft_malloc(prg, sizeof(t_string) * 2);
		dst.malloc_size = 2;
	}
	else
	{
		dst.table = ft_malloc(prg, sizeof(t_string)
				* heredocs.malloc_size * 2);
		dst.malloc_size *= 2;
	}
	dst.size = heredocs.size;
	dst.index = heredocs.index;
	dst.malloc_size = heredocs.malloc_size * 2;
	while (heredocs.size--)
		dst.table[heredocs.size] = heredocs.table[heredocs.size];
	return (dst);
}

/*
	Add element to the end of the heredoc table
	1: Check if malloc_size is enough and call realloc_heredoc();
*/
void	add_heredoc(t_heredoc *heredocs, t_string new, int index, t_prg *prg)
{
	if (!new.str)
		return ;
	if (heredocs->malloc_size == heredocs->size && heredocs->size <= index)
		*heredocs = realloc_heredoc(*heredocs, prg);
	heredocs->table[index] = new;
	if (heredocs->size <= index)
		heredocs->size += 1;
}
