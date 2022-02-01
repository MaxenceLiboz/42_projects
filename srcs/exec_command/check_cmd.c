/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:57:38 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/02/01 14:18:32 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_bool	ft_open(char *file, char *options, int *fd, t_prg *prg)
{
	if (*fd > 0 && *fd != prg->fd.stdin_save && *fd != prg->fd.stdout_save)
		close(*fd);
	if (ft_strncmp(options, "CRA", 4) == 0)
		*fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (ft_strncmp(options, "CRT", 4) == 0)
		*fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (ft_strncmp(options, "ROK", 4) == 0)
	{
		if (access(file, R_OK) == 0)
			*fd = open(file, O_RDONLY);
		else
			return (print_stderror(-1, 4, "open: ",
					file, ": ", strerror(errno)));
	}
	if (*fd == -1)
		return (print_stderror(FAIL, 2, "open: ", strerror(errno)));
	return (SUCCESS);
}

t_bool	check_limiter(char *limiter, char *prompt)
{
	int		i;

	i = 0;
	while (prompt[i] && limiter[i])
	{
		if (prompt[i] != limiter[i])
			return (FAIL);
		i++;
	}
	if (prompt[i] != '\n' || limiter[i] != '\0')
		return (FAIL);
	return (SUCCESS);
}

t_bool	here_doc(char *limiter, t_prg *prg, int *fd)
{
	t_string	prompt;

	if (pipe(prg->fd.fd) == -1)
		return (print_stderror(FAIL, 1, strerror(errno)));
	while (1)
	{
		ft_putstr_fd("here_doc > ", 0);
		init_string(&prompt, get_next_line(0), TRUE, &prg->mem);
		if (check_limiter(limiter, prompt.str) == SUCCESS)
			break ;
		change_arg_command(prg, &prompt);
		if (write(prg->fd.fd[1], prompt.str, prompt.size - 1) == -1)
			return (print_stderror(FAIL, 1, strerror(errno)));
	}
	close(prg->fd.fd[1]);
	*fd = prg->fd.fd[0];
	return (SUCCESS);
}

int	check_cmd(t_prg *prg, t_lst_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->cmd[i])
	{
		if (ft_strncmp(cmd->cmd[i], "<", 2) == 0)
			if (ft_open(cmd->cmd[i + 1], "ROK", &prg->fd.fd_in, prg) == FAIL)
				return (FAIL);
		if (ft_strncmp(cmd->cmd[i], "<<", 3) == 0)
			if (here_doc(cmd->cmd[i + 1], prg, &prg->fd.fd_in) == FAIL)
				return (FAIL);
		if (ft_strncmp(cmd->cmd[i], ">", 2) == 0)
			if (ft_open(cmd->cmd[i + 1], "CRT", &prg->fd.fd_out, prg) == FAIL)
				return (FAIL);
		if (ft_strncmp(cmd->cmd[i], ">>", 3) == 0)
			if (ft_open(cmd->cmd[i + 1], "CRA", &prg->fd.fd_out, prg) == FAIL)
				return (FAIL);
		i++;
	}
	cmd->cmd = f_cmd(cmd->cmd, &prg->mem);
	// dprintf(2, "%d, %d\n", prg->fd.fd_in, prg->fd.fd_out);
	if (prg->fd.fd_in > 0)
		dup2(prg->fd.fd_in, STDIN_FILENO);
	if (prg->fd.fd_out > 0)
		dup2(prg->fd.fd_out, STDOUT_FILENO);
	return (SUCCESS);
}
