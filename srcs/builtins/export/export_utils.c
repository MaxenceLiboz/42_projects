/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 10:37:17 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/17 10:23:55 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Print exported value with the name var and var if they have one
*/
int	print_export(t_head_env *head)
{
	t_lst_env	*export;
	t_lst_env	*env;

	export = head->export;
	env = head->env;
	while (export)
	{
		printf("declare -x %s", export->name_var.str);
		if (lst_env_find_name_var(env, export->name_var.str).str == 0)
			printf("\n");
		else if (export->var.str && *export->var.str)
			printf("=\"%s\"\n", export->var.str);
		else
			printf("=\"\"\n");
		export = export->next;
	}
	return (0);
}

/*
	Get the index of the variable c
*/
int	ft_strchr_len(const char *s, int c)
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

/*
	Check if the arg isalnum and does't start with a number
*/
t_bool	control_args(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (FAIL);
	if (ft_isalnum(str[i]) == 0 || (str[i] >= '0' && str[i] <= '9'))
		return (FAIL);
	i++;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

/*
	Add the argument to our export list and sort it
	If argument isn't null add it to the env list
*/
void	add_elem_to_lst(char *arg, t_head_env *head, t_prg *prg)
{
	t_lst_env	*new_export;
	t_lst_env	*new_env;
	int			c;

	new_export = lst_env_new("", NULL, prg);
	c = ft_strchr_len(arg, '=');
	new_env = NULL;
	new_export->name_var = sub_string(arg, 0, c, prg);
	if (ft_strchr(arg, '=') != 0)
	{
		new_env = lst_env_new("", NULL, prg);
		new_env->name_var = sub_string(arg, 0, c, prg);
		new_env->var = sub_string(arg, c + 1, ft_strlen(arg) - c, prg);
		new_export->var = sub_string(arg, c + 1, ft_strlen(arg) - c, prg);
		lst_env_add_front(&head->env, new_env);
	}
	lst_env_add_front(&head->export, new_export);
	lst_env_sort(&head->export);
}

/*
	Replace the old var with the new var in export list
	Check if name_var exist in env list
		- If not create and add the new element to the list
		- Else replace the old var with the new var in the list
*/
void	replace_elem_of_lst(t_head_env *head, char *var, char *var_name,
		t_prg *prg)
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
		env = lst_env_new("", NULL, prg);
		env->name_var = sub_string(export->name_var.str, 0,
				export->name_var.size, prg);
		env->var = sub_string(var, c + 1, ft_strlen(var) - c, prg);
		lst_env_add_front(&head->env, env);
	}
	env->var = sub_string(var, c + 1, ft_strlen(var) - c, prg);
	export->var = sub_string(var, c + 1, ft_strlen(var) - c, prg);
}
