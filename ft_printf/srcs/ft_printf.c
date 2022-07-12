/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:49:01 by mliboz            #+#    #+#             */
/*   Updated: 2021/11/18 09:35:02 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

/*
	1: Get the index of the arg corresponding to the index of 
	   the pointer to functions
	2: If the arg is valid and not a % print the arg
	3: If the arg is valid and it's a % print %
	4: Return the total of chars print 
*/
int	ft_print_arg(char arg, va_list args, int (**f)(void *))
{
	int		return_value;
	int		arg_i;

	return_value = 0;
	arg_i = ft_check_args(arg);
	if (arg_i >= 0 && arg_i != 7)
		return_value = f[arg_i]((void *)va_arg(args, void *));
	else if (arg_i >= 0)
		return_value = ft_putchar('%');
	return (return_value);
}

/*
	1: Start the list
	2: If there is % print the arg
	3: Else print the char
	4: End the list
	5: All the functions that print something return the number of chars
	   they print, everything is add up and return.
*/
int	ft_printf(const char *str, ...)
{
	va_list		args;
	int			i;
	int			return_value;
	int			(*f[NUM_F])(void *);

	return_value = 0;
	i = 0;
	ft_init_f(f);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
			return_value += ft_print_arg(str[i++ + 1], args, f);
		else
			return_value += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (return_value);
}
