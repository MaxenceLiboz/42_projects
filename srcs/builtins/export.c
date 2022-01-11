/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:59:21 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/11 16:15:55 by tarchimb         ###   ########.fr       */
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
		printf("declare -x %s=\"%s\"\n", head->name_var.str,
			head->var.str);
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

static int	control_args(char *str)
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
	char		c;

	new_export = lst_env_new("", NULL);
	new_env = lst_env_new("", NULL);
	c = ft_strchr_len(arg, '=');
	sub_string(&new_export->name_var, arg, 0, c);
	sub_string(&new_env->name_var, arg, 0, c);
	if (ft_strchr(arg, '=') != 0)
	{
		sub_string(&new_export->var, arg, c + 1, ft_strlen(arg) - c);
		sub_string(&new_export->var, arg, c + 1, ft_strlen(arg) - c);
		lst_env_add_front(&head->export, new_env);
	}
	lst_env_add_front(&head->env, new_export);
	lst_env_sort(&head->export);
}

void	ft_export(t_head_env *head, t_command *args)
{
	if (!args->array[args->index].str)
		print_export(head->export);
	while (*args->array[args->index].str != '|' && args->index < args->size)
	{
		if (control_args(args->array[args->index].str) == 0)
			add_elem_to_lst(args->array[args->index].str, head);
		// else
		// 	print_wrong_arg(args);
		args->index += 1;
	}
	return ;
}
