/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:22:24 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/31 13:59:39 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//In this function, need to set var.type to ENV if the name_var contain '='
//As well, the substr function isn't working if the = is not found

static int	export_value_shell(char *envp, t_lst_env *new_export,
			t_lst_env *new_env, t_list **mem)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (envp[i] != '=' && envp[i])
		i++;
	if (!ft_strncmp(new_export->name_var.str, "SHELL", 6))
	{
		path = getcwd(0, 0);
		new_export->var = sub_string(path, 0, ft_strlen(path) + 1,
				mem);
		new_env->var = sub_string(path, 0, ft_strlen(path) + 1, mem);
		free(path);
		return (1);
	}
	return (0);
}

static int	export_value_shlvl(char *envp, t_lst_env *new_export,
			t_lst_env *new_env, t_list **mem)
{
	int		i;
	int		shlvl;
	char	char_shlvl;
	char	*path;

	i = 0;
	shlvl = 1;
	while (envp[i] != '=' && envp[i])
		i++;
	if (!ft_strncmp(new_export->name_var.str, "SHLVL", 6))
	{
		shlvl = shlvl + ft_atoi(envp + i + 1);
		char_shlvl = shlvl + '0';
		path = strdup(&char_shlvl);
		if (!path)
		{
			ft_error_free(mem, "Malloc error\n");
			return (0);
		}
		new_export->var = sub_string(path, 0, ft_strlen(path) + 1, mem);
		new_env->var = sub_string(path, 0, ft_strlen(path) + 1, mem);
		free(path);
		return (1);
	}
	return (0);
}

static int	head_env_init(char *envp, t_lst_env *new_export,
			t_lst_env *new_env, t_list **mem)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (envp[i] != '=' && envp[i])
		i++;
	new_export->name_var = sub_string(envp, 0, i, mem);
	new_env->name_var = sub_string(envp, 0, i, mem);
	if (ft_strncmp(new_export->name_var.str, "OLDPWD", 7)
		&& !export_value_shell(envp, new_export, new_env, mem)
		&& !export_value_shlvl(envp, new_export, new_env, mem))
	{
		new_export->var = sub_string(envp, i + 1, (ft_strlen(envp) - i) + 1,
				mem);
		new_env->var = sub_string(envp, i + 1, (ft_strlen(envp) - i) + 1, mem);
	}
	return (1);
}

//Should we do use add_back or add_front
int	set_export(char **envp, t_head_env *head, t_list **mem)
{
	t_lst_env	*new_export;
	t_lst_env	*new_env;
	int			i;

	i = 0;
	head->env = NULL;
	head->export = NULL;
	while (envp[i])
	{
		new_export = lst_env_new(NULL, NULL, mem);
		new_env = lst_env_new(NULL, NULL, mem);
		lst_env_add_back(&head->export, new_export);
		lst_env_add_back(&head->env, new_env);
		if (!head_env_init(envp[i], new_export, new_env, mem))
			return (0);
		i++;
	}
	lst_env_sort(&head->export);
	return (1);
}
