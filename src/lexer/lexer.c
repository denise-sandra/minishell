/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/07 15:45:50 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_basic_errors(t_minishell *mini)
{
	t_pretok	*list1;
	t_pretok	*list2;

	list1 = mini->pretok; 
	list2 = mini->pretok;
	while (list1)
	{
		if (list1->type == ERROR)
			return (1);
		list1 = list1->next;
	}
	// while (list2)
	// {
	// 	if (list2->type != PIPE)
	// 		list2 = list2->next;
	// 	else
	// 	{
	// 		if (list2->next && list2->next->type == PIPE)
	// 			return (1);
	// 	}
	// }
	return (0);
}

static void	tag_env_variables(t_pretok *start)
{
	t_pretok	*current;

	current = start;
	while (current)
	{
		if (current->type == EXP)
		{
			current = current->next;
			while (current && current->type == CHAR)
			{
				current->type = ENV;
				current = current->next;
			}
		}
		else
			current = current->next;
	}
}

static int	pre_tag(char c)
{
	if (c == 32)
		return (WHITE);
	if (c == 34)
		return (D_Q);
	if (c == 36 || c == 61)
		return (EXP);
	if (c == 39)
		return (S_Q);
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

static int	create_pretokens_list(char *input, t_minishell *mini)
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
			return (1);
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

void	lexer(char *input, t_minishell *mini)
{
	if (create_pretokens_list(input, mini) != 0)
	{
		ft_error("Memory allocation error", mini);
		return ;
	}
	// t_pretok *print = mini->pretok;
	// while (print)
	// {
	// 	printf("before pretok val: %c  type: %i\n", print->c, print->type);
	// 	print = print->next;
	// }
	parse_quotes(mini, NULL);
	tag_env_variables(mini->pretok);
	remove_spaces(mini);
	if (check_basic_errors(mini) != 0)
	{
		ft_error("Syntaxis error: special character not supported", mini);
		return ;
	}
	t_pretok *print = mini->pretok;
	while (print)
	{
		printf("pretok val: %c  type: %i\n", print->c, print->type);
		print = print->next;
	}
}
