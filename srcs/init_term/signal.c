/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 10:40:10 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/12 13:04:04 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handler_forked(int signum, int *return_value)
{
	if (signum == SIGINT)
		write(1, "^C\n", 3);
	if (signum == -1)
		*return_value = 130;
}

void	set_signal(void)
{
	signal(SIGINT, handler_main);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGABRT, SIG_IGN);
	signal(SIGALRM, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}