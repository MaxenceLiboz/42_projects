/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:59:35 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/10 14:42:02 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*Still need to fix check ENV, it's not yet working,
	 have to check the '=' in set_lst_env*/
void	ft_lst_env(t_lst_env *lst)
{
	t_lst_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name_var.str, tmp->var.str);
		tmp = tmp->next;
	}
}
