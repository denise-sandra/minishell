/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var_to_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/08/08 12:18:30 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**add_with_null_value(t_mini *mini, char *new_var)
{
	int		n;
	char	**split;

	n = find_name(mini->export, new_var);
	if (n == 1)
		return (NULL);
	split = malloc(2 * sizeof(char *));
	if (!split)
		return (ft_error(mini, NULL, strerror(errno)), NULL);
	split[0] = ft_strdup(new_var);
	split[1] = NULL;
	if (!split[0])
		return (ft_error(mini, NULL, strerror(errno)), NULL);
	return (split);
}

static void	add_exp(t_mini *mini, char *new_var, char *res)
{
	char		**split_new_exp;
	t_lst_env	*new_node;

	if (res == NULL)
	{
		split_new_exp = add_with_null_value(mini, new_var);
		if (!split_new_exp)
			return ;
	}
	else
	{
		if (find_name(mini->export, new_var) == 1)
			free_env_node(mini, mini->export, new_var);
		split_new_exp = split_env_vars(new_var, '=');
		if (split_new_exp == NULL)
			return (ft_error(mini, NULL, strerror(errno)));
	}
	new_node = ft_lstnew_env(split_new_exp[0], split_new_exp[1]);
	free_tab(split_new_exp);
	if (new_node == NULL)
		return (ft_error(mini, NULL, strerror(errno)));
	ft_lstadd_back_env(&mini->export, new_node);
}

int	add_env(t_mini *mini, char *new_var)
{
	char		**split_new_envp;
	char		*concat;

	concat = NULL;
	split_new_envp = split_env_vars(new_var, '=');
	if (split_new_envp == NULL)
		return (ft_error(mini, NULL, strerror(errno)), -1);
	if (split_new_envp[0][ft_strlen(split_new_envp[0]) - 1] == '+')
	{
		concat = concat_env(mini, split_new_envp[0], split_new_envp[1]);
		if (!concat)
			return (free_tab(split_new_envp), \
			ft_error(mini, NULL, strerror(errno)), -1);
		free(split_new_envp[1]);
		split_new_envp[1] = concat;
	}
	if (add_env_helper(mini, split_new_envp) < 0)
		return (ft_error(mini, NULL, strerror(errno)), -1);
	return (0);
}

static int	check_syn_error(t_mini *mini, char	*new_var)
{
	int		i;

	if (ft_isalpha(new_var[0]) == 0 && new_var[0] != '_')
	{
		if (new_var[0] == '-')
		{
			mini->exit_status = 2;
			return (ft_error(mini, " invalid option", NULL), -1);
		}
		mini->exit_status = 1;
		return (ft_error(mini, " not a valid identifier", NULL), -1);
	}
	i = 1;
	while (new_var[i] && new_var[i] != '=')
	{
		if (ft_isalnum(new_var[i]) == 0 && new_var[i] != '_' \
			&& ft_strncmp(new_var + i, "+=", 2) != 0)
		{
			mini->exit_status = 1;
			return (ft_error(mini, " not a valid identifier", NULL), -1);
		}
		i++;
	}
	return (0);
}

void	add_var_to_list(t_mini *mini, t_token *cur)
{
	char	*res;
	char	*new_var;
	int		i;

	i = 1;
	while (cur->cmd_tab[i])
	{
		res = NULL;
		new_var = cur->cmd_tab[i];
		if (check_syn_error(mini, new_var) != 0)
			return ;
		res = ft_strchr(new_var, '=');
		if (res)
		{
			if (add_env(mini, new_var) != 0)
				return ;
		}
		else if (ft_strncmp(new_var, "=", ft_strlen(new_var)) == 0)
			return (ft_error(mini, " not a valid identifier", NULL));
		add_exp(mini, new_var, res);
		if (mini->error)
			return ;
		i++;
	}
}
