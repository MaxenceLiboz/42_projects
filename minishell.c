/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:02:00 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/18 14:51:05 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// we exit program if we unset PWD, or TERM_SESSION_ID, that is a problem
// Need to reset OLDPWD at each command
//At start, we need to set OLDPWD to 0;
int	main(int argc, char **argv, char **envp)
{
	t_prg	prg;

	(void)argc;
	(void)argv;
	set_export(envp, &prg.env);
	while (1)
	{
		prg.prompt = create_prompt();
		prg.cmd.command.str = readline(prg.prompt.str);
		reinit_string(&prg.prompt);
		init_string(&prg.cmd.command, prg.cmd.command.str, FALSE);
		if (*prg.cmd.command.str)
		{
			prg.lst_cmd = create_command(&prg.cmd, &prg.env);
			// lst_cmd_put(cmd);
			exec_builtin(prg.lst_cmd->cmd, &prg.env);
			lst_cmd_clear(&prg.lst_cmd);
		}
		reinit_command(&prg.cmd);
	}
	lst_env_clear(&prg.env.env);
	lst_env_clear(&prg.env.export);
	return (0);
}
