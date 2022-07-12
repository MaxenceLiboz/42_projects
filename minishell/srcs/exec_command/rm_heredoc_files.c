/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_heredoc_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 08:56:12 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/22 09:41:24 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**create_rm_cmd(t_prg *prg)
{
	char		**cmd;
	t_string	*command;
	int			i;

	i = 0;
	command = ft_malloc(prg, sizeof(t_string) * (prg->heredocs.size + 3));
	init_string(&command[0], "/bin/rm", TRUE, prg);
	init_string(&command[1], "-rf", TRUE, prg);
	while (i < prg->heredocs.size)
	{
		init_string(&command[i + 2], prg->heredocs.table[i].str, TRUE, prg);
		i++;
	}
	command[i + 2].str = NULL;
	cmd = strings_to_array(command, prg);
	return (cmd);
}

/*
	rm all files created by heredocs
*/
void	rm_heredocs_files(t_prg *prg, char **envp)
{
	char	**cmd;
	int		eacces;

	cmd = create_rm_cmd(prg);
	prg->fd.pid = fork();
	if (prg->fd.pid == -1)
		return ;
	else if (prg->fd.pid == 0)
	{
		ft_execve(cmd[0], cmd, envp, &eacces);
		exit(0);
	}
	else
		waitpid(-1, NULL, 0);
}
