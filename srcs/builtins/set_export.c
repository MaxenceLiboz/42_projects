/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:22:24 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/20 10:57:31 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//In this function, need to set var.type to ENV if the name_var contain '='
//As well, the substr function isn't working if the = is not found
static int	head_env_init(char *envp, t_lst_env *new_export,
			t_lst_env *new_env, t_list **mem)
{
	int	i;

	i = 0;
	while (envp[i] != '=' && envp[i])
		i++;
	new_export->name_var = sub_string(envp, 0, i, mem);
	new_env->name_var = sub_string(envp, 0, i, mem);
	if (ft_strncmp(new_export->name_var.str, "OLDPWD", 7))
	{
		new_export->var = sub_string(envp, i + 1, (ft_strlen(envp) - i) + 1,
				mem);
		new_env->var = sub_string(envp, i + 1, (ft_strlen(envp) - i) + 1, mem);
	}
	return (1);
}

//Should we do use add_back or add_front
int	set_export(char **envp, t_head_env *head, t_list **mem)
{
	t_lst_env	*new_export;
	t_lst_env	*new_env;
	int			i;

	i = 0;
	head->env = NULL;
	head->export = NULL;
	while (envp[i])
	{
		new_export = lst_env_new(NULL, NULL, mem);
		new_env = lst_env_new(NULL, NULL, mem);
		lst_env_add_back(&head->export, new_export);
		lst_env_add_back(&head->env, new_env);
		if (!head_env_init(envp[i], new_export, new_env, mem))
			return (0);
		i++;
	}
	lst_env_sort(&head->export);
	return (1);
}
