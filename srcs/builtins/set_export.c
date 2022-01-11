/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:22:24 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/11 09:57:36 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// static void	set_struct(t_swap *swap, t_lst_env **env)
// {
// 	swap->last = NULL;
// 	swap->head = *env;
// 	swap->next = swap->head->next;
// }	

// void	ascii_ordering(t_lst_env **env)
// {
// 	t_swap	swap;

// 	set_struct(&swap, env);
// 	while (swap.next)
// 	{
// 		if (ft_strncmp(swap.head->name_var.str, swap.next->name_var.str,
// 				swap.head->name_var.size) > 0)
// 		{
// 			swap.head->next = swap.next->next;
// 			swap.next->next = swap.head;
// 			if (swap.last)
// 				swap.last->next = swap.next;
// 			else
// 				*env = swap.next;
// 			set_struct(&swap, env);
// 		}
// 		else
// 		{
// 				swap.last = swap.head;
// 				swap.head = swap.last->next;
// 				swap.next = swap.head->next;
// 		}
// 	}
// }

//In this function, need to set var.type to ENV if the name_var contain '='
//As well, the substr function isn't working if the = is not found
static int	head_env_init(char *envp, t_lst_env *new_export,
			t_lst_env *new_env)
{
	int	i;

	i = 0;
	while (envp[i] != '=' && envp[i])
		i++;
	sub_string(&new_export->name_var, envp, 0, i);
	sub_string(&new_env->name_var, envp, 0, i);
	sub_string(&new_env->var, envp, i + 1, (ft_strlen(envp) - i) + 1);
	sub_string(&new_export->var, envp, i + 1, (ft_strlen(envp) - i) + 1);
	return (1);
}

//Should we do use add_back or add_front
int	set_export(char **envp, t_head_env *head)
{
	t_lst_env	*new_export;
	t_lst_env	*new_env;
	int			i;

	i = 0;
	while (envp[i])
	{
		new_export = lst_env_new("", "");
		new_env = lst_env_new("", "");
		lst_env_add_back(&head->export, new_export);
		lst_env_add_back(&head->env, new_env);
		if (!head_env_init(envp[i], new_export, new_env))
			return (0);
		i++;
	}
	lst_env_sort(&head->export);
	return (1);
}
