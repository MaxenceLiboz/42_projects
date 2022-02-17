/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:59:35 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/16 17:35:00 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Reporducing env command in bash
	No argument handle
*/
int	ft_env(t_lst_env *lst, char **command)
{
	t_lst_env	*tmp;

	tmp = lst;
	if (command[1])
		return (print_stderror(FAIL, 1, "use the command whitout arguments"));
	while (tmp)
	{
		if (tmp->var.str != NULL)
			printf("%s=%s\n", tmp->name_var.str, tmp->var.str);
		tmp = tmp->next;
	}
	return (0);
}
