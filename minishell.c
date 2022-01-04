/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:02:00 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/04 14:44:42 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>
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
	int 	i = 0;

	pd = ft_strdup("pwd");
	while (i < 3)
	{
		cwd = pwd(&pd);
		prompt = add_color(BLUE, cwd);
		if (!prompt)
			return (0);
		str = readline(prompt);
		free(str);
		free(prompt);
		free(cwd);
		str = 0;
		prompt = 0;
		cwd = 0;
		i++;
	}
	free(pd);
	return (0);
}
