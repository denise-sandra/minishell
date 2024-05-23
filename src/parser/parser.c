/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/05/23 16:14:06 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_minishell *minishell)
{
	char	*value;
	int		*quotes;
	int		env_var;
	int		i;

	i = 0;
	while (i < minishell->token_count)
	{
		value = minishell->token[i]->value;
		quotes = check_quotes(value);
		env_var = count_env_var(value);
		printf("env_var: %d %s\n", env_var, value );
		if ( env_var > 0)
		{
			minishell->token[i]->value = replace_env_value(minishell, value, env_var);
		}		
		else if (quotes[0] == 0 || quotes[1] == 0)
			minishell->token[i]->value = erase_all_quotes(value);
		else if (quotes[0] > 0 && quotes[1] > 0)
			minishell->token[i]->value = erase_outer_quotes(value);
		free(quotes);
		printf("parser: %s\n",minishell->token[i]->value );
		i++;
	}
	tag_token(minishell);
}