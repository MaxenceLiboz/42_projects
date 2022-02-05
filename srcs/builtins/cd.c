/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:59:05 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/05 18:27:52 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Get previous doc when using ..
	Not working with cd includes/../libft/srcs
*/
t_string	get_previous_path(char *path, char *str, t_list **mem)
{
	t_string	dst;
	int			i;
	int			to_trim;
	int			to_trim_cpy;

	to_trim = 0;
	to_trim_cpy = 0;
	i = 0;
	if (ft_strncmp(str, "..", 2) == 0)
		to_trim++;
	while (str[i])
	{
		if (ft_strncmp(&str[i], "/../", 4) == 0)
			to_trim++;
		i++;
	}
	if (ft_strncmp(&str[i - 3], "/..", 4) == 0)
		to_trim++;
	to_trim_cpy = to_trim;
	i = ft_strlen(path) - 1;
	while (path[i--])
	{
		if (path[i] == '/')
			to_trim--;
		if (to_trim == 0)
			break ;
	}
	dst = sub_string(path, 0, i, mem);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '/')
			to_trim_cpy--;
		if (to_trim_cpy == 0)
			break ;
	}
	add_string(&dst, "/", dst.size - 1, mem);
	add_string(&dst, &str[i + 1], dst.size - 1, mem);
	printf("%s\n", dst.str);
	return (dst);
}

//  cd ---- wrong error
// cd -- take next arg as path
static int	get_new_path(char **str, t_lst_env *env,
	t_string *path, t_list **mem)
{
	if (!str[1])
	{
		dup_string(path, lst_env_find_name_var(env, "HOME").str, 0, mem);
		if (!*path->str)
			return (print_stderror(0, 1, "cd: HOME not set"));
	}
	else if (!*str[1])
		return (0);
	else if (ft_strncmp(str[1], "-", 2) == 0)
	{
		dup_string(path, lst_env_find_name_var(env, "OLDPWD").str, 0, mem);
		if (!*path->str)
			return (print_stderror(0, 1, "cd: OLDPWD not set"));
		else
			printf("%s\n", path->str);
	}	
	else if (str[1][0] == '~')
	{
		str[1] = sub_string(str[1], 1, ft_strlen(str[1]) - 1, mem).str;
		dup_string(path, getenv("HOME"), 0, mem);
		add_string(path, str[1], path->size - 1, mem);
	}
	else if (str[1][0] == '/')
		dup_string(path, str[1], 0, mem);
	else if (ft_strncmp(str[1], "./", 2) == 0)
		add_string(path, &str[1][2], path->size - 1, mem);
	else if (ft_strncmp(str[1], "..", 2) == 0)
		*path = get_previous_path(path->str, str[1], mem);
	else if (ft_strncmp(str[1], "./", 2) != 0 && str[1][0] != '.')
		add_string(path, str[1], path->size - 1, mem);
	return (1);
}

static void	init_oldpwd(t_head_env *head, t_string *pwd, t_list **mem)
{
	t_lst_env	*env;
	t_lst_env	*export;

	env = head->env;
	export = head->export;
	while (ft_strncmp(env->name_var.str, "OLDPWD", 7) != 0 && env->next)
		env = env->next;
	while (ft_strncmp(export->name_var.str, "OLDPWD", 7) != 0 && export->next)
		export = export->next;
	if (ft_strncmp(export->name_var.str, "OLDPWD", 7) == 0)
	{
		init_string(&export->var, pwd->str, TRUE, mem);
		init_string(&env->var, pwd->str, TRUE, mem);
	}
	else
	{
		lst_env_add_front(&head->env, lst_env_new("OLDPWD",
				sub_string(pwd->str, 0, pwd->size - 1, mem).str, mem));
		lst_env_add_front(&head->export, lst_env_new("OLDPWD",
				sub_string(pwd->str, 0, pwd->size - 1, mem).str, mem));
		lst_env_sort(&head->export);
	}
}

static void	set_new_pwd(t_head_env *head, t_string *pwd, t_list **mem)
{
	t_lst_env	*env;
	t_lst_env	*export;

	env = head->env;
	export = head->export;
	if (lst_env_find_name_var(head->export, "PWD").max_size != 0)
	{
		while (ft_strncmp(env->name_var.str, "PWD", 4) != 0 && env->next)
		env = env->next;
		if (!env->next)
			lst_env_add_front(&head->env, lst_env_new("PWD",
					sub_string(pwd->str, 0, pwd->size - 1, mem).str, mem));
		while (ft_strncmp(export->name_var.str, "PWD", 4) != 0 && export->next)
		export = export->next;
		export->var = sub_string(pwd->str, 0, pwd->size - 1, mem);
		env->var = sub_string(pwd->str, 0, pwd->size - 1, mem);
	}
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
	struct stat	sb;

	init_string(&path, pwd->str, TRUE, mem);
	add_string(&path, "/", path.size - 1, mem);
	if (!get_new_path(str, head->env, &path, mem))
		return (1);
	init_oldpwd(head, pwd, mem);
	stat(path.str, &sb);
	trim_db_slash(&path, mem);
	if (chdir(path.str) != 0)
		return (print_stderror(1, 4, "cd: ", str[1], ": ", strerror(errno)));
	dup_string(pwd, path.str, 0, mem);
	// dprintf(2, "(%s)\n", pwd->str);
	set_new_pwd(head, pwd, mem);
	return (0);
}