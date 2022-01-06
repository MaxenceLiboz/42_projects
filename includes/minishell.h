/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:37:52 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/06 13:00:04 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <libft.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BLUE "\033[0;34m"
# define END_COLOR "\033[0m"

typedef struct s_string
{
	char	*str;
	int		size;
	int		max_size;
}	t_string;

typedef struct s_array_string
{
	void	*t_string;
	int		size;
	int		max_size;
}	t_array_string;

char	*create_prompt(char *color, char *str);
int		exec_builtin(char **str);
void	freestr(char *str);

#endif