/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:07:50 by mliboz            #+#    #+#             */
/*   Updated: 2021/12/12 14:35:35 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

int	main(int argc, char **argv)
{
	char	*str;
	int		i;

	i = 0;
	if (argc != 3)
		return (0);
	while (argv[2][i])
	{
		str = ft_itoa_base(argv[2][i], BASE2);
		if (ft_strlen(str) != 8)
			put_bytes(&str);
		send_signal(str, ft_atoi(argv[1]));
		free(str);
		i++;
	}
	send_signal("00000000", ft_atoi(argv[1]));
}
