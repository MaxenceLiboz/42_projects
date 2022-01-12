/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:15:42 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/01/12 11:24:54 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static void	printf_argv(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
		printf("%s\n", argv[i++]);
}

int	main(int argc, char **argv)
{
	printf_argv(argc, argv);
	return (0);
}
