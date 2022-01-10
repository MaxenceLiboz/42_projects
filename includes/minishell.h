/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:37:52 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/10 12:54:53 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <libft.h>
# include <readline/readline.h>
# include <readline/history.h>

#define TEST_PS(expectation, ft) printf("Expected:\t\e[0;34m%s\e[0m\nGot:\t\t\e[0;34m", expectation); ft; printf("\e[0m\n");
#define TEST_S(expectation, str) ft_strncmp(expectation, str, ft_strlen(expectation) + 1) == 0 ? printf("\e[0;32mOK\e[0m\n") : printf("\e[0;31mFALSE\e[0m\nExpected:\t\e[0;34m%s\e[0m\nGot:\t\t\e[0;34m%s\e[0m\n\n", expectation, str);
#define TEST_I(expectation, int) expectation == int ? printf("\e[0;32mOK\e[0m\n") : printf("\e[0;31mFALSE\e[0m\nExpected:\t\e[0;34m%d\e[0m\nGot:\t\t\e[0;34m%d\e[0m\n\n", expectation, int);

# define BLUE "\033[0;34m"
# define END_COLOR "\033[0m"
# define TRUE 1
# define FALSE 0

typedef int	t_bool;

/**************** String  ****************/
typedef struct s_string
{
	char	*str;
	int		size;
	int		max_size;
}	t_string;

void		init_string(t_string *string, char *src, t_bool to_malloc);
void		reinit_string(t_string *string);
void		cat_string(t_string *string, t_string cat);
void		add_string_str(t_string *string, char *src, int index);
void		replace_string(t_string *string, int index, char *replace_with,
				int rindex);
void		sub_string(t_string *string, int start, int end, char *src);

/**************** Array string ********/
typedef struct s_array_string
{
	t_string	*array;
	t_string	command;
	int			size;
	int			max_size;
}	t_array_string;

void		init_array_string(t_array_string *array_string,
				int size, int to_malloc);
void		reinit_array_string(t_array_string *array);
/**************** OPTIONAL ****************/
char		**ft_free(char **str);

/**************** Built in ********/
int			exec_builtin(char **str);

/**************** Parsing ******************/
t_string	create_prompt(char *str);
int			create_command(t_array_string *command);
void		split_wog(t_array_string *command, char c);
int			count_split_wog(const char *str, char charset);

#endif