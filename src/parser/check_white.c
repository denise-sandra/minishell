/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_white.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:03:59 by skanna            #+#    #+#             */
/*   Updated: 2024/07/06 16:21:16 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void join_tok(t_mini *mini, t_token **tmp, t_token **prev)
{
    char	*new_token;
    t_token	*new;
    
    new_token = ft_strjoin_free((*tmp)->value, (*tmp)->next->value);
    if (!new_token)
        return (ft_error(mini, NULL, strerror(errno)));
    new = tok_new_node(new_token, STRING);
    free(new_token);
    if (!new)
        return (ft_error(mini, NULL, strerror(errno)));
    new->next = (*tmp)->next->next;
    free((*tmp)->next);
    free(*tmp);
    *tmp = new;
    if (*prev)
        (*prev)->next = new;
    else
        mini->token = new;
}


static void erase_white_tok(t_mini *mini, t_token **tmp, t_token **prev)
{
    if (*prev)
    {
        (*prev)->next = (*tmp)->next;
        free((*tmp)->value);
        free(*tmp);
        *tmp = (*prev)->next;
    }
    else
    {
        mini->token = (*tmp)->next;
        free((*tmp)->value);
        free(*tmp);
        *tmp = mini->token;
    }
}

int check_white(t_mini *mini)
{
	t_token *tmp;
	t_token *prev;
	
	tmp = mini->token;
	prev = NULL;
	while (tmp)
	{
		if ((tmp->type == STRING || tmp->type == D_Q || tmp->type == S_Q)
			&& tmp->next && (tmp->next->type == STRING || \
			tmp->next->type == D_Q || tmp->next->type == S_Q))
            join_tok(mini, &tmp, &prev);
		else if (tmp->type == WHITE)
            erase_white_tok(mini, &tmp, &prev);
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
        if (mini->error != 0)
            return (1) ;
	}
    return (0);
}
