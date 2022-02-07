/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:57:38 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/02/07 14:18:07 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	here_doc(t_prg *prg, int *fd, int *index)
{
	int		pid;

	(void)fd;
	ft_pipe(prg->fd.fd, &prg->mem);
	pid = fork();
	if (pid < 0)
		ft_error_exit(&prg->mem, 2, "fork: ", strerror(errno));
	if (pid == 0)
	{
		dup2(prg->fd.fd[0], prg->fd.fd_in);
		ft_close(prg->fd.fd[0], &prg->mem);
		// if (prg->heredocs.table[*index].size > 65000)
		// 	ft_error_exit(&prg->mem, 1, "heredoc bigger than 64K");
		ft_write(prg->fd.fd[1], prg->heredocs.table[*index].str,
			prg->heredocs.table[*index].size - 1, &prg->mem);
		ft_close(prg->fd.fd[1], &prg->mem);
	}
	else
	{
		close(prg->fd.fd[1]);
		*fd = prg->fd.fd[0];
		close(prg->fd.fd[1]);
	}
}

/*
	1: Get the right infile and outfile
	2: Remove infile, outfile and heredoc from the command
	3: Dup the STD
*/
void	check_cmd(t_prg *prg, t_lst_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->cmd[i])
	{
		if (ft_strncmp(cmd->cmd[i], "<", 2) == 0)
			ft_open(cmd->cmd[i + 1], "ROK", &prg->fd.fd_in, prg);
		if (ft_strncmp(cmd->cmd[i], "<<", 3) == 0)
			here_doc(prg, &prg->fd.fd_in, &prg->heredocs.index);
		if (ft_strncmp(cmd->cmd[i], ">", 2) == 0)
			ft_open(cmd->cmd[i + 1], "CRT", &prg->fd.fd_out, prg);
		if (ft_strncmp(cmd->cmd[i], ">>", 3) == 0)
			ft_open(cmd->cmd[i + 1], "CRA", &prg->fd.fd_out, prg);
		i++;
	}
	cmd->cmd = f_cmd(cmd->cmd, &prg->mem);
	ft_double_dup(prg->fd.fd_in, prg->fd.fd_out, &prg->mem);
}
