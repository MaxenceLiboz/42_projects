/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:58:59 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/28 08:36:43 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	check_arg(char **str, int *i, int *n)
{
	int	k;
	int	j;

	k = 1;
	j = 1;
	while (ft_strncmp(str[*i], "-n", 2) == 0)
	{
		while (str[*i][j])
		{
			if (str[*i][j] != 'n')
				return ;
			j++;
		}
		if (str[*i][j] == '\0')
			*n = 1;
		*i += 1;
	}
}

int	ft_echo(char **str)
{
	int		n;
	int		i;

	n = 0;
	i = 1;
	if (!str[1])
		return (printf("\n") - 1);
	if (!str[2] && n == 1)
		return (printf(""));
	check_arg(str, &i, &n);
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