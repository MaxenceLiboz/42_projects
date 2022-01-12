/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:02:00 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/12 17:47:15 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// first name_var of export is NULL, that's a problem
int	main(int argc, char **argv, char **envp)
{
	t_head_env		env;
	t_string		prompt;
	t_command		command;
	t_lst_cmd		*cmd;
	// int				i = 3;

	// printf_argv(argc, argv);
	// (void)envp;
	(void)argc;
	(void)argv;
	set_export(envp, &env);
	while (1)
	{
		prompt = create_prompt(lst_env_find_name_var(env.env, "PWD").str);
		command.command.str = readline(prompt.str);
		reinit_string(&prompt);
		init_string(&command.command, command.command.str, FALSE);
		if (*command.command.str)
		{
			cmd = create_command(&command, &env);
			lst_cmd_put(cmd);
			// ft_export(&env, &command);
			lst_cmd_clear(&cmd);
		}
		reinit_command(&command);
	}
	lst_env_clear(&env.env);
	lst_env_clear(&env.export);
	return (0);
}
