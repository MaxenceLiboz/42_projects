/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:38:32 by mliboz            #+#    #+#             */
/*   Updated: 2022/03/09 13:23:40 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	ft_lstclear(t_list **lst)
{
	t_list	*save;

	if (!*lst)
		return (0);
	while ((*lst)->next)
	{
		save = (*lst)->next;
		if ((*lst)->ptr)
			free((*lst)->ptr);
		free(*lst);
		*lst = save;
	}
	*lst = 0;
	return (0);
}
