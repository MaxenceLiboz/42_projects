/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:57:33 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/19 13:45:24 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_lst_env	*lst_env_new(char *name_var, char *var, t_list **mem)
{
	t_lst_env	*lst;

	lst = ft_malloc(mem, sizeof(t_lst_env) * 1);
	init_string(&lst->name_var, name_var, TRUE, mem);
	init_string(&lst->var, var, TRUE, mem);
	lst->next = 0;
	return (lst);
}

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

void	lst_env_add_front(t_lst_env **lst, t_lst_env *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}

int	lst_env_clear(t_lst_env **lst)
{
	t_lst_env	*save;

	if (!*lst)
		return (0);
	while (*lst)
	{
		save = (*lst)->next;
		if ((*lst)->name_var.str)
			reinit_string(&(*lst)->name_var);
		if ((*lst)->var.str)
			reinit_string(&(*lst)->var);
		free(*lst);
		*lst = save;
	}
	*lst = 0;
	return (0);
}

void	lst_env_delone(t_lst_env *prev, t_lst_env *to_del, t_lst_env **head)
{
	if (!to_del)
		return ;
	if (prev == to_del)
		*head = to_del->next;
	else
		prev->next = to_del->next;
	reinit_string(&to_del->name_var);
	reinit_string(&to_del->var);
	free(to_del);
}
