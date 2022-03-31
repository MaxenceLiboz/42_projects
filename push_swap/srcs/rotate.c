/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:42:39 by maxencelibo       #+#    #+#             */
/*   Updated: 2021/12/17 15:07:00 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
	1: If lst doesn't exist or we have only one element return
	2: Make the first element of a become the last
*/
void	ra(t_list **a, int m)
{
	t_list	*last;
	t_list	*first;

	if (!*a || !(*a)->next)
		return ;
	last = ft_lstlast(*a);
	first = *a;
	(*a) = (*a)->next;
	last->next = first;
	first->next = 0;
	if (m != 0)
		ft_putstr_fd("ra\n", 1);
}

/*
	1: If lst doesn't exist or we have only one element return
	2: Make the first element of a become the last
*/
void	rb(t_list **b, int m)
{
	t_list	*last;
	t_list	*first;

	if (!*b || !(*b)->next)
		return ;
	last = ft_lstlast(*b);
	first = *b;
	(*b) = (*b)->next;
	last->next = first;
	first->next = 0;
	if (m != 0)
		ft_putstr_fd("rb\n", 1);
}

/*
	1: Use rotate for both stack
*/
void	rr(t_list **a, t_list **b)
{
	ra(a, 0);
	rb(b, 0);
	ft_putstr_fd("rr\n", 1);
}
