/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 10:47:50 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/07 16:23:20 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_command(t_array_string *command)
{
	int		squotes;
	int		dquotes;
	int		i;

	squotes = 0;
	dquotes = 0;
	i = 0;
	while (command->command.str[i])
	{
		if (command->command.str[i] == '\"')
			dquotes += 1;
		if (command->command.str[i] == '\'')
			squotes += 1;
		i++;
	}
	if (squotes % 2 != 0 && dquotes % 2 != 0)
		printf("Missing both: \" and \'\n");
	else if (squotes % 2 != 0)
		printf("Missing: \'\n");
	else if (dquotes % 2 != 0)
		printf("Missing: \"\n");
	if (squotes % 2 != 0 || dquotes % 2 != 0)
		return (0);
	return (1);
}

void	realloc_string(t_string *string)
{
	t_string	dst;

	init_string(&dst, string->size, TRUE);
	add_string_str(&dst, string->str, 0);
	freestr(string->str);
	init_string(string, string->max_size * 2, TRUE);
	add_string_str(string, dst.str, 0);
	freestr(dst.str);
}

void	add_string_str(t_string *string, char *src, int index)
{
	int		i;

	i = 0;
	if (string->max_size < ((string->size - index) + ft_strlen(src) + 2))
		realloc_string(string);
	printf("%d, %d\n", string->max_size, ((string->size - index) + ft_strlen(src) + 1));
	while (src[i])
		string->str[index++] = src[i++];
	string->str[index] = 0;
	string->size = ft_strlen(string->str);
}

// void	replace_string(t_string *string, char *gotta_replace,
// 			int index, t_env env)
// {
// 	int			size;
// 	t_string	dst;
// 	t_string	arg;
// 	t_string	save;

// 	// arg = find_and_get(env, gotta_replace);
// 	size = ft_strlen(gotta_replace);
// 	init_string(&save, string->size - (index + size), TRUE);
// 	copy_string_str(&save, &string->str[index]);


	
// 	freestr(save.str);
// }

// int	check_arg(t_array_string *command)
// {
// 	int		i;

// 	i = 1;
// 	if (command->command[i] == "$")
// 	while (command->command[i])
// 	{
// 		if (command->command[i] == "$" && command->command[i - 1] != "\'"
// 			&& i > 1)
// 			break;
// 	}
// }

int	create_command(t_array_string *command)
{
	if (!command->command.str)
		exit(-1);
	if (!check_command(command))
		return (0);
	// check_arg(command);
	split_wog(command, ' ');
	return (1);
}
