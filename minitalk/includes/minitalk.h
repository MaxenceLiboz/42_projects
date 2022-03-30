/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:58:56 by mliboz            #+#    #+#             */
/*   Updated: 2021/12/12 14:35:49 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <libft.h>
# include <stdio.h>
# include <signal.h>
# define BASE2 "01"
# define BASE10 "0123456789"

char	*ft_itoa_base(int n, char *base);
void	sighandler(int signum);
void	put_bytes(char **str);
void	send_signal(char *str, int pid);

#endif