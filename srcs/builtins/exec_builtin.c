/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 09:22:35 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/25 16:03:20 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_builtin(char **command, t_head_env *head, t_list **mem)
{
	if (ft_strncmp(command[0], "echo", 5) == 0)
		return (ft_echo(command));
	else if (ft_strncmp(command[0], "cd", 3) == 0)
		return (ft_cd(command, head, mem));
	else if (ft_strncmp(command[0], "pwd", 4) == 0)
		return (ft_pwd(command));
	if (ft_strncmp(command[0], "export", 7) == 0)
		return (ft_export(head, command, mem));
	else if (ft_strncmp(command[0], "unset", 6) == 0)
		return (ft_unset(&head, command));
	else if (ft_strncmp(command[0], "env", 4) == 0)
		return (ft_env(head->env, command));
	else if (ft_strncmp(command[0], "exit", 5) == 0)
		ft_exit(command);
	else
		return (-1);
	return (0);
}
