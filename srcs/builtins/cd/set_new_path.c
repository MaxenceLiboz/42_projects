/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_new_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:20:48 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/17 10:23:55 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#define COPY_PATH 0
#define TRIM_LAST_DIR 1
#define NEXT_PATH 2

/*
	Parse the path / by / and return what you need to do:
	- COPY_PATH
	- TRIM_LAST_DIR
	- NEXT_PATH
*/
static int	get_to_do_new_path(char *str, int start, int *end, t_prg *prg)
{
	int			start_cpy;
	t_string	tmp;

	while (str[start] == '/')
		start += 1;
	start_cpy = start;
	*end = start;
	while (str[start_cpy] && str[start_cpy] != '/')
	{
		start_cpy++;
		*end += 1;
	}
	tmp = sub_string(str, start, *end - start, prg);
	if (ft_strncmp(tmp.str, "..", 3) == 0)
		return (TRIM_LAST_DIR);
	else if (ft_strncmp(tmp.str, ".", 2) == 0)
		return (NEXT_PATH);
	else
		return (COPY_PATH);
}

/*
	Trim path until next / starting from the end
*/
static void	trim_last_dir(t_string *path, t_prg *prg)
{
	int		i;

	i = path->size - 2;
	if (path->str[i] == '/')
		i--;
	while (path->str[i] && path->str[i] != '/')
		i--;
	*path = sub_string(path->str, 0, i, prg);
}

/*
	Create the new path:
	- COPY_PATH => copy until the next / into dest;
	- TRIM_LAST_DIR => call trim_last_dir();
	- else => pass to the next part of the path
*/
t_bool	set_new_path(char *str, t_string *path, t_prg *prg)
{
	int		start;
	int		to_do;
	int		end;

	start = 0;
	to_do = 0;
	end = 0;
	while (str[start])
	{
		to_do = get_to_do_new_path(str, start, &end, prg);
		if (to_do == COPY_PATH)
			add_string(path, sub_string(str, start, end - start, prg).str,
				path->size - 1, prg);
		if (to_do == TRIM_LAST_DIR)
			trim_last_dir(path, prg);
		start = end;
	}
	return (SUCCESS);
}
