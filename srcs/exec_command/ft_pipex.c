/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 10:33:51 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/16 12:16:57 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_exec_process(t_prg *prg, char **envp)
{
	struct stat	file;
	int			eacces;

	eacces = FALSE;
	stat(prg->lst_cmd->cmd[0], &file);
	if (S_ISDIR(file.st_mode) == TRUE)
		exit(print_stderror(126, 2, prg->lst_cmd->cmd[0],
				": is a dir"));
	ft_execve(prg->lst_cmd->cmd[0], prg->lst_cmd->cmd, envp, &eacces);
	if (!prg->paths || is_path(prg->lst_cmd->cmd[0]) == TRUE)
		exit(print_stderror(127, 2, prg->lst_cmd->cmd[0],
				": No such file or directory"));
	ft_exec_path(prg, envp, &eacces);
	if (eacces == TRUE)
		exit(print_stderror(126, 3,
				prg->lst_cmd->cmd[0], ": ", strerror(errno)));
	exit(print_stderror(127, 2, prg->lst_cmd->cmd[0],
			": command not found"));
}

static void	ft_get_fd(t_prg *prg, int *j, char **envp)
{
	pipe(prg->fd.fd);
	prg->fd.pid = fork();
	if (prg->fd.pid == -1)
		exit(print_stderror(-1, 2, "fork: ", strerror(errno)));
	if (prg->fd.pid != 0)
	{
		close(prg->fd.fd[1]);
		close(prg->fd.fd[0]);
	}
	else
	{
		close(prg->fd.fd[0]);
		if (*j != prg->fd.pipe_nb + 1)
			dup2(prg->fd.fd[1], STDOUT_FILENO);
		close(prg->fd.fd[1]);
		check_cmd(prg, prg->lst_cmd);
		if (!prg->lst_cmd->cmd || !*prg->lst_cmd->cmd)
			exit(FAIL);
		prg->lst_cmd->cmd = trim_quotes_unneeded(prg->lst_cmd->cmd, &prg->mem);
		if (exec_builtin(prg->lst_cmd->cmd, &prg->env, prg) != 2)
			exit(g_returnvalue);
		ft_exec_process(prg, envp);
	}
}

/*
	If there is only 1 cmd and it is a built in, exec it outside fork
*/
static int	ft_one_builtin(t_prg *prg)
{
	if (prg->fd.pipe_nb == 1 && is_builtin(prg))
	{
		check_cmd(prg, prg->lst_cmd);
		if (!prg->lst_cmd->cmd || !*prg->lst_cmd->cmd)
			return (g_returnvalue);
		prg->lst_cmd->cmd = trim_quotes_unneeded(prg->lst_cmd->cmd, &prg->mem);
		if (exec_builtin(prg->lst_cmd->cmd, &prg->env, prg) != 2)
			return (2);
	}
	return (-1);
}

int	check_heredoc_pipex(char *str, int i)
{
	int		pipe;

	pipe = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			while (str[i] && str[++i] != '\"')
				;
		if (str[i] == '\'')
			while (str[i] && str[++i] != '\'')
				;
		if (ft_strncmp(&str[i], "<<", 2) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_pipex(t_prg *prg, char **envp)
{
	int		j;
	int		heredoc;
	int		i;

	j = 1;
	set_signals(prg->lst_cmd->cmd[0]);
	if (ft_one_builtin(prg) != -1)
		return ;
	while (++j <= prg->fd.pipe_nb + 1)
	{
		ft_get_fd(prg, &j, envp);
		i = -1;
		heredoc = 0;
		while (prg->lst_cmd->cmd[++i])
		{
			if (check_heredoc_pipex(prg->lst_cmd->cmd[i], 0) > -1)
				heredoc = 1;
		}
		if (heredoc > 0)
			prg->heredocs.index += 1;
		prg->lst_cmd = prg->lst_cmd->next;
	}
	close(prg->fd.fd[0]);
	close(prg->fd.fd[1]);
	return ;
}
