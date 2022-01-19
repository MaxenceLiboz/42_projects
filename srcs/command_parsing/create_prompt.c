/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:35:52 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/19 09:13:54 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_string	create_prompt(t_list **mem)
{
	t_string	dst;
	char		*pwd;

	pwd = 0;
	pwd = getcwd(pwd, 0);
	init_string(&dst, BLUE, TRUE, mem);
	dup_string(&dst, pwd, dst.size - 1, mem);
	dup_string(&dst, END_COLOR, dst.size - 1, mem);
	dup_string(&dst, " 👉 ", dst.size - 1, mem);
	free(pwd);
	return (dst);
}
