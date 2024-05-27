/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/05/27 14:08:51 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_minishell *minishell)
{
	t_lst_token    **split_token;
	char	*value;
	int		env_var;
	int		i;

	i = 0;
	while (i < minishell->token_count)
	{
		value = minishell->token[i]->value;
		minishell->token[i]->value = erase_extra_quotes(value, ft_strlen(value));
		value = minishell->token[i]->value;
		split_token = split_token_in_nodes(minishell, value, ft_strlen(value));
		if (value == NULL)
			ft_error("Malloc in erase_extra_quotes", minishell);
		env_var = count_env_var(split_token);
		printf("env_var: %d \n", env_var);
		if ( env_var > 0)
			minishell->token[i]->value = replace_env_value(minishell, split_token, env_var);	
		printf("parser: %s\n",minishell->token[i]->value );
		i++;
	}
	tag_token(minishell);
}