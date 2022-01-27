/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 10:47:50 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/27 14:01:42 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_lst_cmd	*create_command(t_prg *prg)
{
	t_lst_cmd	*lst;

	lst = 0;
	prg->cmd.command.size = 0;
	if (!check_quotes(prg->cmd.command)
		|| !check_chevrons(&prg->cmd.command, &prg->mem)
		|| count_split_wog(prg->cmd.command.str, ' ') == 0)
		return (0);
	change_arg_command(prg, &prg->cmd.command);
	split_wog(prg, ' ');
	if (!check_pipes(prg->cmd))
		return (0);
	lst = lst_cmd_init(&prg->cmd, &prg->mem);
	return (lst);
}
