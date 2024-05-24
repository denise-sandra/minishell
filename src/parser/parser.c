/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/05/24 23:48:02 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_minishell *minishell)
{
	char	*value;
	int		env_var;
	int		i;

	i = 0;
	while (i < minishell->token_count)
	{
		value = minishell->token[i]->value;
		minishell->token[i]->value = erase_extra_quotes(value);
		value = minishell->token[i]->value;
		//minishell->token[i]->value = copy_inside_q(value);
		//value = minishell->token[i]->value;
		if (value == NULL)
			ft_error("Malloc in erase_extra_quotes", minishell);
		env_var = count_env_var(value);
		printf("env_var: %d %s\n", env_var,value);
		if ( env_var > 0)
			minishell->token[i]->value = replace_env_value(minishell, value, env_var);	
		printf("parser: %s\n",minishell->token[i]->value );
		i++;
	}
	tag_token(minishell);
}