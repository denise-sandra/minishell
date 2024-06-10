/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:47:03 by sandra            #+#    #+#             */
/*   Updated: 2024/06/10 15:21:18 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*fill_cmd_table(t_token *cur, t_token *new, t_minishell *mini)
{
	int	i;
     t_token *tmp;
     
	i = 0;
     printf("table -- type: %u \n", cur->type);
	while (cur && (cur->type == COMMAND || cur->type == BUILTIN \
          || cur->type == OPT || cur->type == ARG))
	{
		if (cur->type == EMPTY)
			new->tab[i] = ft_strdup("");
		else
			new->tab[i] = ft_strdup(cur->value);
		check_malloc_error(mini, new->tab,"Malloc in parser",  -1);
          printf("parse: %s\n", new->tab[i]);
          tmp = cur->next;
          free(cur->value);
         // free(cur);
          cur = tmp;
		i++;
	}
	new->tab[i] = NULL;
     new->next = cur;
     return (new);
     
}

static int     count_token(t_token	*cur)
{
     int  i;
     
      i = 0;
     while (cur)
     {
          if (cur->type == OPT || cur->type == ARG || cur->type == EMPTY)
          i++; 
          cur = cur->next;
     }
     return (i);
}

void	parse_commands(t_minishell *mini)
{
	t_token	*cur;
     t_token	*new;
     int       i;

	cur = mini->token;
	printf("----entered parse command ----\n");
     while (cur)
     {
          new = malloc(sizeof(t_token));
          check_malloc_error(mini, new,"Malloc in parse_command", -1);
          i = count_token(cur);
          new->tab = malloc((i + 2) * sizeof(char*));
          check_malloc_error(mini, new->tab, "Malloc in parse_command", -1);
          cur = fill_cmd_table(cur, new, mini);
          printf("newp: %p\n", new);
          cur = cur->next;
     }
}