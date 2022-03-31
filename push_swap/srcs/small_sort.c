/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 08:24:36 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/18 08:50:34 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
	1: Sort the list in Maximum 3 command
*/
void	small_sort(t_list **a)
{
	while (!ft_lstsorted(*a))
	{
		if (sa(a, 0, 1))
			;
		else if ((*a)->index < (*a)->next->next->index)
		{
			sa(a, 1, 1);
			ra(a, 1);
		}
		else if ((*a)->index > (*a)->next->next->index)
			rra(a, 1);
	}
}
