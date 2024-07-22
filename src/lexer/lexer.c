/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deniseerjavec <deniseerjavec@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/09 14:34:57 by deniseerjav      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_basic_errors(t_mini *mini)
{
	t_pretok	*list1;

	list1 = mini->pretok;
	while (list1)
	{
		if (list1->type == ERROR)
			return (1);
		list1 = list1->next;
	}
	return (0);
}

static int	pre_tag(char c)
{
	if (c == 32)
		return (WHITE);
	if (c == 34)
		return (D_Q);
	if (c == 39)
		return (S_Q);
	if (c == '/')
		return (SLASH);
	if (c == 45)
		return (OPT);
	if (c == 60)
		return (IN);
	if (c == 62)
		return (OUT);
	if (c == 124)
		return (PIPE);
	if (c == 38 || c == 40 || c == 41 || c == 59 || c == 92)
		return (ERROR);
	return (CHAR);
}

static int	create_pretokens_list(char *input, t_mini *mini)
{
	t_pretok	*current;
	t_pretok	*new_node;
	int			i;

	mini->pretok = NULL;
	current = NULL;
	i = 0;
	while (input[i])
	{
		new_node = malloc(sizeof(t_pretok));
		if (!new_node)
			return (ft_error(mini, NULL, strerror(errno)), 1);
		new_node->c = input[i];
		new_node->type = pre_tag(input[i]);
		new_node->next = NULL;
		if (mini->pretok == NULL)
			mini->pretok = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (0);
}

void	remove_extra_empty(t_mini *mini)
{
	t_pretok	*cur;
	t_pretok	*next;

	cur = mini->pretok;
	while (cur)
	{
		next = cur->next;
		if ((cur->type != WHITE || (cur->next->next && cur->next->next->type != WHITE)) \
			&& next && next->type == EMPTY)
		{
			cur->next = next->next;
			free(next);
		}
		else
			cur = cur->next;
	}
}

void	lexer(char *input, t_mini *mini)
{
	if (create_pretokens_list(input, mini) != 0)
		return ;
	tag_in_quotes(mini, NULL);
	if (mini->error != 0)
		return ;
	remove_spaces(mini);
	if (check_basic_errors(mini) != 0)
	{
		ft_error(mini, "Syntaxis error: special character not supported", NULL);
		return ;
	}
	remove_extra_empty(mini);
	// t_pretok *print = mini->pretok;
	// while (print)
	// {
	// 	printf("pretok val: %c  type: %i\n", print->c, print->type);
	// 	print = print->next;
	// }
}
