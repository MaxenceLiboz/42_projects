/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:01:09 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/16 18:01:30 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Create the prompt that is going to be display with readline
*/
t_string	create_prompt(t_string pwd, t_list **mem)
{
	t_string	dst;

	init_string(&dst, BLUE, TRUE, mem);
	add_string(&dst, pwd.str, dst.size - 1, mem);
	add_string(&dst, YELLOW, dst.size - 1, mem);
	add_string(&dst, " >> ", dst.size - 1, mem);
	add_string(&dst, END_COLOR, dst.size - 1, mem);
	return (dst);
}
