/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:02:19 by mliboz            #+#    #+#             */
/*   Updated: 2021/12/15 18:02:42 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
	1: Until stack b is not empty get the max, use either rb or rrb
	   depending on the place of the max index
	2: Push in stack a
*/
static void	big_sort_p2(t_list **lst, t_list **lst2)
{
	while (ft_lstsize(*lst2) != 0)
	{
		while (get_index_max(*lst2) != (*lst2)->index)
		{
			if (index_nearest(*lst2, get_index_max(*lst2)) == 1)
				rrb(lst2, 1);
			else if (index_nearest(*lst2, get_index_max(*lst2)) == 0)
				rb(lst2, 1);
		}
		pa(lst, lst2);
	}
}

/*
	1: Sort by chunck (according to a specific percentage)
	2: Push in stack b all index depending on the current percentage
	3: Send to a function that sort from max to min pushing in stack a
*/
void	big_sort(t_list **a, t_list **b, int p)
{
	int		size;
	int		percent;

	size = ft_lstsize(*a);
	percent = p;
	while (ft_lstsize(*a) != 0)
	{	
		if ((*a)->index <= size * percent / 100)
		{
			pb(a, b);
			if (!(get_index_min(*a) <= size * percent / 100))
				percent += p;
			if ((*b)->index < size * percent / 100 - ((size * p / 100) / 2))
				rr(a, b);
		}
		else
			ra(a, 1);
	}
	big_sort_p2(a, b);
}
