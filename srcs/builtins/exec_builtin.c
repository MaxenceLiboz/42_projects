/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 09:22:35 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/24 11:58:10 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


//Check which value we should return
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
	return (-1);
}
