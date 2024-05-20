/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/05/20 12:56:12 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*erase_special_c(char *word)
{
	int	i;
	int	j;
	int	q;
	char	*new_word;

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
	i = 0;
	j = 0;
	while (word[j])
	{
		if (word[j] != 34 & word[j] != 39)
		{
			new_word[i] = word[j];
			i++;
		}
		j++;		
	} 
	free(word);
	return (new_word);
}

void	parser(t_minishell *minishell)
{
	t_token **token;
	int	i;
	
	printf("tokens: %d\n",minishell->token_count );
	token = minishell->token;
	i = 0;
	while (i < minishell->token_count)
	{
		printf("parser : %s\n",token[i]->value);
		token[i]->value = erase_special_c(token[i]->value);
		printf("parser : %s\n",token[i]->value);
		i++;
	}
}