/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:09:36 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/17 12:30:38 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*set_value_shlvl(int shlvl, t_string shlvl_var)
{
	char	*dst;

	dst = NULL;
	shlvl += ft_atoi(shlvl_var.str);
	if (shlvl <= -1)
		shlvl = 0;
	dst = ft_itoa(shlvl);
	if (dst == NULL)
		return (NULL);
	if (shlvl > 1000)
	{
		print_stderror(2, 3, "warning: shell level (",
			dst, ") too high, resetting to 1");
		shlvl = 1;
	}
	free(dst);
	dst = ft_itoa(shlvl);
	if (dst == NULL)
		return (NULL);
	return (dst);
}
