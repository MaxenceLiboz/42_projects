/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:59:05 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/08 11:44:46 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// static char	*get_new_path(char **str)
// {
// 	char	*dst;
// 	int		i;

// 	i = 0;
// 	dst = NULL;
// 	if (!str[1])
// 		dst = getenv("HOME");
// 	if (ft_strncmp(str[1], "../", 3) == 0)
// 	{
// 		while ()
// 		dst = ft_strjoin(dst, str[1])
// 	}
// 	return (dst);
// }

int	ft_cd(char **str)
{
	char		*path;
	char		*cpy;

	path = NULL;
	cpy = ft_strdup(str[1]);
	if (!str[1] || !*str[1] || (str[1][0] == '~' && ft_strlen(str[1]) < 2))
	{
		path = getenv("HOME");
	}
	else if (str[1][0] != '/' && str[1][0] != '~')
		path = ft_strjoin(ft_strjoin(getcwd(path, 0), "/"), str[1]);
	else
	{
		if (str[1][0] == '~')
			str[1] = ft_substr(str[1], 1, ft_strlen(str[1]) - 1);
		path = ft_strdup(getenv("HOME"));
		path = ft_strjoin(path, str[1]);
		// printf("%s\n", path);
	}
	if (access((const char *)path, F_OK) == 0)
	{
		if (access((const char *)path, X_OK) == 0)
			chdir(path);
		else
		{
			ft_putstr_fd("bash: cd: ", 2);
			ft_putstr_fd(cpy, 2);
			return ((int)error(": Permission denied", 0));
		}
	}
	else
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(cpy, 2);
		return ((int)error(": No such file or directory", 0));
	}
	path = NULL;
	path = getcwd(path, 0);
	printf("%s\n", path);
	return (0);
}
