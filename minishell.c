/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:02:00 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/11 09:15:06 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(void)
{
	char			*cwd;
	t_string		prompt;
	t_command		command;
	int				i = 3;

	cwd = NULL;
	while (i--)
	{
		cwd = getcwd(cwd, 0);
		if (!cwd)
			exit(-1);
		prompt = create_prompt(cwd);
		command.command.str = readline(prompt.str);
		reinit_string(&prompt);
		init_string(&command.command, command.command.str, FALSE);
		if (create_command(&command))
		{
			for (int i = 0; i < command.size; i++)
				printf("%s\n", command.array[i].str);
		}
		reinit_command(&command);
		cwd = 0;
	}
	return (0);
}
