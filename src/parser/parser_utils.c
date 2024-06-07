/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:03:59 by skanna            #+#    #+#             */
/*   Updated: 2024/06/07 09:10:15 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_env_value(t_minishell *mini, char *env, char *s)
{
	env = get_env_value(mini->env, env);
	check_malloc_error(mini, env, "Malloc error", -1);
	s = ft_strjoin_free(s, env);
	check_malloc_error(mini, s, "Malloc error", -1);
	return (s);
}

static void	create_node_txt(t_minishell *mini, char *s, t_type prev)
{
	t_token	*new_node;

	new_node = tok_new_node(s, TEXT, prev);
	free(s);
	check_malloc_error(mini, new_node, "Malloc error", -1);
	tok_addback(&mini->token, new_node);
}

t_pretok	*opt_join(t_minishell *mini, t_pretok *lexer, t_type prev)
{
	char	*s;
	char	*env;

	s = NULL;
	while (lexer && lexer->type != WHITE)
	{
		env = NULL;
		if (lexer->type == EXP)
			lexer = lexer->next;
		while (lexer && lexer->type == ENV)
		{
			env = ft_strjoin_char(env, lexer->c);
			lexer = lexer->next;
		}
		if (env != NULL)
			s = replace_env_value(mini, env, s);
		else
		{
			s = ft_strjoin_char(s, lexer->c);
			check_malloc_error(mini, s, "Malloc error", -1);
			lexer = lexer->next;
		}
	}
	create_node_txt(mini, s, prev);
	return (lexer);
}

t_pretok	*type_join(t_minishell *mini, t_pretok *lexer, t_type prev)
{
	char	*s;
	char *env;

	s = NULL;
	while (lexer && (lexer->type == CHAR \
		|| lexer->type == ENV || lexer->type == EXP))
	{
		env = NULL;
		if (lexer->type == EXP)
			lexer = lexer->next;
		while (lexer && lexer->type == ENV)
		{
			env = ft_strjoin_char(env, lexer->c);
			lexer = lexer->next;
		}
		if (env != NULL)
			s = replace_env_value(mini, env, s);
		else
		{
			s = ft_strjoin_char(s, lexer->c);
			check_malloc_error(mini, s, "Malloc error", -1);
			lexer = lexer->next;
		}
	}
	create_node_txt(mini, s, prev);
	return (lexer);
}