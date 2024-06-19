/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/19 14:17:10 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_env(t_lst_env *env)
{
	char	*name;
	char	*value;
	char	*joint_a;
	char	*joint_b;

	name = ft_strdup(env->name);
	value = ft_strdup(env->value);
	if (name == NULL || value == NULL)
		return (NULL);
	joint_a = ft_strjoin_char(name, '=');
	if (joint_a == NULL)
		return (NULL);
	joint_b = ft_strjoin_free(joint_a, value);
	if (joint_b == NULL)
		return (NULL);
	return (joint_b);
}

static char	**list_to_tab(t_mini *mini)
{
	t_lst_env	*tmp;
	char		**env;
	int			i;

	env = malloc((count_elements(mini) + 1) * sizeof(char *));
	if (env == NULL)
		ft_error("Malloc in export cmd", mini);
	i = 0;
	tmp = mini->env;
	while (tmp)
	{
		env[i] = join_env(tmp);
		if (env[i] == NULL)
		{
			free_tab(env);
			ft_error("Malloc in export cmd", mini);
		}
		tmp = tmp->next;
		i++;
	}
	env[i] = NULL;
	mini->mod_env = 1;
	return (env);
}

static void	print_export(t_lst_env *env)
{
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
		else
			printf("declare -x %s\n", env->name);
		env = env->next;
	}
}

static void	add_exp(t_mini *mini, char *new_var, char *res)
{
	char		**split_new_exp;
	char	*value;
	t_lst_env	*new_node;

	split_new_exp = NULL;
	if (res)
	{
		printf("pepe\n");
		split_new_exp = split_env_vars(new_var, '=');
		if (split_new_exp == NULL)
			return (ft_error("Malloc in export cmd", mini));
		free_env(mini->export, split_new_exp[0]);
	}
	else
	{
		value = get_env_value(mini->export, new_var);
		if (!value)
			return (ft_error("Malloc in export function", mini));
		if (value[0] != '\0')
			return (free(value));
		free(value);
		split_new_exp = malloc(2 * sizeof(char*));
		if (!split_new_exp)
			return (ft_error("Malloc in export function", mini));
		split_new_exp[0] = ft_strdup(new_var);
		split_new_exp[1] = NULL;
		if (!split_new_exp[0])
			return (ft_error("Malloc in export function", mini));
	}
	new_node = ft_lstnew_env(split_new_exp[0], split_new_exp[1]);
	free_tab(split_new_exp);
	if (new_node == NULL)
		return (ft_error("Malloc in export function", mini));
	ft_lstadd_back_env(&mini->export, new_node);
}


static void	add_env(t_mini *mini, char *new_var)
{
	char		**split_new_envp;
	t_lst_env	*new_node;

	split_new_envp = split_env_vars(new_var, '=');
	if (split_new_envp == NULL)
		return (ft_error("Malloc in export cmd", mini));
	free_env(mini->env, split_new_envp[0]);
	new_node = ft_lstnew_env(split_new_envp[0], split_new_envp[1]);
	free_tab(split_new_envp);
	if (new_node == NULL)
		return (ft_error("Malloc in export function", mini));
	ft_lstadd_back_env(&mini->env, new_node);
	if (mini->mod_env == 1)
		free_tab(mini->env_char);
	clean_exp(mini);
	mini->export = copy_list(mini->env);
	if (mini->export == NULL)
		return (ft_error("Malloc error", mini));
	mini->env_char = list_to_tab(mini);
}

void	export_command(t_mini *mini, t_token *cur)
{
	char	*res;
	char	*new_var;
	int	i;

	res = NULL;
	new_var = cur->cmd_tab[1];
	if (new_var)
	{
		res = ft_strchr(new_var, '=');
		printf("res %p %s\n", res, new_var);
		if (ft_isalpha(new_var[0]) == 0)
		{
			mini->exit_status = 1;
			ft_error(" not a valid identifier\n", mini);
			return ;
		}
		i = 1;
		while (new_var[i] && new_var[i] != '=')
		{
			if(isalnum(new_var[i]) == 0)
			{
				mini->exit_status = 1;
				return (ft_error(" not a valid identifier\n", mini));
			}
			i++;
		}
		if (res)
			add_env(mini, new_var);
		else if (ft_strncmp(new_var, "=", ft_strlen(new_var)) == 0)
			return (ft_error(" not a valid identifier\n", mini));
		add_exp(mini, new_var, res);
		if (mini->error)
			return ;
	}
	else
		print_export(mini->export);
	
}
