/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:38:49 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/21 14:31:33 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Convert our string stored heredoc to an infile
*/
int	here_doc(t_prg *prg, int *fd, int *index)
{
	if (ft_pipe(prg->fd.fd, prg) != SUCCESS)
		return (FAIL);
	if (prg->heredocs.table[*index].size > 65000)
		ft_error_exit(prg, 1, "heredoc bigger than 64K");
	write(prg->fd.fd[1], prg->heredocs.table[*index].str,
		prg->heredocs.table[*index].size - 1);
	if (ft_close(prg->fd.fd[1], prg) != SUCCESS)
		return (FAIL);
	*fd = prg->fd.fd[0];
	return (SUCCESS);
}

/*
	1: Get the right infile and outfile
	2: Remove infile, outfile and heredoc from the command
	3: Dup the STD
*/
int	get_redirections(t_prg *prg, t_lst_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->cmd[i])
	{
		if (ft_strncmp(cmd->cmd[i], "<", 2) == 0)
			if (ft_open(cmd->cmd[i + 1], "ROK", &prg->fd.fd_in, prg) != SUCCESS)
				return (FAIL);
		if (ft_strncmp(cmd->cmd[i], "<<", 3) == 0)
			if (ft_open(prg->heredocs.table[prg->heredocs.index].str,
					"ROK", &prg->fd.fd_in, prg) != SUCCESS)
				return (FAIL);
		if (ft_strncmp(cmd->cmd[i], ">", 2) == 0)
			if (ft_open(cmd->cmd[i + 1], "CRT",
					&prg->fd.fd_out, prg) != SUCCESS)
				return (FAIL);
		if (ft_strncmp(cmd->cmd[i], ">>", 3) == 0)
			if (ft_open(cmd->cmd[i + 1], "CRA",
					&prg->fd.fd_out, prg) != SUCCESS)
				return (FAIL);
		i++;
	}
	cmd->cmd = create_final_command(cmd->cmd, prg);
	return (ft_double_dup(prg->fd.fd_in, prg->fd.fd_out, prg));
}
