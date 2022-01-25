/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:02:00 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/25 16:36:38 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// we exit program if we unset PWD, or TERM_SESSION_ID, that is a problem
// Need to reset OLDPWD at each command
//At start, we need to set OLDPWD to 0;
int	main(int argc, char **argv, char **envp)
{
	t_prg	prg;
	int		i = 10;

	(void)argc;
	(void)argv;
	prg.mem = 0;
	set_export(envp, &prg.env, &prg.mem);
	while (i--)
	{
		prg.prompt = create_prompt(&prg.mem);
		prg.cmd.command.str = readline(prg.prompt.str);
		if (*prg.cmd.command.str)
			add_history(prg.cmd.command.str);
		init_string(&prg.cmd.command, prg.cmd.command.str, FALSE, &prg.mem);
		ft_lstadd_front(&prg.mem, ft_lstnew(prg.cmd.command.str));
		if (*prg.cmd.command.str)
		{
			prg.lst_cmd = create_command(&prg);
			if (prg.lst_cmd && *prg.lst_cmd->cmd[0] != 0)
			{
				// lst_cmd_put(cmd);
				exec_command(&prg, envp);
				// exec_builtin(prg.lst_cmd->cmd, &prg.env, &prg.mem);
			}
		}
		reinit_command(&prg.cmd);
	}
	return (ft_lstclear(&prg.mem, free));
}
