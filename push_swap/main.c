/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 08:06:41 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/10 10:53:15 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
	1: If list sorted return
	2: Send to the appropriate sort algorithm
*/
void	send_to_be_sort(t_list **a, t_list **b, int size)
{
	if (ft_lstsorted(*a))
		return ;
	set_index(a);
	if (size <= 3)
		small_sort(a);
	else if (size <= 10)
		mid_sort(a, b);
	else if (size <= 200)
		big_sort(a, b, 30);
	else
		radix(a, b);
}

/*
	1: Check number of args
	2: Add args to a list, if error return
	3: Send to the different sort algorithm
	4: free
*/
int	main(int argc, char **argv)
{
	t_list		*a;
	t_list		*b;

	a = NULL;
	b = NULL;
	if (argc < 2)
		return (0);
	if (argv[1][0] == 0 || !get_int(&a, argc, argv))
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	send_to_be_sort(&a, &b, ft_lstsize(a));
	return (ft_lstclear(&a, free));
}
