/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_functions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:19:41 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/12 22:48:41 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_lst_env	*lst_env_last(t_lst_env *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	lst_env_size(t_lst_env *lst)
{
	int		size;

	if (!lst)
		return (0);
	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

void	lst_env_swap(t_lst_env **head, t_lst_env **next)
{
	t_string	temp;

	temp = (*head)->name_var;
	(*head)->name_var = (*next)->name_var;
	(*next)->name_var = temp;
	temp = (*head)->var;
	(*head)->var = (*next)->var;
	(*next)->var = temp;
}

void	lst_env_sort(t_lst_env **env)
{
	t_lst_env	*head;
	t_lst_env	*next;

	if (!env)
		return ;
	head = *env;
	while (head)
	{
		next = head->next;
		while (next)
		{
			if (ft_strncmp(head->name_var.str, next->name_var.str,
					head->name_var.size) > 0)
				lst_env_swap(&head, &next);
			next = next->next;
		}
		head = head->next;
	}
}

t_string	lst_env_find_name_var(t_lst_env *env, char *str)
{
	t_lst_env	*tmp;
	t_string	null;

	null.str = 0;
	if (!str)
		return (null);
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name_var.str, str,
				tmp->name_var.size) == 0)
			return (tmp->var);
		tmp = tmp->next;
	}
	return (null);
}
