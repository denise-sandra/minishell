/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inside_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/05/27 14:45:41 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_quotetype analyse_node(t_lst_token *node, int len, t_quotetype prev_type)
{
    // revisar los pipe y dir
    if (prev_type == OPEN_D_QUOTES && ft_strchr_int(node->value, '$') == 1)
        node->type = ENV;
    else if (prev_type == OPEN_D_QUOTES || prev_type == OPEN_S_QUOTES)
        node->type = TEXT;
    else if (prev_type == OTHER && len == 2 && node->value[0] == 39)
        node->type = OPEN_S_QUOTES;
    else if (prev_type == OTHER && len == 2 && node->value[0] == 34)
        node->type = OPEN_D_QUOTES;
    else if ((prev_type == ENV || prev_type == TEXT) && len == 2 && node->value[0] == 34)
        node->type = CLOSE_D_QUOTES;
    else if (prev_type == TEXT && len == 2 && node->value[0] == 39)
        node->type = CLOSE_S_QUOTES;
    else if (len == 2 && node->value[0] == '|')
        node->type = PIPE;
    else if (node->value[0] == '>')
        node->type = REDIR_IN;
     else if (node->value[0] == '<')
        node->type = REDIR_OUT;
    return (node->type);     
}

static t_lst_token **create_node(t_minishell *minishell, char *str, \
    int i, t_lst_token **split_token)
{
    char    *split_str;
    t_lst_token *node;
    static int prev_type = 0;
    
    split_str = malloc((i + 1) * sizeof(char));
    if (split_str == NULL)
    {
        ft_lstclear_t(split_token, free);
        ft_error("Malloc in create_node", minishell);
    }
    ft_strlcpy(split_str, str, i + 1);
    node = ft_lstnew_t(split_str);
    if (node == NULL)
    {
        ft_lstclear_t(split_token, free);
        ft_error("Malloc in create_node", minishell);
    }
    prev_type = analyse_node(node, ft_strlen(node->value), prev_type);
    ft_add_back_t(split_token, node);
}

static t_lst_token    **split_token_in_nodes(t_minishell *minishell, char *str, int len)
{
    t_lst_token    **split_token;
    int i;
    
    split_token = malloc(sizeof(t_lst_token*));
    if (split_token)
        ft_error("Malloc in copy_inside_q", minishell);
    while (*str)
    {
        i = 0;
        if (str[0] == 34 || str[0] == 39 || \
            str[0] == '|' || str[0] == '>' || str[0] == '<')
        {
            while (str[i] == str[0])
                i++;
        }
        else
        {
            while (str[i] && str[i] != 39 && str[i] != 34 && str[i] != '|' \
                && str[i] != '>' && str[i] != '<')
                i++;
        }
        split_token = create_node(minishell, str, i, split_token);
        str = str + i;
    }
    return (split_token);
}
