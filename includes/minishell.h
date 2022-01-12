/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:37:52 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/12 16:45:10 by tarchimb         ###   ########.fr       */
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
void		dup_string(t_string *string, char *src, int index);
void		replace_string(t_string *string, int index, char *replace_with,
				size_t rsize);
void		sub_string(t_string *string, char *src, size_t start, size_t size);
void		erase_string(t_string *string, char *to_replace, size_t start);
void		add_string(t_string *string, char *to_add, size_t index);

/**************** Command ********/
typedef struct s_command
{
	t_string	*array;
	t_string	command;
	int			index;
	int			size;
	int			max_size;
}	t_command;

void		init_command(t_command *array_string,
				int size, int to_malloc);
void		reinit_command(t_command *array);

/**************** ENV ********************/
typedef struct s_lst_env
{
	t_string			name_var;
	t_string			var;
	struct s_lst_env	*next;
}	t_lst_env;

t_lst_env	*lst_env_new(char *name_var, char *var);
void		lst_env_add_back(t_lst_env **lst, t_lst_env *new);
void		lst_env_add_front(t_lst_env **lst, t_lst_env *new);
int			lst_env_clear(t_lst_env **lst);
void		lst_env_delone(t_lst_env *prev);
t_lst_env	*lst_env_last(t_lst_env *lst);
int			lst_env_size(t_lst_env *lst);
void		lst_env_swap(t_lst_env **head, t_lst_env **next);
void		lst_env_sort(t_lst_env **env);
t_string	lst_env_find_name_var(t_lst_env *env, char *str);

typedef struct s_head_env
{
	t_lst_env			*env;
	t_lst_env			*export;
}	t_head_env;

/**************** OPTIONAL ****************/
char		**ft_free(char **str);

/**************** Built in ********/
int			exec_builtin(char **str);
void		ft_export(t_head_env *head, char **command);
int			control_args(char *str);

/**************** Parsing ******************/
t_string	create_prompt(char *str);
int			create_command(t_command *command, t_head_env *envi);
void		split_wog(t_command *command, char c);
int			count_split_wog(const char *str, char charset);

int			set_export(char **envp, t_head_env *head);

#endif