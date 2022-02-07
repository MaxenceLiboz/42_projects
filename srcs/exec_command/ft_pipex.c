/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 10:33:51 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/07 15:51:58 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_exec_process(t_prg *prg, char **envp)
{
	int			i;
	t_string	cmd;

	i = -1;
	if (!prg->paths)
		exit(print_stderror(2, 2, prg->lst_cmd->cmd[0],
				": No such file or directory"));
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

static void	ft_get_fd(t_prg *prg, int *j, char **envp)
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
		check_cmd(prg, prg->lst_cmd);
		if (!prg->lst_cmd->cmd || !*prg->lst_cmd->cmd)
			exit(FAIL);
		prg->lst_cmd->cmd = trim_quotes_unneeded(prg->lst_cmd->cmd, &prg->mem);
		prg->return_value = exec_builtin(prg->lst_cmd->cmd, &prg->env, prg);
		if (prg->return_value != 2)
			exit(prg->return_value);
		ft_exec_process(prg, envp);
	}
}

/*
	check if the command is a bultin
*/
static t_bool	is_builtin(t_prg *prg)
{
	char	**tmp;

	tmp = f_cmd(prg->lst_cmd->cmd, &prg->mem);
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
	If there is only 1 cmd and it is a built in, exec it outside fork
*/
static int	ft_one_builtin(t_prg *prg)
{
	if (prg->fd.pipe_nb == 1 && is_builtin(prg))
	{
		check_cmd(prg, prg->lst_cmd);
		if (!prg->lst_cmd->cmd || !*prg->lst_cmd->cmd)
			return (prg->return_value);
		prg->lst_cmd->cmd = trim_quotes_unneeded(prg->lst_cmd->cmd, &prg->mem);
		prg->return_value = exec_builtin(prg->lst_cmd->cmd, &prg->env, prg);
		if (prg->return_value != 2)
			return (prg->return_value);
	}
	return (-1);
}

int	ft_pipex(t_prg *prg, char **envp)
{
	int		j;
	int		heredoc;
	int		i;

	j = 1;
	if (ft_one_builtin(prg) != -1)
		return (prg->return_value);
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
	return (0);
}
