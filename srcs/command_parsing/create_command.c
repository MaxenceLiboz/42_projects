/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 10:47:50 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/17 10:20:15 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	While the command is not ended (pipe at the end)
	Parse it and check everything
*/
static t_bool	parse_command(t_prg *prg)
{
	t_bool	status;
	int		save;
	char	*line;

	save = 0;
	status = FAIL;
	while (status == FAIL)
	{
		if (check_quotes(prg->cmd.command) == FAIL
			|| syntax_special_char(&prg->cmd.command, prg) == FAIL
			|| count_split_wog(prg->cmd.command.str, ' ') == 0)
			return (FAIL);
		init_table_heredoc(prg, &save);
		change_arg_command(prg, &prg->cmd.command);
		split_wog(prg, ' ');
		status = check_pipes(prg->cmd);
		if (status == SUCCESS)
			break ;
		if (status == -1)
			return (FAIL);
		line = readline("pipe > ");
		add_string(&prg->cmd.command, line,
			prg->cmd.command.size, prg);
		free(line);
	}
	return (SUCCESS);
}

/*
	Parse the recieved command in our structures
*/
t_lst_cmd	*create_command(t_prg *prg)
{
	t_lst_cmd	*lst;

	lst = 0;
	init_heredoc(&prg->heredocs);
	if (parse_command(prg) == FAIL)
		return (NULL);
	prg->heredocs.index = 0;
	lst = lst_cmd_init(&prg->cmd, prg);
	return (lst);
}
