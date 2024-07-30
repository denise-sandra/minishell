/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:16 by skanna            #+#    #+#             */
/*   Updated: 2024/07/29 17:48:05 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst_env	*copy_list(t_lst_env *lst)
{
	t_lst_env	*new;
	t_lst_env	*new_lst;

	new_lst = NULL;
	while (lst)
	{
		new = ft_lstnew_env(lst->name, lst->value);
		if (!new)
			return (NULL);
		ft_lstadd_back_env(&new_lst, new);
		lst = lst->next;
	}
	return (new_lst);
}

int	handle_shlvl(t_mini *mini)
{
	char	*shlvl;
	char	*shlvl_join;
	int		lvl;

	shlvl = get_env_value(mini->env, "SHLVL");
	if (!shlvl)
		return (1);
	lvl = ft_atoi(shlvl);
	free (shlvl);
	lvl++;
	shlvl = ft_itoa(lvl);
	if (!shlvl)
		return (1);
	shlvl_join = ft_strjoin("SHLVL=", shlvl);
	free (shlvl);
	if (!shlvl_join)
		return (1);
	if (add_env(mini, shlvl_join) != 0)
		return (1);
	free (shlvl_join);
	free_tab(mini->env_char);
	mini->env_char = list_to_tab(mini);
	if (mini->env_char == NULL)
		return (1);
	return (0);
}
