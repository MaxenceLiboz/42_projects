/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:59:48 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/15 10:43:34 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ' ')
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

void	ft_exit(char **str, t_prg *prg)
{
	int		nb;

	if (prg->fd.pid != 0)
		ft_putstr_fd("exit\n", 2);
	if (!str)
	{
		tcsetattr(0, TCSANOW, &prg->old);
		ft_lstclear(&prg->mem, free);
		exit(g_returnvalue);
	}
	if (!str[1])
	{
		ft_lstclear(&prg->mem, free);
		tcsetattr(0, TCSANOW, &prg->old);
		exit(g_returnvalue);
	}
	if (!isnum(str[1]) || !is_atoll(ft_atoll(str[1]), str[1]))
		print_exit(str[1], ": numeric argument required", 255, &prg->mem);
	if (str[2])
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		g_returnvalue = 1;
		return ;
	}
	nb = ft_atoll(str[1]);
	ft_lstclear(&prg->mem, free);
	tcsetattr(0, TCSANOW, &prg->old);
	exit(nb);
}
