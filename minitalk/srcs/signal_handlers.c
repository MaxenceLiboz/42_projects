/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 14:34:20 by mliboz            #+#    #+#             */
/*   Updated: 2021/12/12 14:35:40 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	put_bytes(char **str)
{
	int		size;
	char	*s2;

	size = 8 - ft_strlen(*str);
	while (size--)
	{
		s2 = ft_strdup("0");
		*str = ft_strjoin(s2, *str);
	}
}

void	send_signal(char *str, int pid)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '0')
			kill(pid, SIGUSR1);
		if (str[i] == '1')
			kill(pid, SIGUSR2);
		usleep(150);
		i++;
	}
}

static void	reinit_str(char **str)
{
	int		i;

	i = 0;
	while (str[0][i])
		str[0][i++] = 0;
}

static void	handle_word(char **save, char *str)
{
	static char	*string;

	if (ft_strncmp(*save, "00000000", 8) == 0)
	{
		if (ft_strncmp(string, "exit", 4) == 0)
			exit(1);
		ft_printf("%s\n", string);
		reinit_str(&string);
	}
	str = malloc(sizeof(char) * 2);
	if (!str)
		exit(1);
	str[0] = ft_atoi_base(*save, BASE2);
	str[1] = 0;
	string = ft_strjoin(string, str);
	reinit_str(save);
}

void	sighandler(int signum)
{
	static char	*save;
	static int	index = 0;
	char		*str;

	if (signum == 31)
		str = ft_strdup("1");
	else if (signum == 30)
		str = ft_strdup("0");
	else
		return ;
	index++;
	save = ft_strjoin(save, str);
	if (index % 8 == 0)
		handle_word(&save, str);
}
