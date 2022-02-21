/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 10:40:10 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/21 18:04:35 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Handle SIGINT and SIGQUIT inside Children
*/
void	handler_forked(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "^C\n", 3);
		g_returnvalue = 130;
	}
	if (signum == SIGQUIT)
	{
		write(1, "^\\Quit: 3\n", 10);
		g_returnvalue = 131;
	}
}

void	handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_returnvalue = 1;
		exit(1);
	}
}

/*
	Set the signal we have to handle in minishell
*/
void	set_signal(void)
{
	signal(SIGINT, handler_main);
	signal(SIGQUIT, SIG_IGN);
}
