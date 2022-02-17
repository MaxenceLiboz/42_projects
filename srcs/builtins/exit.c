/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:59:48 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/17 10:25:12 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Check if the argument is numerical
*/
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

/*
	use print_stderror();
	use ft_lst_clear();
	exit with variable r
*/
static void	print_exit(char *arg, char *msg, int exit_value, t_prg *prg)
{
	print_stderror(0, 3, "exit: ", arg, msg);
	ft_lstclear_all(&prg->mem, &prg->old);
	exit(exit_value);
}

/*
	Clear list
	Set terminal termios to old
	Exit with exit_status
*/
static void	exit_prg(t_prg *prg, int exit_status)
{
	ft_lstclear_all(&prg->mem, &prg->old);
	exit(exit_status);
}

/*
	Reproducing exit command in bash
	The first argument become the exit status
	The garbage collector is freed
*/
void	ft_exit(char **str, t_prg *prg)
{
	int		nb;

	if (prg->fd.pid != 0)
		ft_putstr_fd("exit\n", 2);
	if (!str || str[1])
		exit_prg(prg, g_returnvalue);
	if (!isnum(str[1]) || !is_atoll(ft_atoll(str[1]), str[1]))
		print_exit(str[1], ": numeric argument required", 255, prg);
	if (str[2])
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		g_returnvalue = 1;
		return ;
	}
	nb = ft_atoll(str[1]);
	exit_prg(prg, nb);
}
