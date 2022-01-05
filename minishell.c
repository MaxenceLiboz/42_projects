/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:02:00 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/05 09:29:46 by mliboz           ###   ########.fr       */
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
	char	*str;
	char	*cwd;
	char	*prompt;
	char	*pd;

	pd = ft_strdup("pwd");
	while (1)
	{
		cwd = pwd(&pd);
		prompt = create_prompt(BLUE, cwd);
		if (!prompt)
			return (0);
		str = readline(prompt);
		free(str);
		free(prompt);
		free(cwd);
		str = 0;
		prompt = 0;
		cwd = 0;
	}
	free(pd);
	return (0);
}
