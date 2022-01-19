/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:59:05 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/19 14:13:26 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	get_new_path(char **str, t_lst_env *env, char **path)
{
	if (!str[1] || !*str[1] || ft_strncmp("~", str[1], 2) == 0)
		*path = getenv("HOME");
	else if (str[1][0] == '-')
	{
		*path = ft_strdup(lst_env_find_name_var(env, "OLDPWD").str);
		if (!*path)
			return (print_stderror(1, 1, "bash: cd: OLDPWD not set\n"));
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

void	init_oldpwd(t_head_env *head, char *cwd)
{
	t_lst_env	*env;
	t_lst_env	*export;

	env = head->env;
	export = head->export;
	while (ft_strncmp(env->name_var.str, "OLDPWD", 7) != 0)
		env = env->next;
	while (ft_strncmp(export->name_var.str, "OLDPWD", 7) != 0)
		export = export->next;
	sub_string(&export->var, cwd, 0, ft_strlen(cwd));
	sub_string(&env->var, cwd, 0, ft_strlen(cwd));
}

int	ft_cd(char **str, t_head_env *head)
{
	char		*path;
	struct stat	sb;

	path = NULL;
	if (!get_new_path(str, head->env, &path))
		return (1);
	init_oldpwd(head, getcwd(NULL, 0));
	stat(path, &sb);
	if (access((const char *)path, F_OK) == 0)
	{
		if (S_ISDIR(sb.st_mode))
		{
			if (access((const char *)path, X_OK) == 0)
				chdir(path);
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
