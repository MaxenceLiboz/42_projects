/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:57:38 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/01/28 13:36:29 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_open(char *file, char *options)
{
	int		fd;

	fd = -1;
	if (ft_strncmp(options, "CRA", 4) == 0)
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (ft_strncmp(options, "CRT", 4) == 0)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (ft_strncmp(options, "R_OK", 5) == 0)
	{
		if (access(file, R_OK) == 0)
			fd = open(file, O_RDONLY);
		else
			return (print_stderror(-1, 4, "open: ",
					file, ": ", strerror(errno)));
	}
	if (fd == -1)
		return (print_stderror(-1, 2, "open: ", strerror(errno)));
	return (fd);
}

t_bool	check_limiter(char *limiter, char *prompt)
{
	int		i;

	i = 0;
	while (prompt[i] && limiter[i])
	{
		if (prompt[i] != limiter[i])
			return (FALSE);
		i++;
	}
	if (prompt[i] != '\n' || limiter[i] != '\0')
		return (FALSE);
	return (TRUE);
}

int	here_doc(char *limiter, t_prg *prg)
{
	t_string	prompt;

	if (pipe(prg->fd.fd) == -1)
		return (print_stderror(-1, 1, strerror(errno)));
	while (1)
	{
		ft_putstr_fd("here_doc > ", 0);
		init_string(&prompt, get_next_line(0), TRUE, &prg->mem);
		if (check_limiter(limiter, prompt.str) == TRUE)
			break ;
		change_arg_command(prg, &prompt);
		if (write(prg->fd.fd[1], prompt.str, prompt.size - 1) == -1)
			return (print_stderror(-1, 1, strerror(errno)));
	}
	close(prg->fd.fd[1]);
	return (prg->fd.fd[0]);
}

int	check_cmd(t_prg *prg, t_lst_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->cmd[i])
	{
		if (ft_strncmp(cmd->cmd[i], "<", 2) == 0)
			prg->fd.fd_in = ft_open(cmd->cmd[i + 1], "R_OK");
		if (ft_strncmp(cmd->cmd[i], "<<", 3) == 0)
			prg->fd.fd_in = here_doc(cmd->cmd[i + 1], prg);
		if (ft_strncmp(cmd->cmd[i], ">", 2) == 0)
			prg->fd.fd_out = ft_open(cmd->cmd[i + 1], "CRT");
		if (ft_strncmp(cmd->cmd[i], ">>", 3) == 0)
			prg->fd.fd_out = ft_open(cmd->cmd[i + 1], "CRA");
		i++;
	}
	cmd->cmd = f_cmd(cmd->cmd, &prg->mem);
	if (prg->fd.fd_in == -1 || prg->fd.fd_out == -1)
		return (-1);
	if (prg->fd.fd_in > 0)
		dup2(prg->fd.fd_in, STDIN);
	if (prg->fd.fd_out > 0)
		dup2(prg->fd.fd_out, STDOUT);
	return (0);
}
