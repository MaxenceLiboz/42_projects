/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:59:48 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/18 14:58:28 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	isnum(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **str)
{
	printf("exit\n");
	if (!str[1])
		exit(0);
	if (!isnum(str[1]))
	{
		print_stderror(3, "bash: exit: ", str[1],
			": numeric argument required\n");
		exit(255);
	}
	if (str[2])
	{
		if (ft_strncmp(str[2], "|", 2) != 0)
		{
			print_stderror(1, "bash: exit: too many arguments\n");
			exit(255);
		}
	}
	exit(ft_atoi(str[1]));
}