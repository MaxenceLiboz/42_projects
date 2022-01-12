/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:22:24 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/12 11:03:00 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	head->env = NULL;
	head->export = NULL;
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
