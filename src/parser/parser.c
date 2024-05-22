/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/05/22 15:22:58 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_minishell *minishell)
{
	t_token	**token;
	int		*quotes;
	int		env_var;
	int		i;

	token = minishell->token;
	i = 0;
	while (i < minishell->token_count)
	{
		quotes = check_quotes(token[i]->value);
		env_var = count_env_var(minishell, token[i]->value);
		printf("env_var: %d %s\n", env_var,token[i]->value );
		if ( env_var > 0)
		{
			token[i]->value = replace_env_value(minishell, \
			token[i]->value, env_var);
		}		
		else if (quotes[0] == 0 || quotes[1] == 0)
			token[i]->value = erase_all_quotes(token[i]->value);
		else if (quotes[0] > 0 && quotes[1] > 0)
			token[i]->value = erase_outer_quotes(token[i]->value);
		free(quotes);
		printf("parser: %s\n",minishell->token[i]->value );
		i++;
	}
	tag_token(minishell);
}