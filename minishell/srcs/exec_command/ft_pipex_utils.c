/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 09:48:10 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/22 09:44:37 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Try execve
	Catch executable rights and store in variable
*/
void	ft_execve(char *cmd, char **args, char **envp, int *eacces)
{
	execve(cmd, args, envp);
	if (errno == EACCES)
		*eacces = TRUE;
}

/*
	Try execve for all the path in $PATH variable
*/
void	ft_exec_path(t_prg *prg, char **envp, int *eacces)
{
	int			i;
	t_string	cmd;
	struct stat	file;

	i = -1;
	while (prg->paths[++i])
	{
		cmd = join_string(prg->paths[i], prg->lst_cmd->cmd[0], prg);
		stat(cmd.str, &file);
		ft_execve(cmd.str, prg->lst_cmd->cmd, envp, eacces);
	}
}

/*
	Check if the command is a path
*/
t_bool	is_path(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/*
	check if the command is a bultin
*/
t_bool	is_builtin(t_prg *prg)
{
	char	**tmp;

	tmp = create_final_command(prg->lst_cmd->cmd, prg);
	if (ft_strncmp(tmp[0], "echo", 5) == 0)
		return (TRUE);
	else if (ft_strncmp(tmp[0], "cd", 3) == 0)
		return (TRUE);
	else if (ft_strncmp(tmp[0], "pwd", 4) == 0)
		return (TRUE);
	else if (ft_strncmp(tmp[0], "export", 7) == 0)
		return (TRUE);
	else if (ft_strncmp(tmp[0], "unset", 6) == 0)
		return (TRUE);
	else if (ft_strncmp(tmp[0], "env", 4) == 0)
		return (TRUE);
	else if (ft_strncmp(tmp[0], "tarchimb", 9) == 0 || ft_strncmp(tmp[0],
			"mliboz", 7) == 0)
		return (TRUE);
	else if (ft_strncmp(tmp[0], "exit", 5) == 0)
		return (TRUE);
	return (FALSE);
}

/*
	Put the right signal depending if we go on a child or open another instance 
	of minishell
*/
void	set_signals(char *cmd)
{
	if (ft_strnstr(cmd, "minishell", ft_strlen(cmd)) == NULL)
	{
		signal(SIGINT, (void (*)(int))handler_forked);
		signal(SIGQUIT, (void (*)(int))handler_forked);
	}
	else
		signal(SIGINT, SIG_IGN);
}
