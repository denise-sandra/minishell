/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/05/24 14:07:04 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*erase_all_quotes_utils(char *str, char *new_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] != 34 && str[j] != 39)
		{
			new_str[i] = str[j];
			i++;
		}
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*erase_all_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		quotes;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			quotes++;		
		i++;
	}
	if (quotes == 0)
		return (str);
	new_str = malloc((ft_strlen(str) - quotes + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	new_str = erase_all_quotes_utils(str, new_str);
	free(str);
	return (new_str);
}

char	*erase_outer_quotes(char *str)
{
	char	*new_str;
	int		new_size;
	
	if (str[0] != 34 && str[0] != 39)
		return (str);
	new_size = ft_strlen(str) - 2 + 1;
	new_str = malloc(new_size * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, str + 1, new_size);
	free(str);
	return (new_str);
}

void	erase_quotes(t_minishell *minishell, int i)
{
	int *quotes;
	char	*str;

	str = minishell->token[i]->value;
	quotes = check_quotes(str);
	if (quotes == NULL)
		ft_error("malloc in check_quotes", minishell);
	if (quotes[0] == 0 || quotes[1] == 0)
		minishell->token[i]->value = erase_all_quotes(str);
	else if (quotes[0] > 0 && quotes[1] > 0)
		minishell->token[i]->value = erase_outer_quotes(str);
	if (minishell->token[i]->value == NULL)
	{
		free(quotes);
		ft_error("Malloc in erase_quotes", minishell);
	}	
	free(quotes);
}
