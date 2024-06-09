/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:03:59 by skanna            #+#    #+#             */
/*   Updated: 2024/06/09 16:00:32 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_var(t_mini *mini, t_pretok **cur, t_token **list)
{
	char	*env_name;
	char	*env_value;

	*cur = (*cur)->next;
	if (!(*cur) || (*cur)->type != ENV)
	{
		if (tok_list("$", TEXT, list) != 0)
			return (ft_error("Memory allocation error", mini));
		return ;
	}
	env_name = NULL;
	while (*cur && (*cur)->type == ENV)
	{
		env_name = ft_strjoin_char(env_name, (*cur)->c);
		if (!env_name)
			return (ft_error("Memory allocation error", mini));
		*cur = (*cur)->next;
	}
	env_value = get_env_value(mini->env, env_name);
	free(env_name);
	if (!env_value)
		return (ft_error("Memory allocation error", mini));
	if (tok_list(env_value, ENV, list) != 0)
		return (free(env_value), ft_error("Memory allocation error", mini));
	free(env_value);
}

static void	last_quotes(t_mini *mini, t_pretok **cur, t_token **lst, t_type q)
{
	char	*str;

	str = NULL;
	*cur = (*cur)->next;
	while (*cur && (*cur)->type != q)
	{
		if ((*cur)->type == EXP)
			expand_var(mini, cur, lst);
		else
		{
			str = ft_strjoin_char(str, (*cur)->c);
			if (!str)
				return (ft_error("Memory allocation error", mini));
			*cur = (*cur)->next;
		}
	}
	if (*cur && (*cur)->type == q)
		*cur = (*cur)->next;
	if (str)
	{
		if (tok_list(str, TEXT, lst) != 0)
			return (free(str), ft_error("Memory allocation error", mini));
		free(str);
	}
}

static void	pipes_and_opts(t_mini *mini, t_pretok **cur, t_token **list)
{
	if ((*cur)->type == PIPE)
	{
		if (!(*cur)->next)
			return (ft_error("Syntax error near unexpected token `|'", mini));
		if (tok_list("|", PIPE, list) != 0)
			return (ft_error("Memory allocation error", mini));
	}
	else
	{
		if ((*cur)->next && (*cur)->next->type == OPT)
		{
			if (tok_list("--", OPT, list) != 0)
				return (ft_error("Memory allocation error", mini));
		}
		else
		{
			if (tok_list("-", OPT, list) != 0)
				return (ft_error("Memory allocation error", mini));
		}
	}
	*cur = (*cur)->next;
}

static void	chars_and_empty(t_mini *mini, t_pretok **cur, t_token **list)
{
	char	*join;

	join = NULL;
	while (*cur && ((*cur)->type == CHAR || (*cur)->type == EMPTY))
	{
		if ((*cur)->type == CHAR)
		{
			join = ft_strjoin_char(join, (*cur)->c);
			if (!join)
				return (ft_error("Memory allocation error", mini));
		}
		else if ((*cur)->type == EMPTY)
		{
			if (tok_list("", EMPTY, list) != 0)
				return (ft_error("Memory allocation error", mini));
		}
		*cur = (*cur)->next;
	}
	if (join)
	{
		if (tok_list(join, TEXT, list) != 0)
			return (free(join), ft_error("Memory allocation error", mini));
		free(join);
	}
}

void parser(t_mini *mini)
{
	t_pretok	*cur_pretok;

	cur_pretok = mini->pretok;
	while (cur_pretok)
	{
		if (cur_pretok->type == CHAR || cur_pretok->type == EMPTY)
			chars_and_empty(mini, &cur_pretok, &(mini->token));
		else if (cur_pretok->type == PIPE || cur_pretok->type == OPT)
			pipes_and_opts(mini, &cur_pretok, &(mini->token));
		else if (cur_pretok->type == IN || cur_pretok->type == OUT)
			parse_redirs(mini, &cur_pretok, &(mini->token));
		else if (cur_pretok->type == EXP)
			expand_var(mini, &cur_pretok, &(mini->token));
		else if (cur_pretok->type == D_Q || cur_pretok->type == S_Q)
			last_quotes(mini, &cur_pretok, &(mini->token), cur_pretok->type);
		else
			cur_pretok = cur_pretok->next;
		if (mini->error != 0)
			return ;
	}
	clean_pretokens(mini);
	parse_commands(mini); //para despues, tener en cuenta que esto puede hacer un return despues de un error
	t_token *print = mini->token;
	printf ("tok list: %p \n", mini->token);
	while (print)
	{
		printf("new: %s  type: %i\n", print->value, print->type);
		if (print->type == COMMAND)
		{
			for (int i = 0; print->cmd_tab[i]; i++)
				printf("cmd: %s\n", print->cmd_tab[i]);
		}
		print = print->next;
	}
	// check_syntax_erros(mini);
}
