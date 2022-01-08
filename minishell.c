/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:02:00 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/08 17:07:47 by maxencelibo      ###   ########.fr       */
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

	cwd = NULL;
	while (1)
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
			{
				printf("%s\n", command.array[i].str);
				reinit_string(&command.array[i]);
			}
			free(command.array);
			reinit_string(&command.command);
		}
		cwd = 0;
	}
	return (0);
	// int	i = 0;
	// printf("%s\n", ft_copy("\"E\"cho test \"1 22 34       4\"", ' ', &i));
	// printf("%s\n", ft_copy("\"E\"cho test \"1 22 34       4\"", ' ', &i));
	// printf("%s\n", ft_copy("\"E\"cho test \"1 22 34       4\"", ' ', &i));
	// t_string		string;
	// t_string		cat;
	// t_array_string	command;

	// init_string(&string, "test 1 2 3 4", TRUE);
	// TEST_I(13, string.size);
	// init_string(&cat, "cat 1 2 3 4", TRUE);
	// TEST_I(12, cat.size);
	// add_string_str(&string, " ", string.size - 1);
	// add_string_str(&string, cat.str, string.size - 1);
	// TEST_S("test 1 2 3 4 cat 1 2 3 4", string.str)
	// replace_string(&string, 13, "dog", 3);
	// TEST_S("test 1 2 3 4 dog 1 2 3 4", string.str)
	// TEST_I(ft_strlen("test 1 2 3 4 dog 1 2 3 4") + 1, string.size);	
	// reinit_string(&cat);
	// reinit_string(&string);
}
