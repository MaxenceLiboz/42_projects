/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:35:52 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/11 13:55:37 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_strcat(char *dest, char *src)
{
	int		i_dest;
	int		i_src;

	i_dest = 0;
	i_src = 0;
	while (dest[i_dest])
		i_dest++;
	while (src[i_src])
	{
		dest[i_dest + i_src] = src[i_src];
		i_src++;
	}
	dest[i_dest + i_src] = '\0';
}

t_string	create_prompt(char *str)
{
	t_string	dst;

	if (!str)
		exit(-1);
	init_string(&dst, BLUE, TRUE);
	dup_string(&dst, str, dst.size - 1);
	dup_string(&dst, END_COLOR, dst.size - 1);
	dup_string(&dst, " 👉 ", dst.size - 1);
	return (dst);
}
