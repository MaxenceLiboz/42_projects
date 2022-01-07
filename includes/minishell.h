/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:37:52 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/07 16:07:54 by mliboz           ###   ########.fr       */
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

typedef int t_bool;

typedef struct s_string
{
	char	*str;
	int		size;
	int		max_size;
}	t_string;

typedef struct s_array_string
{
	t_string	*array;
	t_string	command;
	int			size;
	int			max_size;
}	t_array_string;

typedef struct s_env
{
	t_string		name_var;
	t_string		var;
	struct s_env	*next;
}	t_env;

typedef struct s_env_head
{
	struct s_env	*first;
	int				size;
}	t_env_head;

char		*create_prompt(char *color, char *str);
int			exec_builtin(char **str);
int			create_command(t_array_string *command);
void		split_wog(t_array_string *command, char c);
int			count_split_wog(const char *str, char charset);

/**************** OPTIONAL ****************/
void		freestr(char *str);
char		**ft_free(char **str);

/**************** struct functions ********/
void		init_array_string(t_array_string *array_string,
				int size, int to_malloc);
void		init_string(t_string *array, int size, t_bool to_malloc);
void		cat_string(t_string *string, t_string cat);
void		add_string_str(t_string *string, char *src, int index);

#endif