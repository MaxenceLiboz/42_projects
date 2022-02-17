/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:38:49 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/17 10:23:55 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Convert our string stored heredoc to an infile
*/
void	here_doc(t_prg *prg, int *fd, int *index)
{
	ft_pipe(prg->fd.fd, prg);
	if (prg->heredocs.table[*index].size > 65000)
		ft_error_exit(prg, 1, "heredoc bigger than 64K");
	ft_write(prg->fd.fd[1], prg->heredocs.table[*index].str,
		prg->heredocs.table[*index].size - 1, prg);
	ft_close(prg->fd.fd[1], prg);
	*fd = prg->fd.fd[0];
}

/*
	1: Get the right infile and outfile
	2: Remove infile, outfile and heredoc from the command
	3: Dup the STD
*/
void	get_redirections(t_prg *prg, t_lst_cmd *cmd)
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
	cmd->cmd = create_final_command(cmd->cmd, prg);
	ft_double_dup(prg->fd.fd_in, prg->fd.fd_out, prg);
}
