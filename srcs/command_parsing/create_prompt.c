/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:35:52 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/13 13:49:37 by maxencelibo      ###   ########.fr       */
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

t_string	create_prompt(void)
{
	t_string	dst;
	char		*pwd;

	pwd = 0;
	pwd = getcwd(pwd, 0);
	init_string(&dst, BLUE, TRUE);
	dup_string(&dst, pwd, dst.size - 1);
	dup_string(&dst, END_COLOR, dst.size - 1);
	dup_string(&dst, " 👉 ", dst.size - 1);
	free(pwd);
	return (dst);
}
