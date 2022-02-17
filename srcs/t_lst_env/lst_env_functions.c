/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:57:33 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/17 13:30:47 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Create a new instance of a node lst_env
*/
t_lst_env	*lst_env_new(char *name_var, char *var, t_prg *prg)
{
	t_lst_env	*lst;

	lst = ft_malloc(prg, sizeof(t_lst_env) * 1);
	init_string(&lst->name_var, name_var, TRUE, prg);
	init_string(&lst->var, var, TRUE, prg);
	lst->next = 0;
	return (lst);
}

/*
	Add a node at the back of the list
*/
void	lst_env_add_back(t_lst_env **lst, t_lst_env *new)
{
	t_lst_env	*last;

	if (!new)
		return ;
	new->next = 0;
	if (!*lst)
	{
		*lst = new;
	}
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

/*
	Add a node in front of the list
*/
void	lst_env_add_front(t_lst_env **lst, t_lst_env *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}

/*
	Remove a node form the list
*/
void	lst_env_delone(t_lst_env *prev, t_lst_env *to_del, t_lst_env **head)
{
	if (!to_del)
		return ;
	if (prev == to_del)
		*head = to_del->next;
	else
		prev->next = to_del->next;
}
