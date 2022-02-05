/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 08:20:07 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/02/05 09:27:50 by mliboz           ###   ########.fr       */
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
			dup2(prg->fd.fd_in, STDIN_FILENO);
		if (prg->fd.fd_out > 0)
			dup2(prg->fd.fd_out, STDOUT_FILENO);
		init_string(&cmd, "", TRUE, &prg->mem);
		i = -1;
		while (prg->paths[++i])
		{
			cmd = join_string(prg->paths[i], prg->lst_cmd->cmd[0], &prg->mem);
			execve(cmd.str, prg->lst_cmd->cmd, envp);
		}
		cmd = sub_string(prg->lst_cmd->cmd[0], 1, cmd.size, &prg->mem);
		cmd = join_string(getcwd(0, 0), cmd.str, &prg->mem);
		execve(cmd.str, prg->lst_cmd->cmd, envp);
		exit(print_stderror(2, 2, prg->lst_cmd->cmd[0],
				": command not found"));
	}
	return (0);
}

void	double_dup(int fd1, int fd2, t_list **mem)
{
	if (fd1 > 0)
	{
		if (dup2(fd1, STDIN_FILENO) == -1)
			ft_error_free(mem, "error: STDIN_FILENO dup failed");
	}
	if (fd2 > 0)
	{
		if (dup2(fd2, STDOUT_FILENO) == -1)
			ft_error_free(mem, "error: STDOUT_FILENO dup failed");
	}
}

static int	get_size_to_dup(const char *src)
{
	int		i;
	int		quotes;

	i = 0;
	quotes = 0;
	while (src[i])
	{
		if (src[i] == '\'')
		{
			quotes += 2;
			while (src[i] && src[++i] != '\'')
				;
		}
		if (src[i] == '\'')
		{
			quotes += 2;
			while (src[i] && src[++i] != '\'')
				;
		}
		i++;
	}
	return (i - quotes);
}

char	*ft_strdup_and_trim(const char *src, t_list **mem)
{
	int		i;
	int		j;
	char	*dest;

	j = 0;
	dest = ft_malloc(mem, sizeof(char) * (get_size_to_dup(src) + 1));
	i = 0;
	while (src[i])
	{
		if (src[i] == '\'')
		{
			while (src[i] && src[++i] != '\'')
				dest[j++] = src[i];
			j++;
		}
		if (src[i] == '\"')
		{
			while (src[i] && src[++i] != '\"')
				dest[j++] = src[i];
			j++;
		}
		dest[j++] = src[i++];
	}
	dest[j] = '\0';
	return (dest);
}

char	**trim_quotes_unneeded(char **cmd, t_list **mem)
{
	char	**dst;
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	dst = malloc(sizeof(char *) * (i + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (cmd[i])
	{
		dst[i] = ft_strdup_and_trim(cmd[i], mem);
		i++;
	}
	dst[i] = 0;
	return (dst);
}

int	exec_one(t_prg *prg)
{
	char	**envp;

	prg->fd.fd_in = prg->fd.stdin_save;
	prg->fd.fd_out = prg->fd.stdout_save;
	envp = lst_env_to_array(prg->env.env, &prg->mem);
	if (check_cmd(prg, prg->lst_cmd) == FAIL)
		return (FAIL);
	if (!prg->lst_cmd->cmd || !*prg->lst_cmd->cmd)
		return (FAIL);
	prg->lst_cmd->cmd = trim_quotes_unneeded(prg->lst_cmd->cmd, &prg->mem);
	double_dup(prg->fd.fd_in, prg->fd.fd_out, &prg->mem);
	prg->return_value = exec_builtin(prg->lst_cmd->cmd, &prg->env, prg);
	if (prg->return_value != 2)
		return (prg->return_value);
	prg->return_value = ft_execve(prg, envp);
	waitpid(-1, &prg->return_value, 0);
	if (prg->return_value == 256)
		return (1);
	else
		return (127);
	return (prg->return_value);
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
	cmd = sub_string(prg->lst_cmd->cmd[0], 1, cmd.size, &prg->mem);
	cmd = join_string(getcwd(0, 0), cmd.str, &prg->mem);
	execve(cmd.str, prg->lst_cmd->cmd, envp);
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
		dup2(prg->fd.fd[0], STDIN_FILENO);
		close(prg->fd.fd[0]);
	}
	else
	{
		close(prg->fd.fd[0]);
		if (*j != prg->fd.pipe_nb + 1)
			dup2(prg->fd.fd[1], STDOUT_FILENO);
		close(prg->fd.fd[1]);
		if (check_cmd(prg, prg->lst_cmd) == FAIL)
			exit(FAIL);
		if (!prg->lst_cmd->cmd || !*prg->lst_cmd->cmd)
			exit(FAIL);
		prg->lst_cmd->cmd = trim_quotes_unneeded(prg->lst_cmd->cmd, &prg->mem);
		prg->return_value = exec_builtin(prg->lst_cmd->cmd, &prg->env, prg);
		if (prg->return_value != 2)
			exit(prg->return_value);
		ft_exec_process(prg, envp);
	}
}

int	ft_pipex(t_prg *prg)
{
	int		j;
	int		heredoc;
	int		i;
	char	**envp;

	j = 1;
	envp = lst_env_to_array(prg->env.env, &prg->mem);
	prg->fd.pipe_nb = lst_cmd_size(prg->lst_cmd);
	while (++j <= prg->fd.pipe_nb + 1)
	{
		ft_get_fd(prg, &j, envp);
		i = -1;
		heredoc = 0;
		while (prg->lst_cmd->cmd[++i])
		{
			if (check_heredoc(prg->lst_cmd->cmd[i], 0, &i) > -1)
				heredoc = 1;
		}
		if (heredoc > 0)
			prg->heredocs.index += 1;
		prg->lst_cmd = prg->lst_cmd->next;
	}
	while (waitpid(-1, 0, 0) != -1)
		;
	return (0);
}

static void	init_prg(t_prg *prg)
{
	errno = 0;
	prg->return_value = 0;
	prg->fd.stdin_save = dup(STDIN_FILENO);
	if (prg->fd.stdin_save == -1)
		ft_error_free(&prg->mem, "error: STDIN_FILENO save failed");
	prg->fd.stdout_save = dup(STDOUT_FILENO);
	if (prg->fd.stdout_save == -1)
		ft_error_free(&prg->mem, "error: STDOUT_FILENO save failed");
	prg->fd.fd_in = 0;
	prg->fd.fd_out = 0;
	prg->paths = get_path(prg->env.export, &prg->mem);
}

int	exec_command(t_prg *prg)
{
	init_prg(prg);
	if (lst_cmd_size(prg->lst_cmd) == 1)
		prg->return_value = exec_one(prg);
	else
		ft_pipex(prg);
	double_dup(prg->fd.stdin_save, prg->fd.stdout_save, &prg->mem);
	close(prg->fd.stdin_save);
	close(prg->fd.stdout_save);
	return (prg->return_value);
}
