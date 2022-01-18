/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:59:05 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/18 14:55:31 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	get_new_path(char **str, t_lst_env *env, char **path)
{
	if (!str[1] || !*str[1] || ft_strncmp("~", str[1], 2) == 0)
		*path = getenv("HOME");
	else if (str[1][0] == '-')
	{
		*path = lst_env_find_name_var(env, "OLDPWD").str;
		if (!*path)
			return (print_stderror(1, "bash: cd: OLDPWD not set\n"));
	}	
	else if (str[1][0] != '/')
	{
		*path = getcwd(*path, 0);
		*path = ft_strjoin(*path, "/");
		*path = ft_strjoin(*path, str[1]);
	}
	else
	{
		if (str[1][0] == '~')
			str[1] = ft_substr(str[1], 1, ft_strlen(str[1]) - 1);
		*path = ft_strdup("/");
		*path = ft_strjoin(*path, str[1]);
	}
	return (1);
}

int	ft_cd(char **str, t_lst_env *env)
{
	char		*path;

	path = NULL;
	if (!get_new_path(str, env, &path))
		return (1);
	if (access((const char *)path, F_OK) == 0)
	{
		if (access((const char *)path, X_OK) == 0)
			chdir(path);
		else
			return (print_stderror(3, "bash: cd: ",
					str[1], ": Permission denied\n"));
	}
	else
		return (print_stderror(3, "bash: cd: ",
				str[1], ": No such file or directory\n"));
	return (0);
}
