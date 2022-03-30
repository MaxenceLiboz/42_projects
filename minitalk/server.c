/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:23:13 by mliboz            #+#    #+#             */
/*   Updated: 2021/12/12 14:34:06 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("The PID is: %d\nWaiting for a signal...\n", pid);
	while (1)
	{
		signal(SIGUSR1, sighandler);
		signal(SIGUSR2, sighandler);
		usleep(50);
	}
}
