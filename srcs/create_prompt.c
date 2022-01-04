/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:35:52 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/04 15:19:25 by mliboz           ###   ########.fr       */
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

char	*create_prompt(char *color, char *str)
{
	char	*dst;
	int		size;
	int		colorlen;
	int		end_colorlen;
	int		strlen;

	colorlen = ft_strlen(color);
	end_colorlen = ft_strlen(END_COLOR);
	strlen = ft_strlen(str);
	size = colorlen + end_colorlen + strlen;
	dst = malloc(sizeof(char) * (size + 4));
	if (!dst)
		return (0);
	ft_strcat(dst, color);
	ft_strcat(dst, str);
	ft_strcat(dst, END_COLOR);
	ft_strcat(dst, " 👉 ");
	return (dst);
}
