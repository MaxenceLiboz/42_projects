/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:59:05 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/21 16:16:03 by maxencelibo      ###   ########.fr       */
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
			return (print_stderror(0, 1, "bash: cd: HOME not set\n"));
	}
	else if (!*str[1])
		return (0);
	else if (ft_strncmp(str[1], "-", 2) == 0)
	{
		dup_string(path, lst_env_find_name_var(env, "OLDPWD").str, 0, mem);
		if (!path->str)
			return (print_stderror(0, 1, "bash: cd: OLDPWD not set\n"));
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

int	ft_cd(char **str, t_head_env *head, t_list **mem)
{
	t_string	path;
	struct stat	sb;

	init_string(&path, "", TRUE, mem);
	if (!get_new_path(str, head->env, &path, mem))
		return (1);
	init_oldpwd(head, getcwd(NULL, 0), mem);
	stat(path.str, &sb);
	if (access((const char *)path.str, F_OK) == 0)
	{
		if (S_ISDIR(sb.st_mode))
		{
			if (access((const char *)path.str, X_OK) == 0)
				chdir(path.str);
			else
				return (print_stderror(1, 3, "bash: cd: ",
						str[1], ": Permission denied\n"));
		}
		else
			return (print_stderror(1, 5, "bash: cd: ",
					str[1], ": ", strerror(errno), "\n"));
	}
	else
		return (print_stderror(1, 5, "bash: cd: ",
				str[1], ": ", strerror(errno), "\n"));
	return (0);
}
