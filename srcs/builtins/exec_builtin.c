/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 09:22:35 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/01 08:24:53 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_builtin(char **command, t_head_env *head, t_prg *prg)
{
	int	return_value;

	return_value = 2;
	double_dup(prg->fd.fd_in, prg->fd.fd_out, &prg->mem);
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
	else if (ft_strncmp(command[0], "tarchimb", 9) == 0 || ft_strncmp(command[0]
			, "mliboz", 7) == 0)
		return_value = biography(command[0]);
	else if (ft_strncmp(command[0], "exit", 5) == 0)
		ft_exit(command, &prg->mem);
	return (return_value);
}
