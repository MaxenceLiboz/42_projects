/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:55:50 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/02 12:01:50 by mliboz           ###   ########.fr       */
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
}

/*
	Add element to the end of the heredoc table
*/
// void	add_heredoc(t_heredoc *heredocs, t_string new, t_list **mem)
// {
// 	if ()
// }


;