/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:59:28 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/16 17:32:38 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Remove the var and namevar from the list
*/
static void	unset_link(t_lst_env **head, t_lst_env *prev,
	t_lst_env *actual, char *name)
{
	if (ft_strncmp(name, actual->name_var.str, ft_strlen(name)) != 0)
		return ;
	lst_env_delone(prev, actual, head);
}

/*
	Get the previous and the actual var to unset
*/
static void	get_link(t_lst_env **prev, t_lst_env **actual, char *name)
{
	t_lst_env	*next;

	next = (*actual)->next;
	while (ft_strncmp(name, (*actual)->name_var.str,
			ft_strlen(name) + 1) != 0 && next)
	{
		*prev = *actual;
		*actual = (*actual)->next;
		next = (*actual)->next;
	}
}

/*
	Find the var to unset and use unset_link();
*/
static void	find_link(t_head_env **head, char *name)
{
	t_lst_env	*prev;
	t_lst_env	*actual;

	actual = (*head)->export;
	prev = actual;
	get_link(&prev, &actual, name);
	unset_link(&(*head)->export, prev, actual, name);
	actual = (*head)->env;
	prev = actual;
	get_link(&prev, &actual, name);
	unset_link(&(*head)->env, prev, actual, name);
}

/*
	Reproducing unset command in bash
*/
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
