/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:59:28 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/26 11:54:07 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	unset_link(t_lst_env **head, t_lst_env *prev,
	t_lst_env *actual, char *name)
{
	if (ft_strncmp(name, actual->name_var.str, ft_strlen(name)) != 0)
		return ;
	lst_env_delone(prev, actual, head);
}

static void	find_link(t_head_env **head, char *name)
{
	t_lst_env	*prev;
	t_lst_env	*actual;
	t_lst_env	*next;

	actual = (*head)->export;
	prev = actual;
	next = actual->next;
	while (ft_strncmp(name, actual->name_var.str, ft_strlen(name) + 1) != 0 && next)
	{
		prev = actual;
		actual = actual->next;
		next = actual->next;
	}
	unset_link(&(*head)->export, prev, actual, name);
	actual = (*head)->env;
	prev = actual;
	next = actual->next;
	while (ft_strncmp(name, actual->name_var.str, ft_strlen(name) + 1) != 0 && next)
	{
		prev = actual;
		actual = actual->next;
		next = actual->next;
	}
	unset_link(&(*head)->env, prev, actual, name);
}

int	ft_unset(t_head_env **head, char **command)
{
	int	i;

	i = 1;
	if (!command[i])
		return (0);
	while (command[i])
	{
		if (control_args(command[i]) == 0)
			find_link(head, command[i]);
		else
			print_stderror(1, 3, "unset: `", command[i],
				"': not a valid identifier");
		i++;
	}
	return (0);
}
