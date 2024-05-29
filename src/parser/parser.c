/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:02:56 by skanna            #+#    #+#             */
/*   Updated: 2024/05/29 10:30:46 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lst_token **fill_new_token(t_minishell *minishell, t_lst_token **sub_token)
{
	t_lst_token	*tmp;
	char		*env_value;

	tmp = *sub_token;
	env_value = NULL;
	while (tmp)
	{
		if (tmp->sub_type == ENV)
		{
			env_value = get_env_value(minishell->env, tmp->value + 1);
			printf("ENV: name: %s value: %s\n", tmp->value + 1, env_value);
			free(tmp->value);
			tmp->value = ft_strdup(env_value);
			if (!tmp->value)
				ft_error("can't duplicate env value\n", minishell);
		}
		tmp = tmp->next;
	}
	return (sub_token);

}

void	parser(t_minishell *minishell)
{
	t_lst_token    *sub_token;
	t_token	*tmp;
	//int		env_var;

	tmp = minishell->token;
	while (tmp)
	{
		tmp->value = erase_extra_quotes(tmp->value, ft_strlen(tmp->value));
		printf("erase_extra_quotes: %s\n", tmp->value);
		sub_token = *sub_token_in_nodes(minishell, tmp->value);
		if (tmp->value == NULL)
			ft_error("Malloc in erase_extra_quotes", minishell);
		fill_new_token(minishell, &sub_token);
		tmp->sub_token = sub_token;
		printf("parser CHAR: %s\n", tmp->value);
		t_lst_token    *pnt;
		pnt = tmp->sub_token;
		while (pnt)
		{
			printf("list st: %s  subtype: %u\n", pnt->value, pnt->sub_type);
			pnt = pnt->next;
		}
		tmp = tmp->next;
	}
	tag_token(minishell);
}