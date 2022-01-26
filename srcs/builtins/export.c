/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:40:44 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/25 08:44:33 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_strchr_len(const char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

int	control_args(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (ft_isalnum(str[i]) == 0 || (str[i] >= '0' && str[i] <= '9'))
		return (1);
	i++;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

//change sorting to avoid to iterate on all the lst again
static void	add_elem_to_lst(char *arg, t_head_env *head, t_list **mem)
{
	t_lst_env	*new_export;
	t_lst_env	*new_env;
	int			c;

	new_export = lst_env_new("", NULL, mem);
	c = ft_strchr_len(arg, '=');
	new_env = NULL;
	new_export->name_var = sub_string(arg, 0, c, mem);
	if (ft_strchr(arg, '=') != 0)
	{
		new_env = lst_env_new("", NULL, mem);
		new_env->name_var = sub_string(arg, 0, c, mem);
		new_env->var = sub_string(arg, c + 1, ft_strlen(arg) - c, mem);
		new_export->var = sub_string(arg, c + 1, ft_strlen(arg) - c, mem);
		lst_env_add_front(&head->env, new_env);
	}
	lst_env_add_front(&head->export, new_export);
	lst_env_sort(&head->export);
	return ;
}

static void	replace_elem_of_lst(t_head_env *head, char *var, char *var_name,
		t_list **mem)
{
	t_lst_env	*export;
	t_lst_env	*env;
	int			c;

	export = head->export;
	env = head->env;
	c = ft_strchr_len(var, '=');
	while (export && ft_strncmp(var_name, export->name_var.str,
			ft_strlen(var_name) + 1) != 0)
		export = export->next;
	while (env && ft_strncmp(var_name, env->name_var.str,
			ft_strlen(var_name) + 1) != 0)
		env = env->next;
	if (!env)
	{
		env = lst_env_new("", NULL, mem);
		env->name_var = sub_string(export->name_var.str, 0,
				export->name_var.size, mem);
		env->var = sub_string(var, c + 1, ft_strlen(var) - c, mem);
		lst_env_add_front(&head->env, env);
	}
	env->var = sub_string(var, c + 1, ft_strlen(var) - c, mem);
	export->var = sub_string(var, c + 1, ft_strlen(var) - c, mem);
}

int	ft_export(t_head_env *head, char **command, t_list **mem)
{
	char	*var_name;
	int		i;

	i = 0;
	if (!command[i + 1])
		return (print_export(head));
	while (command[++i])
	{
		var_name = sub_string(command[i], 0, ft_strchr_len(command[i], '='),
				mem).str;
		if (control_args(var_name) == 0)
		{
			if (lst_env_find_name_var(head->export, var_name).str == 0)
				add_elem_to_lst(command[i], head, mem);
			else
				if (ft_strchr(command[i], '=') != 0)
					replace_elem_of_lst(head, command[i], var_name, mem);
		}
		else
			return (print_stderror(1, 3, "bash: export: `", command[i],
					"': not a valid identifier\n"));
	}
	return (0);
}
