/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:58:59 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/18 11:31:50 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_echo(char **str)
{
	int		n;
	int		i;

	n = 0;
	i = 1;
	if (!str[1])
		return (printf("\n"));
	while (ft_strncmp(str[i], "-n", 3) == 0)
	{
		n = 1;
		i++;
	}
	if (!str[2] && n == 1)
		return (printf(""));
	while (str[i])
	{
		printf("%s", str[i]);
		i++;
		if (str[i])
			printf(" ");
	}
	if (!n)
		printf("\n");
	return (0);
}