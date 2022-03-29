/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:37:46 by mliboz            #+#    #+#             */
/*   Updated: 2021/11/18 09:52:05 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# define NUM_F 7
# define BASE "0123456789abcdef"
# define BASE_U "0123456789ABCDEF"
# define ARGS "cspdiuxX%"

int		ft_strlen(const char *s);
int		ft_putstr(const char *str);
int		ft_putchar(char c);
int		ft_putptr(void *ptr);
int		ft_putnbr(int n);
int		ft_putunbr(unsigned int n);
void	ft_convert_hexa(unsigned long nbr, int baselen, char *base, int *i);
int		ft_putnbr_hexa(unsigned int nbr);
int		ft_putnbr_uhexa(unsigned int nbr);
int		ft_printf(const char *str, ...);
void	ft_itop(int n);
void	ft_uitop(unsigned int n);
int		ft_check_args(char arg);
void	ft_init_f(int (**f)(void *));

#endif