/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_functions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:19:41 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/26 13:28:55 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

char	**lst_env_to_array(t_lst_env *env, t_list **mem)
{
	char		**envp;
	t_string	*temp;
	t_lst_env	*head;
	int			i;

	envp = 0;
	if (!env)
		return (envp);
	i = 0;
	head = env;
	temp = ft_malloc(mem, sizeof(t_string) * (lst_env_size(env) + 1));
	while (head)
	{
		init_string(&temp[i], head->name_var.str, TRUE, mem);
		add_string(&temp[i], "=", temp[i].size - 1, mem);
		add_string(&temp[i], head->var.str, temp[i].size - 1, mem);
		head = head->next;
		i++;
	}
	temp[i].str = 0;
	return (envp = strings_to_array(temp, mem));
}
