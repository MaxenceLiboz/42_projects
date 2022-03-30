/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:23:16 by mliboz            #+#    #+#             */
/*   Updated: 2021/12/11 10:51:02 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_intlen(int n, int baselen)
{
	int		count;

	count = 0;
	while (n != 0)
	{
		count++;
		n /= baselen;
	}
	return (count);
}

static void	ft_recursive(int n, char *dst, int *i, char *base)
{
	int		baselen;

	baselen = ft_strlen(base);
	if (n != 0)
	{
		ft_recursive(n / baselen, dst, i, base);
	}
	if (n < 0)
	{
		dst[*i] = base[-(n % baselen)];
		*i += 1;
	}
	else if (n > 0)
	{
		dst[*i] = base[(n % baselen)];
		*i += 1;
	}
}

char	*ft_itoa_base(int n, char *base)
{
	char	*dst;
	int		nlen;
	int		neg;
	int		i;

	neg = 0;
	i = 0;
	if (n == 0)
		return (ft_strdup("0"));
	nlen = ft_intlen(n, ft_strlen(base)) + 1;
	if (n < 0)
		neg = +1;
	dst = malloc(sizeof(char) * (nlen + neg));
	if (!dst)
		return (0);
	if (n < 0)
	{
		dst[0] = '-';
		i = 1;
	}
	ft_recursive(n, dst, &i, base);
	dst[i] = 0;
	return (dst);
}
