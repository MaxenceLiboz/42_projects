/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_term.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:31:57 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/09 16:13:35 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_term_env(t_list **mem)
{
	char	*tmp;
	
	(void)mem;
	// if (tgetent(NULL, getenv("TERM")) == ERR)
	// 	ft_error_exit(mem, 1, "getent: error");
	tgetent(NULL, getenv("TERM"));
	tmp = tgetstr("cl", NULL);
	// if (tmp == NULL)
	// 	ft_error_exit(mem, 1, "tgetstr: error");
	tputs(tmp, 10, putchar);
}
