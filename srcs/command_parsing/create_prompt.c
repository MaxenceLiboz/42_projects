/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:35:52 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/05 13:55:27 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_string	create_prompt(t_string pwd, t_list **mem)
{
	t_string	dst;

	init_string(&dst, BLUE, TRUE, mem);
	dup_string(&dst, pwd.str, dst.size - 1, mem);
	dup_string(&dst, END_COLOR, dst.size - 1, mem);
	dup_string(&dst, " 👉 ", dst.size - 1, mem);
	return (dst);
}
