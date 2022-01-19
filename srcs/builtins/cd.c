/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:59:05 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/19 15:32:52 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	get_new_path(char **str, t_lst_env *env,
	t_string *path, t_list **mem)
{
	if (!str[1] || !*str[1] || ft_strncmp("~", str[1], 2) == 0)
		dup_string(path, getenv("HOME"), 0, mem);
	else if (str[1][0] == '-')
	{
		dup_string(path, lst_env_find_name_var(env, "OLDPWD").str, 0, mem);
		if (!path->str)
			return (print_stderror(1, 1, "bash: cd: OLDPWD not set\n"));
	}	
	else if (str[1][0] != '/')
	{
		dup_string(path, getcwd(NULL, 0), 0, mem);
		add_string(path, "/", path->size - 1, mem);
		// path->str = ft_strjoin(path->str, "/");
		add_string(path, str[1], path->size - 1, mem);
		// path->str = ft_strjoin(path->str, str[1]);
	}
	else
	{
		if (str[1][0] == '~')
			str[1] = sub_string(str[1], 1, ft_strlen(str[1]) - 1, mem).str;
			// str[1] = ft_substr(str[1], 1, ft_strlen(str[1]) - 1);
		dup_string(path, "/", 0, mem);
		add_string(path, str[1], path->size - 1, mem);
		// path->str = ft_strdup("/");
		// path->str = ft_strjoin(path->str, str[1]);
	}
	return (1);
}

static void	init_oldpwd(t_head_env *head, char *cwd, t_list **mem)
{
	t_lst_env	*env;
	t_lst_env	*export;

	env = head->env;
	export = head->export;
	while (ft_strncmp(env->name_var.str, "OLDPWD", 7) != 0)
		env = env->next;
	while (ft_strncmp(export->name_var.str, "OLDPWD", 7) != 0)
		export = export->next;
	export->var = sub_string(cwd, 0, ft_strlen(cwd), mem);
	env->var = sub_string(cwd, 0, ft_strlen(cwd), mem);
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
			return (print_stderror(1, 3, "bash: cd: ",
					str[1], ": Not a directory\n"));
	}
	else
		return (print_stderror(1, 3, "bash: cd: ",
				str[1], ": No such file or directory\n"));
	return (0);
}
