/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:40:44 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/12 18:29:44 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//Have to check if variable got a value, if no don't print the =
static void	print_export(t_lst_env *export)
{
	t_lst_env	*head;

	head = export;
	while (head)
	{
		printf("declare -x %s", head->name_var.str);
		if (head->var.str && !*head->var.str)
			printf("=\"\"\n");
		else if (!head->var.str)
			printf("\n");
		else
			printf("=\"%s\"\n", head->var.str);
		head = head->next;
	}
}

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
	if (ft_isalnum(str[i]) == 0)
		return (1);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

//change sorting to avoid to iterate on all the lst again
static void	add_elem_to_lst(char *arg, t_head_env *head)
{
	t_lst_env	*new_export;
	t_lst_env	*new_env;
	int			c;

	new_export = lst_env_new("", NULL);
	c = ft_strchr_len(arg, '=');
	new_env = NULL;
	sub_string(&new_export->name_var, arg, 0, c);
	if (ft_strchr(arg, '=') != 0)
	{
		new_env = lst_env_new("", NULL);
		sub_string(&new_env->name_var, arg, 0, c);
		sub_string(&new_env->var, arg, c + 1, ft_strlen(arg) - c);
		sub_string(&new_export->var, arg, c + 1, ft_strlen(arg) - c);
		lst_env_add_front(&head->env, new_env);
	}
	lst_env_add_front(&head->export, new_export);
	lst_env_sort(&head->export);
	return ;
}

static void	replace_elem_of_lst(t_head_env *head, char *var, char *var_name)
{
	t_lst_env	*export;
	t_lst_env	*env;
	int			c;

	export = head->export;
	env = head->env;
	c = ft_strchr_len(var, '=');
	while (ft_strncmp(var_name, export->name_var.str, ft_strlen(var_name)) != 0)
		export = export->next;
	while (ft_strncmp(var_name, env->name_var.str, ft_strlen(var_name)) != 0)
		env = env->next;
	sub_string(&env->var, var, c + 1, ft_strlen(var) - c);
	sub_string(&export->var, var, c + 1, ft_strlen(var) - c);
	return ;
}

void	ft_export(t_head_env *head, char **command)
{
	char	*var_name;
	int		i;

	i = 1;
	if (!command[i])
	{
		print_export(head->export);
		return ;
	}
	while (command[i])
	{
		var_name = ft_substr(command[i], 0, ft_strchr_len(command[i], '='));
		if (control_args(var_name) == 0)
		{
			if (lst_env_find_name_var(head->export, var_name).str == 0)
				add_elem_to_lst(command[i], head);
			else
				if (ft_strchr(command[i], '=') != 0)
					replace_elem_of_lst(head, command[i], var_name);
		}
		else
		{
			// dprintf(2, "bash: export `%s': not a valid identifier", var_name);
		}
		i++;
	}
	free(var_name);
	return ;
}
