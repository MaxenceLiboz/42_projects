/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:02:00 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/13 15:06:22 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// we exit program if we unset PWD, or TERM_SESSION_ID, that is a problem
int	main(int argc, char **argv, char **envp)
{
	t_head_env		env;
	t_string		prompt;
	t_command		command;
	t_lst_cmd		*cmd;

	(void)argc;
	(void)argv;
	set_export(envp, &env);
	while (1)
	{
		prompt = create_prompt();
		command.command.str = readline(prompt.str);
		reinit_string(&prompt);
		init_string(&command.command, command.command.str, FALSE);
		if (*command.command.str)
		{
			cmd = create_command(&command, &env);
			// lst_cmd_put(cmd);
			exec_builtin(cmd->cmd, &env);
			lst_cmd_clear(&cmd);
		}
		reinit_command(&command);
	}
	lst_env_clear(&env.env);
	lst_env_clear(&env.export);
	return (0);
}