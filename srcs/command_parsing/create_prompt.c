/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:35:52 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/08 16:32:20 by maxencelibo      ###   ########.fr       */
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

	init_string(&dst, BLUE, TRUE);
	add_string_str(&dst, str, dst.size - 1);
	add_string_str(&dst, END_COLOR, dst.size - 1);
	add_string_str(&dst, " 👉 ", dst.size - 1);
	free(str);
	return (dst);
}
