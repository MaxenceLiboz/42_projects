/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_term.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:31:57 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/10 09:21:21 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_term_env(t_list **mem)
{
	char	*tmp;

	if (tgetent(NULL, getenv("TERM")) == ERR)
		ft_error_exit(mem, 1, "getent: error");
	tmp = tgetstr("cl", NULL);
	if (tmp == NULL)
		ft_error_exit(mem, 1, "tgetstr: error");
	tputs(tmp, 10, putchar);
}
