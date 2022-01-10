/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:34:57 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/10 12:42:02 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sub_string(t_string *string, int start, int end, char *src)
{
	char	*dst;

	dst = ft_substr(src, start, end - start);
	add_string_str(string, dst, 0);
	free(dst);
}
