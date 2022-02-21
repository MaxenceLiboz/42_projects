/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:59:05 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/21 09:34:20 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Depending on the str[1] value, set the good path
*/
static int	get_new_path(char **str, t_lst_env *env,
	t_string *path, t_prg *prg)
{
	if (!str[1])
		return (set_home_env(path, env, prg));
	else if (ft_strncmp(str[1], "-", 2) == 0)
		return (set_oldpwd(path, env, prg));
	else if (str[1][0] == '~')
		return (set_home_getenv(str[1], path, prg));
	else if (str[1][0] == '/')
	{
		dup_string(path, str[1], 0, prg);
		return (SUCCESS);
	}
	else
		return (set_new_path(str[1], path, prg));
	return (SUCCESS);
}

/*
	trim slash if there is doublons with cd command 
*/
static int	trim_db_slash(t_string *path, t_prg *prg)
{
	int	i;

	i = 0;
	while (path->str[i])
	{
		if (path->str[i + 1] && path->str[i] == '/')
		{
			i++;
			while (path->str[i] && path->str[i] == '/')
				erase_string(path, "/", i, prg);
		}
		i++;
	}
	if (path->size > 2 && path->str[path->size - 2] == '/')
		erase_string(path, "/", path->size - 2, prg);
	return (0);
}

/*
	Repoducing cd command in bash
	No arguments
	Set the PWD and OLDPWD envp variables
*/
int	ft_cd(char **str, t_head_env *head, t_prg *prg, t_string *pwd)
{
	t_string	path;

	init_string(&path, pwd->str, TRUE, prg);
	add_string(&path, "/", path.size - 1, prg);
	if (get_new_path(str, head->env, &path, prg) == FAIL)
		return (FAIL);
	set_oldpwd_env(head, pwd, prg);
	trim_db_slash(&path, prg);
	if (chdir(path.str) != 0)
		return (print_stderror(1, 4, "cd: ", str[1], ": ", strerror(errno)));
	dup_string(pwd, path.str, 0, prg);
	set_new_pwd_env(head, pwd, prg);
	return (0);
}
