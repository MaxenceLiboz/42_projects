/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:03:47 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/18 08:35:23 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
	1: Loop throughout the all list
	2: Each time we get a smaller value increase i and return it
*/
int	get_index(t_list *lst, int value)
{
	int		i;

	i = 1;
	while (lst)
	{
		if (lst->content < value && lst->content != value)
			i++;
		lst = lst->next;
	}
	return (i);
}

/*
	1: For each element of the list, get the index
*/
void	set_index(t_list **lst)
{
	t_list	*head;

	head = *lst;
	while (head)
	{
		head->index = get_index(*lst, head->content);
		head = head->next;
	}
}

/*
	1: Get the minimum index of the list
*/
int	get_index_min(t_list *lst)
{
	int		min;
	int		value;

	if (!lst)
		return (-1);
	min = lst->index;
	value = min;
	ra(&lst, 0);
	while (lst && lst->index != value)
	{
		if (lst->index < min)
			min = lst->index;
		ra(&lst, 0);
	}
	return (min);
}

/*
	1: Get the maximum index of the list
*/
int	get_index_max(t_list *lst)
{
	int		max;
	int		value;

	if (!lst)
		return (-1);
	max = lst->index;
	value = max;
	ra(&lst, 0);
	while (lst && lst->index != value)
	{
		if (lst->index >= max)
			max = lst->index;
		ra(&lst, 0);
	}
	return (max);
}

/*
	1: Check how many time the list have to rotate before it's the value that
	   we want
	2: Check how many time the list have to rotate before it's back to its
	   original value
	3: Depending on the count return 1 if rra is faster and 0 if it is ra
	4: If we don't have of to rotate
*/
int	index_nearest(t_list *lst, int value)
{
	int		i;
	int		y;
	int		index;

	i = 0;
	y = 0;
	if (!lst)
		return (-1);
	index = lst->index;
	while (lst->index != value)
	{
		ra(&lst, 0);
		i++;
	}
	while (lst->index != index)
	{
		ra(&lst, 0);
		y++;
	}
	if (i <= y && i != 0)
		return (0);
	else if (y <= i && y != 0)
		return (1);
	else
		return (-1);
}
