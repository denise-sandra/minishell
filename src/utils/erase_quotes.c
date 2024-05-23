/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/05/23 16:21:42 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*erase_all_quotes_utils(char *word, char *new_word)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (word[j])
	{
		if (word[j] != 34 && word[j] != 39)
		{
			new_word[i] = word[j];
			i++;
		}
		j++;
	}
	new_word[i] = '\0';
	return (new_word);
}

char	*erase_all_quotes(char *word)
{
	char	*new_word;
	int		i;
	int		q;

	i = 0;
	q = 0;
	while (word[i])
	{
		if (word[i] == 34 || word[i] == 39)
			q++;		
		i++;
	}
	if (q == 0)
		return (word);
	new_word = malloc((ft_strlen(word) - q + 1) * sizeof(char));
	if (new_word == NULL)
		return (NULL);
	new_word = erase_all_quotes_utils(word, new_word);
	free(word);
	return (new_word);
}

static char	*erase_outer_quotes_utils(char *word, char *new_word, int q_type)
{
	int	i;
	int	j;
	int	q;

	i = 0;
	j = 0;
	q = 0;
	while (word[i])
	{
		if (word[i] != q_type)
			new_word[j++] = word[i];
		i++;
	}
	new_word[j] = '\0';
	return (new_word);
}

char	*erase_outer_quotes(char *word)
{
	char	*new_word;
	int		q_type;
	int		r;
	int		l;

	if (word[0] != 34 && word[0] != 39)
		return (word);
	q_type = word[0];
	r = 0;
	while (word[r] == q_type)
		r++;
	l = ft_strlen(word);
	while (word[l - 1] == q_type)
		l--;
	new_word = malloc((l - r + 1) * sizeof(char));
	if (new_word == NULL)
		return (NULL);
	new_word = erase_outer_quotes_utils(word, new_word, q_type);
	free(word);
	return (new_word);
}

void	erase_quotes(t_minishell *minishell, int i)
{
	int *quotes;
	char	*value;

	value = minishell->token[i]->value;
	quotes = check_quotes(value);
	if (quotes == NULL)
		ft_error("malloc in check_quotes", minishell);
	if (quotes[0] == 0 || quotes[1] == 0)
		minishell->token[i]->value = erase_all_quotes(value);
	else if (quotes[0] > 0 && quotes[1] > 0)
		minishell->token[i]->value = erase_outer_quotes(value);
	if (minishell->token[i]->value == NULL)
	{
		free(quotes);
		ft_error("Malloc in erase_quotes", minishell);
	}	
	free(quotes);
}
