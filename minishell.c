/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:02:00 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/10 12:55:59 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*pwd(char **str)
{
	char	*dst;

	if (!str || strncmp(str[0], "pwd", 4) != 0)
		return (NULL);
	if (str[1] != NULL && *str[1])
		if (str[1] != 0 && strncmp(str[1], "|", 2) != 0)
			return (NULL);
	dst = NULL;
	dst = getcwd(dst, 0);
	if (!dst)
		return (NULL);
	return (dst);
}

int	main(void)
{
	char			*cwd;
	t_string		prompt;
	t_array_string	command;
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
		reinit_array_string(&command);
		cwd = 0;
	}
	return (0);
}
