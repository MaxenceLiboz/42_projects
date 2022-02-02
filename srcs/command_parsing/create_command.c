/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 10:47:50 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/02 10:57:43 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	1: Check if heredoc
*/

t_lst_cmd	*create_command(t_prg *prg)
{
	t_lst_cmd	*lst;
	t_bool		status;

	lst = 0;
	prg->cmd.command.size = 0;
	status = FAIL;
	while (status == FAIL)
	{
		if (check_quotes(prg->cmd.command) == FAIL
			|| check_chevrons(&prg->cmd.command, &prg->mem) == FAIL
			|| count_split_wog(prg->cmd.command.str, ' ') == 0)
			return (NULL);
		init_table_heredoc(prg);
		change_arg_command(prg, &prg->cmd.command);
		split_wog(prg, ' ');
		status = check_pipes(prg->cmd);
		if (status == SUCCESS)
			break ;
		if (status == -1)
			return (NULL);
		add_string(&prg->cmd.command, readline("> "),
			prg->cmd.command.size, &prg->mem);
	}
	// printf("%s\n", prg->cmd.command.str);
	lst = lst_cmd_init(&prg->cmd, &prg->mem);
	return (lst);
}
