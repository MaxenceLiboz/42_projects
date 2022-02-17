/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:01:09 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/17 10:19:18 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Create the prompt that is going to be display with readline
*/
t_string	create_prompt(t_string pwd, t_prg *prg)
{
	t_string	dst;

	init_string(&dst, BLUE, TRUE, prg);
	add_string(&dst, pwd.str, dst.size - 1, prg);
	add_string(&dst, YELLOW, dst.size - 1, prg);
	add_string(&dst, " >> ", dst.size - 1, prg);
	add_string(&dst, END_COLOR, dst.size - 1, prg);
	return (dst);
}
