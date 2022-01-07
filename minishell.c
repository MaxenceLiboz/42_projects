/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:02:00 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/07 16:24:00 by mliboz           ###   ########.fr       */
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
	// char			*cwd;
	// char			*prompt;
	// char			*pdw;
	// t_array_string	command;

	// pdw = ft_strdup("pwd");
	// while (1)
	// {
	// 	cwd = pwd(&pdw);
	// 	prompt = create_prompt(BLUE, cwd);
	// 	command.command.str = readline(prompt);
	// 	init_string(&command.command, ft_strlen(command.command.str), FALSE);
	// 	freestr(prompt);
	// 	if (create_command(&command))
	// 	{
	// 		for (int i = 0; i < command.size; i++)
	// 			printf("%s\n", command.array[i].str);
	// 		freestr(command.command.str);
	// 	}
	// }
	// freestr(pdw);
	// return (0);
	// int	i = 0;
	// printf("%s\n", ft_copy("\"E\"cho test \"1 22 34       4\"", ' ', &i));
	// printf("%s\n", ft_copy("\"E\"cho test \"1 22 34       4\"", ' ', &i));
	// printf("%s\n", ft_copy("\"E\"cho test \"1 22 34       4\"", ' ', &i));
	t_string	string;
	t_string	cat;

	init_string(&string, 100, TRUE);
	init_string(&cat, 100, TRUE);
	TEST_I(100, string.max_size)
	TEST_I(100, cat.max_size);
	TEST_I(0, string.size);
	TEST_I(0, cat.size);
	add_string_str(&string, "test 1 2 3 4", 0);
	printf("ALED\n");
	TEST_I(12, string.size);
	add_string_str(&cat, "cat 1 2 3 4", 0);
	TEST_I(11, cat.size);
	add_string_str(&string, " ", string.size);
	add_string_str(&string, cat.str, string.size);
	TEST_S("test 1 2 3 4 cat 1 2 3 4", string.str)
	TEST_I(24, string.size);
	freestr(cat.str);
	freestr(string.str);
}
