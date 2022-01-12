/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:59:14 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/05 14:59:54 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_pwd(char **str)
{
	char	*dst;
	int		i;

	i = 0;
	if (str[1] != NULL)
		if (ft_strncmp(str[1], "|", 2) != 0)
			return (error("pwd: too many arguments", 0));
	dst = NULL;
	dst = getcwd(dst, 0);
	if (!dst)
		return (NULL);
	return (dst);
}
