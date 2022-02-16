/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:19:45 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/16 10:30:53 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Set the path to HOME with our lst and return
*/
t_bool	set_home_env(t_string *path, t_lst_env *env, t_list **mem)
{
	dup_string(path, lst_env_find_name_var(env, "HOME").str, 0, mem);
	if (!*path->str)
		return (print_stderror(FAIL, 1, "cd: HOME not set"));
	return (SUCCESS);
}

/*
	When cd -:
		Set the path to OLDPWD and return
*/
t_bool	set_oldpwd(t_string *path, t_lst_env *env, t_list **mem)
{
	dup_string(path, lst_env_find_name_var(env, "OLDPWD").str, 0, mem);
	if (!*path->str)
		return (print_stderror(FAIL, 1, "cd: OLDPWD not set"));
	return (SUCCESS);
}

/*
	When cd ~:
		Set the path to HOME with getenv
*/
t_bool	set_home_getenv(char *str, t_string *path, t_list **mem)
{
	str = sub_string(str, 1, ft_strlen(str) - 1, mem).str;
	dup_string(path, getenv("HOME"), 0, mem);
	add_string(path, str, path->size - 1, mem);
	return (SUCCESS);
}
