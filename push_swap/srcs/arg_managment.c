/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_managment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:37:16 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/01/18 08:38:00 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
	1: Check if there are only numerical number
*/
static int	check_alph(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ((str[i] >= '0' && str[i] <= '9'))
		i++;
	if (str[i] != 0)
		return (0);
	return (1);
}

/*
	1: Check if the value is already in the list
*/
static int	check_int(t_list *a, t_list *value)
{
	int		i;

	i = 0;
	if (!a)
		return (1);
	while (a)
	{
		if (a->content == value->content && a != value)
			return (0);
		a = a->next;
		i++;
	}
	return (1);
}

/*
	1: Fill str by spliting the argv 1
	2: Return the size of the char **
*/
static int	fill_str(char *arg, char ***str)
{
	int		i;

	i = 0;
	str[0] = ft_split(arg, ' ');
	while (str[0][i] != 0)
		i++;
	return (i);
}

/*
	1: Free the char ** terminated by null value if argc == 2
*/
static void	free_str(char **str, int argc)
{
	int		i;

	i = 0;
	if (argc != 2)
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
}

/*
	1: Check if its one string of argument or a bunch of them
	2: Atoi the arguments one by one from the last, and check for error
	3: Add the new element in the front of the list
*/
int	get_int(t_list **a, int argc, char **argv)
{
	int		i;
	t_list	*new;
	char	**str;

	i = argc;
	if (argc == 2)
		i = fill_str(argv[1], &str);
	else
		str = argv;
	while (i--)
	{
		if (argc != 2 && i == 0)
			break ;
		new = ft_lstnew(ft_atoi(str[i]));
		ft_lstadd_front(a, new);
		if (!new || !check_int(*a, new) || !check_alph(str[i])
			|| ft_atoll(str[i]) > INT_MAX || ft_atoll(str[i]) < INT_MIN)
		{
			free_str(str, argc);
			return (ft_lstclear(a, free));
		}
	}
	free_str(str, argc);
	return (1);
}
