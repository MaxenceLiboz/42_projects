/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 10:37:01 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/07 15:25:42 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_exec_process(t_prg *prg, char **envp)
{
	int			i;
	t_string	cmd;

	i = exec_builtin(prg->lst_cmd->cmd, &prg->env, prg);
	if (i != 2)
		return (i);
	prg->fd.pid = fork();
	if (prg->fd.pid == -1)
		return (0);
	if (prg->fd.pid == 0)
	{
		init_string(&cmd, "", TRUE, &prg->mem);
		i = -1;
		if (!prg->paths)
			exit(print_stderror(127, 2, prg->lst_cmd->cmd[0],
					": No such file or directory"));
		while (prg->paths[++i])
		{
			cmd = join_string(prg->paths[i], prg->lst_cmd->cmd[0], &prg->mem);
			execve(cmd.str, prg->lst_cmd->cmd, envp);
		}
		cmd = sub_string(prg->lst_cmd->cmd[0], 1, cmd.size, &prg->mem);
		cmd = join_string(getcwd(0, 0), cmd.str, &prg->mem);
		execve(cmd.str, prg->lst_cmd->cmd, envp);
		exit(print_stderror(127, 2, prg->lst_cmd->cmd[0],
				": command not found"));
	}
	return (0);
}

int	ft_exec_one(t_prg *prg)
{
	char	**envp;
	int		status;

	envp = lst_env_to_array(prg->env.env, &prg->mem);
	check_cmd(prg, prg->lst_cmd);
	if (!prg->lst_cmd->cmd || !*prg->lst_cmd->cmd)
		return (FAIL);
	prg->lst_cmd->cmd = trim_quotes_unneeded(prg->lst_cmd->cmd, &prg->mem);
	prg->return_value = exec_builtin(prg->lst_cmd->cmd, &prg->env, prg);
	if (prg->return_value != 2)
		return (prg->return_value);
	prg->return_value = ft_exec_process(prg, envp);
	while (waitpid(-1, &status, 0) != -1)
		;
	if (WIFEXITED(status))
	{
        // printf("exited, status=%d\n", WEXITSTATUS(status));
		prg->return_value = WEXITSTATUS(status);
	}
	return (prg->return_value);
}

	// waitpid(-1, &prg->return_value, 0);
	// if (prg->return_value == 256)
	// 	return (1);
	// else
	// 	return (127);