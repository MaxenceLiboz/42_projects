/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:40:11 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/01/03 10:27:19 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
	1: Depending on the mandatory variable and the size
		1: m = 0 => Do nothing if second element is bigger than first
		2: m = 1 => Swap anyway
*/
int	sa(t_list **a, int m, int p)
{
	t_list	*temp;

	if (ft_lstsize(*a) <= 1 || ((*a)->index < (*a)->next->index && m == 0))
		return (0);
	temp = *a;
	*a = (*a)->next;
	temp->next = (*a)->next;
	(*a)->next = temp;
	if (p == 1)
		ft_putstr_fd("sa\n", 1);
	return (1);
}

/*
	1: Depending on the mandatory variable and the size
		1: m = 0 => Do nothing if second element is bigger than first
		2: m = 1 => Swap anyway
*/
int	sb(t_list **b, int m, int p)
{
	t_list	*temp;

	if (ft_lstsize(*b) <= 1 || ((*b)->index < (*b)->next->index && m == 0))
		return (0);
	temp = *b;
	*b = (*b)->next;
	temp->next = (*b)->next;
	(*b)->next = temp;
	if (p == 1)
		ft_putstr_fd("sb\n", 1);
	return (1);
}

/*
	1: Use both sa and sp in one command
*/
void	ss(t_list **a, t_list **b)
{
	int		i;

	i = sa(a, 0, 1);
	i += sb(b, 0, 1);
	if (i > 0)
		ft_putstr_fd("ss\n", 1);
}
