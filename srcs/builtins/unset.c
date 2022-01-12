/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:59:28 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/12 17:13:44 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	unset_link(t_lst_env *last, t_lst_env *actual,
	t_lst_env *next, char *name)
{
	if (ft_strncmp(name, actual->name_var.str, ft_strlen(name)) != 0)
		return ;
	if (next)
		last->next = next;
	lst_env_clear(&actual);
}

static void	find_link(t_head_env *head, char *name)
{
	t_lst_env	*last;
	t_lst_env	*actual;
	t_lst_env	*next;

	actual = head->export;
	last = actual;
	next = actual->next;
	while (ft_strncmp(name, actual->name_var.str, ft_strlen(name)) != 0 && next)
	{
		last = actual;
		actual = actual->next;
		next = actual->next;
	}
	unset_link(last, actual, next, name);
	actual = head->env;
	last = actual;
	next = actual->next;
	while (ft_strncmp(name, actual->name_var.str, ft_strlen(name)) != 0 && next)
	{
		last = actual;
		actual = actual->next;
		next = actual->next;
	}
	unset_link(last, actual, next, name);
}

void	ft_unset(t_head_env *head, char **command)
{
	int	i;

	i = 1;
	if (!command[i])
		return ;
	while (command[i])
	{
		if (control_args(command[i]) == 0)
			find_link(head, command[i]);
		else
		{
			ft_putstr_fd("bash: unset: `", 2);
			ft_putstr_fd(command[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		i++;
	}
}
