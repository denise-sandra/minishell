/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var_to_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/20 15:28:05 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_with_nulll_value(t_mini *mini, char *new_var, char	***split)
{
	char	*value;

	value = get_env_value(mini->export, new_var);
	if (!value)
		return (ft_error(mini, NULL, strerror(errno)), 1);
	if (value[0] != '\0')
		return (free(value), 1);
	free(value);
	*split = malloc(2 * sizeof(char *));
	if (!split)
		return (ft_error(mini, NULL, strerror(errno)), 1);
	(*split)[0] = ft_strdup(new_var);
	(*split)[1] = NULL;
	if (!(*split)[0])
		return (ft_error(mini, NULL, strerror(errno)), 1);
	return (0);
}

static void	add_exp(t_mini *mini, char *new_var, char *res)
{
	char		**split_new_exp;
	t_lst_env	*new_node;

	split_new_exp = NULL;
	if (res)
	{
		split_new_exp = split_env_vars(new_var, '=');
		if (split_new_exp == NULL)
			return (ft_error(mini, NULL, strerror(errno)));
		free_env(mini->export, split_new_exp[0]);
	}
	else
	{
		if (add_with_nulll_value(mini, new_var, &split_new_exp) == 1)
			return ;
	}
	new_node = ft_lstnew_env(split_new_exp[0], split_new_exp[1]);
	free_tab(split_new_exp);
	if (new_node == NULL)
		return (ft_error(mini, NULL, strerror(errno)));
	ft_lstadd_back_env(&mini->export, new_node);
}

static void	add_env(t_mini *mini, char *new_var)
{
	char		**split_new_envp;
	t_lst_env	*new_node;

	split_new_envp = split_env_vars(new_var, '=');
	if (split_new_envp == NULL)
		return (ft_error(mini, NULL, strerror(errno)));
	free_env(mini->env, split_new_envp[0]);
	new_node = ft_lstnew_env(split_new_envp[0], split_new_envp[1]);
	free_tab(split_new_envp);
	if (new_node == NULL)
		return (ft_error(mini, NULL, strerror(errno)));
	ft_lstadd_back_env(&mini->env, new_node);
	if (mini->mod_env == 1)
		free_tab(mini->env_char);
	clean_env_exp(mini, 2);
	mini->export = copy_list(mini->env);
	if (mini->export == NULL)
		return (ft_error(mini, NULL, strerror(errno)));
	mini->env_char = list_to_tab(mini);
}

static void	check_syn_error(t_mini *mini, char	*new_var)
{
	int		i;

	if (ft_isalpha(new_var[0]) == 0)
	{
		mini->exit_status = 1;
		return (ft_error(mini, " not a valid identifier", NULL));
		// return (ft_error(mini, NULL, strerror(errno)));
	}
	i = 1;
	while (new_var[i] && new_var[i] != '=')
	{
		if (ft_isalnum(new_var[i]) == 0)
		{
			mini->exit_status = 1;
			return (ft_error(mini, " not a valid identifier", NULL));
			// return (ft_error(mini, NULL, strerror(errno)));
		}
		i++;
	}
}

void	add_var_to_list(t_mini *mini, t_token *cur)
{
	char	*res;
	char	*new_var;

	res = NULL;
	new_var = cur->cmd_tab[1];
	check_syn_error(mini, new_var);
	if (mini->error)
		return ;
	res = ft_strchr(new_var, '=');
	if (res)
		add_env(mini, new_var);
	else if (ft_strncmp(new_var, "=", ft_strlen(new_var)) == 0)
		return (ft_error(mini, " not a valid identifier", NULL));
		// return (ft_error(mini, NULL, strerror(errno)));
	add_exp(mini, new_var, res);
	if (mini->error)
		return ;
}
