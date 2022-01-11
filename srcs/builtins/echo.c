/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:58:59 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/05 14:24:44 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	*echo_join(char **str, char **dst, int i, int n)
{
	while (str[i] && strncmp(str[i], "|", 2) != 0)
	{
		*dst = ft_strjoin(*dst, str[i]);
		if (!dst)
			return (error("malloc: out of memory", 0));
		i++;
		if (str[i] && strncmp(str[i], "|", 2) != 0)
			*dst = ft_strjoin(*dst, " ");
		if (!dst)
			return (error("malloc: out of memory", 0));
	}
	if (n == 0)
		*dst = ft_strjoin(*dst, "\n");
	if (!dst)
		return (error("malloc: out of memory", 0));
	return ((void *)(size_t)1);
}

char	*ft_echo(char **str)
{
	char	*dst;
	int		n;
	int		i;

	n = 0;
	i = 1;
	dst = NULL;
	if (!str[1])
		return (ft_strdup("\n"));
	if (ft_strncmp(str[1], "-n", 3) == 0)
	{
		n = 1;
		i++;
	}
	if (!str[2] && n == 1)
		return (ft_strdup(""));
	if (!echo_join(str, &dst, i, n))
		return (NULL);
	return (dst);
}