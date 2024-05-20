/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/05/20 17:15:01 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_minishell *minishell)
{
	t_token	**token;
	int		*quotes;
	int		i;

	token = minishell->token;
	i = 0;
	while (i < minishell->token_count)
	{
		quotes = check_quotes(token[i]->value);
		if (quotes[0] == 0 || quotes[1] == 0)
			token[i]->value = erase_all_quotes(token[i]->value);
		else if(quotes[0] > 0 && quotes[1] > 0)
			token[i]->value = erase_outer_quotes(token[i]->value);
		printf("parser : %s\n",token[i]->value);
		free(quotes);
		i++;
	}
}