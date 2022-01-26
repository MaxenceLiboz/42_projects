/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:59:05 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/26 11:51:59 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//  cd ---- wrong error
// cd -- take next arg as path
static int	get_new_path(char **str, t_lst_env *env,
	t_string *path, t_list **mem)
{
	if (!str[1])
	{
		dup_string(path, lst_env_find_name_var(env, "HOME").str, 0, mem);
		if (!path->str)
			return (print_stderror(0, 1, "cd: HOME not set"));
	}
	else if (!*str[1])
		return (0);
	else if (ft_strncmp(str[1], "-", 2) == 0)
	{
		dup_string(path, lst_env_find_name_var(env, "OLDPWD").str, 0, mem);
		if (!path->str)
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
	else
		dup_string(path, str[1], 0, mem);
	return (1);
}

static void	init_oldpwd(t_head_env *head, char *cwd, t_list **mem)
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
		export->var = sub_string(cwd, 0, ft_strlen(cwd), mem);
		env->var = sub_string(cwd, 0, ft_strlen(cwd), mem);
	}
	else
	{
		lst_env_add_front(&head->env, lst_env_new("OLDPWD",
				sub_string(cwd, 0, ft_strlen(cwd), mem).str, mem));
		lst_env_add_front(&head->export, lst_env_new("OLDPWD",
				sub_string(cwd, 0, ft_strlen(cwd), mem).str, mem));
		lst_env_sort(&head->export);
	}
	free(cwd);
}

static void	set_new_pwd(t_head_env *head, t_list **mem)
{
	char		*new_cwd;
	t_lst_env	*env;
	t_lst_env	*export;

	env = head->env;
	export = head->export;
	if (lst_env_find_name_var(head->export, "PWD").max_size != 0)
	{
		new_cwd = getcwd(NULL, 0);
		while (ft_strncmp(env->name_var.str, "PWD", 4) != 0 && env->next)
		env = env->next;
		if (!env->next)
			lst_env_add_front(&head->env, lst_env_new("PWD",
					sub_string(new_cwd, 0, ft_strlen(new_cwd), mem).str, mem));
		while (ft_strncmp(export->name_var.str, "PWD", 4) != 0 && export->next)
		export = export->next;
		export->var = sub_string(new_cwd, 0, ft_strlen(new_cwd), mem);
		env->var = sub_string(new_cwd, 0, ft_strlen(new_cwd), mem);
		free(new_cwd);
	}
}

int	ft_cd(char **str, t_head_env *head, t_list **mem)
{
	t_string	path;
	struct stat	sb;

	init_string(&path, "", TRUE, mem);
	if (!get_new_path(str, head->env, &path, mem))
		return (1);
	init_oldpwd(head, getcwd(NULL, 0), mem);
	stat(path.str, &sb);
	if (chdir(path.str) != 0)
		return (print_stderror(1, 4, "cd: ", str[1], ": ", strerror(errno)));
	set_new_pwd(head, mem);
	return (0);
}
