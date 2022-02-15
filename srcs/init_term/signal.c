/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 10:40:10 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/15 11:23:05 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handler_forked(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "^C\n", 3);
		g_returnvalue = 130;
	}
}

void	set_signal(void)
{
	signal(SIGINT, handler_main);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGABRT, SIG_IGN);
	signal(SIGALRM, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}