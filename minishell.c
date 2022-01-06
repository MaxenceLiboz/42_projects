/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:02:00 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/06 15:23:41 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*pwd(char **str)
{
	char	*dst;

	if (!str || strncmp(str[0], "pwd", 4) != 0)
		return (NULL);
	if (str[1] != NULL && *str[1])
		if (str[1] != 0 && strncmp(str[1], "|", 2) != 0)
			return (NULL);
	dst = NULL;
	dst = getcwd(dst, 0);
	if (!dst)
		return (NULL);
	return (dst);
}

static int	ft_count_words(const char *str, char charset)
{
	int		i;
	int		count;
	int		quotes;

	count = 0;
	i = 0;
	quotes = 1;
	while (str[i] && str[i] == charset)
		i++;
	if (str[i] != 0)
		count++;
	while (str[i])
	{
		if (str[i] == '"')
			quotes *= -1;
		if (str[i] == charset
			&& (str[i + 1] != charset && str[i + 1] != 0) && quotes > 0)
			count++;
		i++;
	}
	return (count);
}

static void	get_copy_size(const char *src, char c, int *i, int *end)
{
	static int	quotes = 1;

	if (quotes > 0)
	{
		while (src[*i] == c)
			*i += 1;
	}
	*end = *i;
	while ((src[*end] != c || quotes < 1) && src[*end] && src[*end])
	{
		if (src[*end] == '"')
			quotes *= -1;
		*end += 1;
	}
}

static char	*ft_copy(const char *src, char c, int *i)
{
	int			end;
	char		*dst;
	int			size;
	int			y;

	y = 0;
	get_copy_size(src, c, i, &end);
	size = end - *i;
	dst = malloc(sizeof(char) * (size + 1));
	if (!dst)
		exit(-1);
	while (*i < end)
	{
		if (src[*i] == '"')
			*i += 1;
		if (*i >= end)
			break ;
		dst[y++] = src[*i];
		*i += 1;
	}
	dst[y] = 0;
	*i = end;
	return (dst);
}

static char	**ft_free(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	exit(-1);
}

char	**ft_split_wog(char const *s, char c)
{
	char	**dst;
	int		words;
	int		i;
	int		dsti;

	if (!s)
		return (0);
	i = 0;
	dsti = 0;
	words = ft_count_words(s, c);
	dst = malloc(sizeof(char *) * (words + 1));
	if (!dst)
		exit (-1);
	while (words--)
	{
		dst[dsti] = ft_copy(s, c, &i);
		if (!dst[dsti])
			return (ft_free(dst));
		dsti++;
	}
	dst[dsti] = 0;
	return (dst);
}

void	create_command(char *str, char ***command)
{

	if (!str)
		return ;
	*command = malloc(sizeof(t_string) * ft_count_words(str, ' '));
	if (!*command)
		exit(-1);
	*command = ft_split_wog(str, ' ');
}

int	main(void)
{
	char		*cwd;
	char		*prompt;
	char		*pdw;
	char		*get;
	char		**command;

	pdw = ft_strdup("pwd");
	while (1)
	{
		cwd = pwd(&pdw);
		prompt = create_prompt(BLUE, cwd);
		if (!prompt)
			return (0);
		get = readline(prompt);
		create_command(get, &command);
		for (int i = 0; command[i]; i++)
			printf("%s\n", command[i]);
		freestr(get);
		freestr(prompt);
		freestr(cwd);
	}
	freestr(pdw);
	return (0);
	// int	i = 0;
	// printf("%s\n", ft_copy("\"E\"cho test \"1 22 34       4\"", ' ', &i));
	// printf("%s\n", ft_copy("\"E\"cho test \"1 22 34       4\"", ' ', &i));
	// printf("%s\n", ft_copy("\"E\"cho test \"1 22 34       4\"", ' ', &i));
}
