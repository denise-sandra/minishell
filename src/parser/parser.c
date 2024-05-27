/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/05/27 18:52:17 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lst_token **fill_new_token(t_minishell *minishell, t_lst_token **split_token)
{
	t_lst_token	*tmp;
	char		*env_value;

	tmp = *split_token;
	env_value = NULL;
	while (tmp)
	{
		if (tmp->type == ENV)
		{
			env_value = get_env_value(minishell->env, tmp->value);
			if (env_value)
			{
				free(tmp->value);
				tmp->value = ft_strdup(env_value);
				if (!tmp->value)
					ft_error("can't duplicate env value\n", minishell);
			}
		}
		tmp = tmp->next;
	}
	return (split_token);

}

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
		if (env_var > 0)
		{
			fill_new_token(minishell, split_token);
			// minishell->token[i]->value = replace_env_value(minishell, split_token, env_var);
		}
		printf("parser: %s\n", minishell->token[i]->value);
		i++;
	}
	tag_token(minishell);
}