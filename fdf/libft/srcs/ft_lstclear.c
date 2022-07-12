/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:38:32 by mliboz            #+#    #+#             */
/*   Updated: 2021/11/29 09:27:47 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*save;

	if (!*lst)
		return ;
	while (*lst)
	{
		save = (*lst)->next;
		if ((*lst)->content)
			del((*lst)->content);
		free(*lst);
		*lst = save;
	}
	*lst = 0;
}
