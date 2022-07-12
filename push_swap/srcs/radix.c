/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:48:52 by maxencelibo       #+#    #+#             */
/*   Updated: 2021/12/28 15:50:01 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
	1: Radix sort for lst size over 200
*/
void	radix(t_list **stack_a, t_list **stack_b)
{
	int	i;
	int	size;
	int	size_tmp;
	int	count;

	size = ft_lstsize(*stack_a);
	i = 0;
	size_tmp = size;
	count = 0;
	while (!ft_lstsorted(*stack_a))
	{
		while (size--)
		{
			if ((((*stack_a)->index >> i) & 1) == 1)
				ra(stack_a, 1);
			else
				pb(stack_a, stack_b);
		}
		while (ft_lstsize(*stack_b) != 0)
			pa(stack_a, stack_b);
		size = size_tmp;
		i++;
	}
}
