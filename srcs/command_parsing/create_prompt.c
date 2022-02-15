/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:35:52 by mliboz            #+#    #+#             */

/*   Updated: 2022/02/15 14:39:54 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
