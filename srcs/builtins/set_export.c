/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:22:24 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/10 18:36:27 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*find_arg(t_lst_env *env, char *str)
{
	t_lst_env	*tmp;

	tmp = env;
	while (tmp->next)
	{
		if (ft_strncmp(tmp->name_var.str, str,
				ft_strlen(tmp->name_var.str)) == 0)
			return (tmp->var.str);
		tmp = tmp->next;
	}
	return (NULL);
}

//In this function, need to set var.type to ENV if the name_var contain '='
//As well, the substr function isn't working if the = is not found
static int	init_lst_str(char *envp, t_lst_env *new_export, t_lst_env *new_env)
{
	int	i;

	i = 0;
	init_string(&new_export->name_var, "", TRUE);
	init_string(&new_env->name_var, "", TRUE);
	init_string(&new_export->var, "", TRUE);
	init_string(&new_env->var, "", TRUE);
	while (envp[i] != '=' && envp[i])
		i++;
	sub_string(&new_export->name_var, envp, 0, i);
	sub_string(&new_env->name_var, envp, 0, i);
	sub_string(&new_env->var, envp, i + 1, (ft_strlen(envp) - i) + 1);
	sub_string(&new_export->var, envp, i + 1, (ft_strlen(envp) - i) + 1);
	return (1);
}

static void	set_struct(t_swap *swap, t_lst_env **env)
{
	swap->last = NULL;
	swap->head = *env;
	swap->next = swap->head->next;
}	

void	ascii_ordering(t_lst_env **env)
{
	t_swap	swap;

	set_struct(&swap, env);
	while (swap.next)
	{
		if (ft_strncmp(swap.head->name_var.str, swap.next->name_var.str,
				swap.head->name_var.size) > 0)
		{
			swap.head->next = swap.next->next;
			swap.next->next = swap.head;
			if (swap.last)
				swap.last->next = swap.next;
			else
				*env = swap.next;
			set_struct(&swap, env);
		}
		else
		{
				swap.last = swap.head;
				swap.head = swap.last->next;
				swap.next = swap.head->next;
		}
	}
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
		new_export = ft_lstnew(0);
		new_env = ft_lstnew(0);
		ft_lstadd_back(&head->export, new_export);
		ft_lstadd_back(&head->env, new_env);
		if (!init_lst_str(envp[i], new_export, new_env))
			return (0);
		i++;
	}
	ascii_ordering(&head->export);
	return (1);
}
