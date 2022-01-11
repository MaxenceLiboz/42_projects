/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:02:00 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/11 13:23:53 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	t_head_env		env;
	t_string		prompt;
	t_command		command;
	int				i = 3;

	(void)argc;
	(void)argv;
	set_export(envp, &env);
	while (i--)
	{
		prompt = create_prompt(lst_env_find_name_var(env.env, "PWD").str);
		command.command.str = readline(prompt.str);
		reinit_string(&prompt);
		init_string(&command.command, command.command.str, FALSE);
		if (create_command(&command, &env))
		{
			for (int i = 0; i < command.size; i++)
				printf("%s\n", command.array[i].str);
		}
		reinit_command(&command);
	}
	lst_env_clear(&env.env);
	lst_env_clear(&env.export);
	return (0);
}
