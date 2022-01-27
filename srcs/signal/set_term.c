/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_term.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:31:57 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/27 15:36:28 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_term_env(void)
{
	int		ret;
	char	*tmp;

	ret = tgetent(NULL, getenv("TERM"));
	tmp = tgetstr("cl", NULL);
	tputs(tmp, 10, putchar);
}