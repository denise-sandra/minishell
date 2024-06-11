/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/11 13:19:11 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_env(t_lst_env *env)
{
	char *name;
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

static char	**list_to_tab(t_minishell *mini)
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

static void	print_export(t_minishell *mini)
{
	t_lst_env	*temp;
	temp = mini->env;
	while (temp)
	{
		printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
		temp = temp->next;
	}
}

static void	add_env(t_minishell *mini, char *new_var)
{
	char		**split_new_envp;
	t_lst_env	*new_node;

	split_new_envp = split_env_vars(new_var, '=');
	if (split_new_envp == NULL)
		ft_error("Malloc in export cmd", mini);
	replace_env(mini->env, split_new_envp[0]);
	new_node = ft_lstnew_env(split_new_envp[0], split_new_envp[1]);
	if (new_node == NULL)
	{
		free_tab(split_new_envp);
		ft_error("Malloc in export function", mini);
	}
	ft_lstadd_back_env(&mini->env, new_node);
	free_tab(split_new_envp);
	if (mini->mod_env == 1)
		free_tab(mini->env_char);
	mini->env_char = list_to_tab(mini);          //poner en exec
}

void	export_command(t_minishell *mini)
{
	int			res;
	char		*new_var;

	res = 0;
	new_var = mini->token->tab[1];
	if (new_var)
		res = ft_strchr_int(new_var, '=');
	else
	{
		print_export(mini);
		return ;
	}	
	if (res > 0)
		add_env(mini, new_var);
	else if (ft_strncmp(new_var, "=", ft_strlen(new_var)) == 0)
		printf("bash: export: `=': not a valid identifier\n");
}
