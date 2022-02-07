/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:59:05 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/07 12:46:10 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Depending on the str[1] value, set the good path
*/
static int	get_new_path(char **str, t_lst_env *env,
	t_string *path, t_list **mem)
{
	if (!str[1])
		return (set_home_env(path, env, mem));
	else if (ft_strncmp(str[1], "-", 2) == 0)
		return (set_oldpwd(path, env, mem));
	else if (str[1][0] == '~')
		return (set_home_getenv(str[1], path, mem));
	else if (str[1][0] == '/')
	{
		dup_string(path, str[1], 0, mem);
		return (SUCCESS);
	}
	else
		return (set_new_path(str[1], path, mem));
	return (SUCCESS);
}

/*
	trim slash if there is doublons with cd command 
*/
static int	trim_db_slash(t_string *path, t_list **mem)
{
	int	i;

	i = 0;
	while (path->str[i])
	{
		if (path->str[i] == '/')
		{
			i++;
			while (path->str[i] && path->str[i] == '/')
				erase_string(path, "/", i, mem);
		}
		i++;
	}
	if (path->size > 2 && path->str[path->size - 2] == '/')
		erase_string(path, "/", path->size - 2, mem);
	return (0);
}

int	ft_cd(char **str, t_head_env *head, t_list **mem, t_string *pwd)
{
	t_string	path;
	// struct stat	sb;

	init_string(&path, pwd->str, TRUE, mem);
	add_string(&path, "/", path.size - 1, mem);
	if (get_new_path(str, head->env, &path, mem) == FAIL)
		return (FAIL);
	set_oldpwd_env(head, pwd, mem);
	// stat(path.str, &sb);
	trim_db_slash(&path, mem);
	if (chdir(path.str) != 0)
		return (print_stderror(1, 4, "cd: ", str[1], ": ", strerror(errno)));
	dup_string(pwd, path.str, 0, mem);
	set_new_pwd_env(head, pwd, mem);
	return (0);
}
