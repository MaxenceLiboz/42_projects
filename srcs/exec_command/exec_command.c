/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 08:20:07 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/01/27 09:41:39 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**get_path(t_lst_env *export, t_list **mem)
{
	t_string	envp_path;
	t_string	*paths;
	char		**dst;
	int			i;

	i = 0;
	envp_path = lst_env_find_name_var(export, "PATH");
	if (!envp_path.str)
		return (0);
	paths = split_string(envp_path.str, ':', mem);
	if (!paths)
		ft_error_free(mem);
	while (paths[i].str)
	{
		add_string(&paths[i], "/", paths[i].size - 1, mem);
		i++;
	}
	dst = strings_to_array(paths, mem);
	return (dst);
}

int	ft_execve(t_prg *prg, char **envp)
{
	int			i;
	t_string	cmd;

	prg->fd.pid = fork();
	if (prg->fd.pid == 0)
	{
		if (prg->fd.fd_in > 0)
			dup2(prg->fd.fd_in, STDIN);
		if (prg->fd.fd_out > 0)
			dup2(prg->fd.fd_out, STDOUT);
		init_string(&cmd, "", TRUE, &prg->mem);
		i = -1;
		while (prg->paths[++i])
		{
			cmd = join_string(prg->paths[i], prg->lst_cmd->cmd[0], &prg->mem);
			execve(cmd.str, prg->lst_cmd->cmd, envp);
		}
		print_stderror(-1, 2, prg->lst_cmd->cmd[0], ": command not found");
	}
	return (0);
}

int	exec_one(t_prg *prg)
{
	char	**envp;
	int		return_value;

	envp = lst_env_to_array(prg->env.env, &prg->mem);
	if (check_cmd(prg, prg->lst_cmd) == -1)
		return (-1);
	if (!prg->lst_cmd->cmd || !*prg->lst_cmd->cmd)
		return (-1);
	return_value = exec_builtin(prg->lst_cmd->cmd, &prg->env, prg);
	if (return_value != -1)
		return (return_value);
	prg->paths = get_path(prg->env.export, &prg->mem);
	ft_execve(prg, envp);
	waitpid(-1, 0, 0);
	return (-1);
}

int	exec_command(t_prg *prg)
{
	int			return_value;

	errno = 0;
	return_value = 1;
	if (lst_cmd_size(prg->lst_cmd) == 1)
		return_value = exec_one(prg);
	// else
	// 	ft_pipex();
	
	return (return_value);
}
