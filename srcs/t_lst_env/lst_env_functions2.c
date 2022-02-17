/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_functions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:19:41 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/17 10:23:55 by tarchimb         ###   ########.fr       */
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
			if (head->name_var.str && next->name_var.str)
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

char	**lst_env_to_array(t_lst_env *env, t_prg *prg)
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
	temp = ft_malloc(prg, sizeof(t_string) * (lst_env_size(env) + 1));
	while (head)
	{
		init_string(&temp[i], head->name_var.str, TRUE, prg);
		add_string(&temp[i], "=", temp[i].size - 1, prg);
		add_string(&temp[i], head->var.str, temp[i].size - 1, prg);
		head = head->next;
		i++;
	}
	temp[i].str = 0;
	return (envp = strings_to_array(temp, prg));
}
