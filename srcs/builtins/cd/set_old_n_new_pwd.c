/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_old_n_new_pwd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:35:28 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/17 10:23:55 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	set the OLDPWD in our envp lists
*/
void	set_oldpwd_env(t_head_env *head, t_string *pwd, t_prg *prg)
{
	t_lst_env	*env;
	t_lst_env	*export;

	env = head->env;
	export = head->export;
	while (ft_strncmp(env->name_var.str, "OLDPWD", 7) != 0 && env->next)
		env = env->next;
	while (ft_strncmp(export->name_var.str, "OLDPWD", 7) != 0 && export->next)
		export = export->next;
	if (ft_strncmp(export->name_var.str, "OLDPWD", 7) == 0)
	{
		init_string(&export->var, pwd->str, TRUE, prg);
		init_string(&env->var, pwd->str, TRUE, prg);
	}
	else
	{
		lst_env_add_front(&head->env, lst_env_new("OLDPWD",
				sub_string(pwd->str, 0, pwd->size - 1, prg).str, prg));
		lst_env_add_front(&head->export, lst_env_new("OLDPWD",
				sub_string(pwd->str, 0, pwd->size - 1, prg).str, prg));
		lst_env_sort(&head->export);
	}
}

/*
	set the PWD in our envp lists	
*/
void	set_new_pwd_env(t_head_env *head, t_string *pwd, t_prg *prg)
{
	t_lst_env	*env;
	t_lst_env	*export;

	env = head->env;
	export = head->export;
	if (lst_env_find_name_var(head->export, "PWD").max_size != 0)
	{
		while (ft_strncmp(env->name_var.str, "PWD", 4) != 0 && env->next)
		env = env->next;
		if (!env->next)
			lst_env_add_front(&head->env, lst_env_new("PWD",
					sub_string(pwd->str, 0, pwd->size - 1, prg).str, prg));
		while (ft_strncmp(export->name_var.str, "PWD", 4) != 0 && export->next)
		export = export->next;
		export->var = sub_string(pwd->str, 0, pwd->size - 1, prg);
		env->var = sub_string(pwd->str, 0, pwd->size - 1, prg);
	}
}
