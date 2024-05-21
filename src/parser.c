/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/05/21 16:34:49 by deniseerjav      ###   ########.fr       */
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
		printf("env cuenta : %d\n", env_var);
		if ( env_var > 0)
		{
			token[i]->value = replace_env_value(minishell, token[i]->value, env_var);
			printf("env final : %s\n", token[i]->value);
		}		
		else if (quotes[0] == 0 || quotes[1] == 0)
			token[i]->value = erase_all_quotes(token[i]->value);
		else if(quotes[0] > 0 && quotes[1] > 0)
			token[i]->value = erase_outer_quotes(token[i]->value);
		printf("parser : %s\n",token[i]->value);
		free(quotes);
		i++;
	}
	tag_token(minishell);
}