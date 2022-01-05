/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 09:22:35 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/05 09:29:41 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_builtin(char **str)
{
	if (ft_strncmp(str[0], "echo", 5) == 0)
		echo(str);
	else if (ft_strncmp(str[0], "cd", 3) == 0)
		cd(str);
	else if (ft_strncmp(str[0], "pwd", 4) == 0)
		pwd(str);
	else if (ft_strncmp(str[0], "export", 7) == 0)
		export(str);
	else if (ft_strncmp(str[0], "unset", 6) == 0)
		unset(str);
	else if (ft_strncmp(str[0], "env", 4) == 0)
		env(str);
	else if (ft_strncmp(str[0], "exit", 5) == 0)
		exit(str);
	else
		return (0);
	return (1);
}
