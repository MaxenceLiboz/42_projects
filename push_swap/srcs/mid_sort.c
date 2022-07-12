/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mid_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 08:26:13 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/03 10:34:55 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>
/*
	1: Push the 2 smallest content to b
	2: Use small sort
	3: Push back the two content
*/
void	mid_sort(t_list **a, t_list **b)
{
	while (ft_lstsize(*a) != 3)
	{
		while (get_index_min(*a) != (*a)->index)
		{
			if (index_nearest(*a, get_index_min(*a)) == 1)
				rra(a, 1);
			else if (index_nearest(*a, get_index_min(*a)) == 0)
				ra(a, 1);
		}
		pb(a, b);
	}
	small_sort(a);
	while (ft_lstsize(*b) != 0)
		pa(a, b);
}
