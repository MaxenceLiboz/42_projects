/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:59:35 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/13 01:54:39 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*Still need to fix check ENV, it's not yet working,
	 have to check the '=' in set_lst_env*/
void	ft_env(t_lst_env *lst, char **command)
{
	t_lst_env	*tmp;

	tmp = lst;
	if (command[1])
		return ((void)print_stderror(1, 0,
				"Actually, we are not taking arguments with env\n"));
	while (tmp)
	{
		printf("%s=%s\n", tmp->name_var.str, tmp->var.str);
		tmp = tmp->next;
	}
}

//Have to check if variable got a value, if no don't print the =
void	print_export(t_head_env *head)
{
	t_lst_env	*export;
	t_lst_env	*env;

	export = head->export;
	env = head->env;
	while (export)
	{
		printf("declare -x %s", export->name_var.str);
		if (lst_env_find_name_var(env, export->name_var.str).str == 0)
			printf("\n");
		else if (export->var.str && *export->var.str)
			printf("=\"%s\"\n", export->var.str);
		else
			printf("=\"\"\n");
		export = export->next;
	}
}
