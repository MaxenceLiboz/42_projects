/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 09:22:35 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/14 10:16:06 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_builtin(char **command, t_head_env *head, t_prg *prg)
{
	if (ft_strncmp(command[0], "echo", 5) == 0)
		g_returnvalue = ft_echo(command);
	else if (ft_strncmp(command[0], "cd", 3) == 0)
		g_returnvalue = ft_cd(command, head, &prg->mem, &prg->pwd);
	else if (ft_strncmp(command[0], "pwd", 4) == 0)
		g_returnvalue = ft_pwd(prg->pwd);
	else if (ft_strncmp(command[0], "export", 7) == 0)
		g_returnvalue = ft_export(head, command, &prg->mem);
	else if (ft_strncmp(command[0], "unset", 6) == 0)
		g_returnvalue = ft_unset(&head, command);
	else if (ft_strncmp(command[0], "env", 4) == 0)
		g_returnvalue = ft_env(head->env, command);
	else if (ft_strncmp(command[0], "tarchimb", 9) == 0 || ft_strncmp(command[0]
			, "mliboz", 7) == 0)
		g_returnvalue = biography(command[0]);
	else if (ft_strncmp(command[0], "exit", 5) == 0)
		ft_exit(command, prg);
	else
		return (2);
	return (g_returnvalue);
}
