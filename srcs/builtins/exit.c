/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:59:48 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/31 15:32:41 by tarchimb         ###   ########.fr       */
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

static void	print_exit(char *arg, char *msg, int r, t_list **mem)
{
	print_stderror(0, 3, "exit: ", arg, msg);
	ft_lstclear(mem, free);
	exit(r);
}

void	ft_exit(char **str, t_list **mem)
{
	int		nb;

	printf("exit\n");
	if (!str[1])
	{
		ft_lstclear(mem, free);
		exit(0);
	}
	if (!isnum(str[1]) || !is_atoll(ft_atoll(str[1]), str[1]))
		print_exit(str[1], ": numeric argument required", 255, mem);
	if (str[2])
	{
		if (ft_strncmp(str[2], "|", 2) != 0)
			print_exit(NULL, "too many arguments", 255, mem);
	}
	nb = ft_atoll(str[1]);
	ft_lstclear(mem, free);
	exit(nb);
}
