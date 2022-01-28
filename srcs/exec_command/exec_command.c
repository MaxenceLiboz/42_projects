/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 08:20:07 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/01/28 15:27:22 by maxencelibo      ###   ########.fr       */
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
		ft_error_free(mem, "envp_path.str: error not found");
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

	i = exec_builtin(prg->lst_cmd->cmd, &prg->env, prg);
	if (i != 2)
		return (i);
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
		exit(print_stderror(2, 2, prg->lst_cmd->cmd[0],
				": command not found"));
	}
	return (0);
}

void	double_dup(int fd1, int fd2, t_list **mem)
{
	if (dup2(fd1, STDIN_FILENO) == -1)
		ft_error_free(mem, "error: STDIN dup failed");
	if (dup2(fd2, STDOUT_FILENO) == -1)
		ft_error_free(mem, "error: STDOUT dup failed");
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
	return_value = ft_execve(prg, envp);
	waitpid(-1, &return_value, 0);
	if (return_value == 0)
		return (0);
	else if (return_value == 1)
		return (1);
	else if (return_value == 256)
		return (1);
	else
		return (127);
	return (-1);
}

void	ft_exec_process(t_prg *prg, char **envp)
{
	int			i;
	t_string	cmd;

	i = -1;
	while (prg->paths[++i])
	{
		cmd = join_string(prg->paths[i], prg->lst_cmd->cmd[0], &prg->mem);
		execve(cmd.str, prg->lst_cmd->cmd, envp);
	}
	exit(print_stderror(2, 2, prg->lst_cmd->cmd[0],
			": command not found"));
}

void	ft_get_fd(t_prg *prg, int *j, char **envp)
{
	pipe(prg->fd.fd);
	prg->fd.pid = fork();
	if (prg->fd.pid != 0)
	{
		close(prg->fd.fd[1]);
		dup2(prg->fd.fd[0], STDIN);
		close(prg->fd.fd[0]);
	}
	else
	{
		close(prg->fd.fd[0]);
		if (*j != prg->fd.pipe_nb + 1)
			dup2(prg->fd.fd[1], STDOUT);
		close(prg->fd.fd[1]);
		check_cmd(prg, prg->lst_cmd);
		ft_exec_process(prg, envp);
	}
}

int	ft_pipex(t_prg *prg)
{
	int		j;
	char	**envp;
	int		stdin_save;
	int		stdout_save;

	stdin_save = dup(STDIN_FILENO);
	stdout_save = dup(STDOUT_FILENO);
	envp = lst_env_to_array(prg->env.env, &prg->mem);
	j = 1;
	prg->fd.pipe_nb = lst_cmd_size(prg->lst_cmd);
	dup2(prg->fd.fd_in, STDIN);
	dup2(prg->fd.fd_out, STDOUT);
	while (++j <= prg->fd.pipe_nb + 1)
	{
		ft_get_fd(prg, &j, envp);
		prg->lst_cmd = prg->lst_cmd->next;
	}
	while (waitpid(-1, 0, 0) != -1)
		;
	close(prg->fd.fd[0]);
	close(prg->fd.fd[1]);
	close(prg->fd.fd_in);
	close(prg->fd.fd_out);
	double_dup(stdin_save, stdout_save, &prg->mem);
	return (0);
}

int	exec_command(t_prg *prg)
{
	int			return_value;

	errno = 0;
	return_value = 1;
	prg->paths = get_path(prg->env.export, &prg->mem);
	if (lst_cmd_size(prg->lst_cmd) == 1)
		return_value = exec_one(prg);
	else
		ft_pipex(prg);
	// printf("%d\n", return_value);
	return (return_value);
}
