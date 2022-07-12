/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:22:24 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/17 12:31:02 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	export_value_shlvl(char *envp, t_lst_env *new_export,
			t_lst_env *new_env, t_prg *prg)
{
	int		i;
	int		shlvl;
	char	*shlvl_v;

	i = 0;
	shlvl = 1;
	while (envp[i] != '=' && envp[i])
		i++;
	if (ft_strncmp(new_export->name_var.str, "SHLVL", 6) == 0)
	{
		new_export->var = sub_string(envp, i + 1, (ft_strlen(envp) - i) + 1,
				prg);
		shlvl_v = set_value_shlvl(shlvl, new_export->var);
		new_export->var = sub_string(shlvl_v, 0, ft_strlen(shlvl_v) + 1, prg);
		new_env->var = sub_string(shlvl_v, 0, ft_strlen(shlvl_v) + 1, prg);
		free(shlvl_v);
		return (1);
	}
	return (0);
}

/*
	Set out minishell path in the PATH variable
*/
static int	export_value_path(char *envp, t_lst_env *new_export,
			t_lst_env *new_env, t_prg *prg)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (envp[i] != '=' && envp[i])
		i++;
	if (!ft_strncmp(new_export->name_var.str, "PATH", 6))
	{
		path = getcwd(0, 0);
		if (path == NULL)
			ft_error_exit(prg, 1, "getcwd: error initializing path value");
		new_export->var = sub_string(envp, i + 1, (ft_strlen(envp) - i) + 1,
				prg);
		new_export->var = join_string(":", new_export->var.str, prg);
		new_export->var = join_string(path, new_export->var.str, prg);
		new_env->var = sub_string(envp, i + 1, (ft_strlen(envp) - i) + 1,
				prg);
		new_env->var = join_string(":", new_env->var.str, prg);
		new_env->var = join_string(path, new_env->var.str, prg);
		free(path);
		return (1);
	}
	return (0);
}

static int	head_env_init(char *envp, t_lst_env *new_export,
			t_lst_env *new_env, t_prg *prg)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (envp[i] != '=' && envp[i])
		i++;
	new_export->name_var = sub_string(envp, 0, i, prg);
	new_env->name_var = sub_string(envp, 0, i, prg);
	if (ft_strncmp(new_export->name_var.str, "OLDPWD", 7)
		&& !export_value_shlvl(envp, new_export, new_env, prg)
		&& !export_value_path(envp, new_export, new_env, prg))
	{
		new_export->var = sub_string(envp, i + 1, (ft_strlen(envp) - i) + 1,
				prg);
		new_env->var = sub_string(envp, i + 1, (ft_strlen(envp) - i) + 1, prg);
	}
	if (ft_strncmp(new_export->name_var.str, "OLDPWD", 7) == 0)
	{
		new_export->var.str = NULL;
		new_env->var.str = NULL;
	}
	return (1);
}

/*
	if SHLVL var is not set at start, we will create it and set it to 1;
*/
static void	create_shlvl(t_head_env *head, t_prg *prg)
{
	t_lst_env	*new_export;
	t_lst_env	*new_env;

	new_export = lst_env_new(NULL, NULL, prg);
	new_env = lst_env_new(NULL, NULL, prg);
	lst_env_add_back(&head->export, new_export);
	lst_env_add_back(&head->env, new_env);
	new_export->name_var = sub_string("SHLVL", 0, 6, prg);
	new_env->name_var = sub_string("SHLVL", 0, 6, prg);
	export_value_shlvl("SHLVL", new_export, new_env, prg);
	return ;
}

/*
	Set envp into our env lists
*/
int	set_export(char **envp, t_head_env *head, t_prg *prg)
{
	t_lst_env	*new_export;
	t_lst_env	*new_env;
	int			i;

	i = 0;
	head->env = NULL;
	head->export = NULL;
	while (envp[i])
	{
		new_export = lst_env_new(NULL, NULL, prg);
		new_env = lst_env_new(NULL, NULL, prg);
		lst_env_add_back(&head->export, new_export);
		lst_env_add_back(&head->env, new_env);
		head_env_init(envp[i], new_export, new_env, prg);
		i++;
	}
	if (!lst_env_find_name_var(head->env, "SHLVL").str)
		create_shlvl(head, prg);
	lst_env_sort(&head->export);
	return (1);
}
