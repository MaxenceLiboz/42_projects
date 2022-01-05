/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:37:52 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/05 09:27:27 by mliboz           ###   ########.fr       */
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

char	*create_prompt(char *color, char *str);
int		exec_builtin(char **str);

#endif