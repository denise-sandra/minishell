/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:37:04 by skanna            #+#    #+#             */
/*   Updated: 2024/03/15 11:13:44 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftv3.h"

static char	**fill_args(char **split, char const *s, size_t args, char c)
{
	size_t	h;
	size_t	len_args;

	h = 0;
	while (s && h < args)
	{
		len_args = 0;
		while (*s == c)
			s++;
		while (*s != '\0' && *s != c)
		{
			len_args++;
			s++;
		}
		split[h] = ft_substr((s - len_args), 0, len_args);
		if (!split[h])
		{
			free_split(split, h);
			return (NULL);
		}
		h++;
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	size_t	args;
	char	**split;

	if (!s)
		return (NULL);
	args = arg_count(s, c);
	split = malloc ((args + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split[args] = 0;
	split = fill_args(split, s, args, c);
	return (split);
}

static char	**fill_args_quotes(char **split, char const *s, size_t args, char c)
{
	size_t	h;
	size_t	len_args;

	h = 0;
	while (s && h < args)
	{
		len_args = 0;
		while (*s == c)
			s++;
		len_args = arg_len_quotes(s, c);
		if (*s == 34 || *s == 39)
		{
			s++;
			len_args -= 2;
		}
		split[h] = ft_substr(s, 0, len_args);
		if (!split[h])
			return (free_tab(split), NULL);
		s += len_args;
		h++;
	}
	return (split);
}

char	**split_quotes(char const *s, char c)
{
	size_t	args;
	char	**split;
	int		valid_quotes;

	if (!s)
		return (NULL);
	valid_quotes = has_quotes(s);
	if (valid_quotes < 0)
		return (NULL);
	args = arg_count_quotes(s, c, valid_quotes);
	split = malloc ((args + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split[args] = 0;
	split = fill_args_quotes(split, s, args, c);
	return (split);
}

/*
#include <stdio.h>
int main(void)
{
	char *s = "sed    's/And/But/'";
	char c = 32;
	char **split;
	int	i;

	i = 0;
	printf("ft_split\n");
	printf("String to be copied: %s\n", s);
	split = ft_split(s, c);
	while (split[i])
	{
		printf("String %d: |%s|\n", i, split[i]);
		free (split[i]);
		i++;
		printf("\n");
	}
	free (split);
	printf("\n");
	return(0);
}*/