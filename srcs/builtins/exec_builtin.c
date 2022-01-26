/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 09:22:35 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/26 10:55:17 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_builtin(char **command, t_head_env *head, t_prg *prg)
{
	int	saved;
	int	return_value;

	return_value = -1;
	saved = dup(STDOUT_FILENO);
	if (prg->fd.fd_out > 0)
		dup2(prg->fd.fd_out, STDOUT_FILENO);
	if (ft_strncmp(command[0], "echo", 5) == 0)
		return_value = ft_echo(command);
	else if (ft_strncmp(command[0], "cd", 3) == 0)
		return_value = ft_cd(command, head, &prg->mem);
	else if (ft_strncmp(command[0], "pwd", 4) == 0)
		return_value = ft_pwd(command);
	else if (ft_strncmp(command[0], "export", 7) == 0)
		return_value = ft_export(head, command, &prg->mem);
	else if (ft_strncmp(command[0], "unset", 6) == 0)
		return_value = ft_unset(&head, command);
	else if (ft_strncmp(command[0], "env", 4) == 0)
		return_value = ft_env(head->env, command);
	else if (ft_strncmp(command[0], "exit", 5) == 0)
		ft_exit(command);
	dup2(saved, STDOUT_FILENO);
	close(saved);
	return (return_value);
}
