/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/06/12 09:36:04 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**pars_path(t_mini *mini)
{
	char	*path;
	char	**split_paths;

	path = get_env_value(mini->env, "PATH");
	check_malloc_error(mini, path, "Malloc in exectution",  -1);
	split_paths = ft_split(path, ':');
	if (!split_paths)
		return (NULL);
	free(path);
	return (split_paths);
}

static char	*join_path(t_mini *mini, char *cmd, char *path)
{
	char	*joint_a;
	char	*joint_b;

	joint_a = ft_strjoin_char(path, '/');
	check_malloc_error(mini, joint_a, "Malloc in exectution",  -1);
	joint_b = ft_strjoin(joint_a, cmd);
	check_malloc_error(mini, joint_b, "Malloc in exectution",  -1);
	free(joint_a);
	return (joint_b);
}

static int	get_infile(t_mini *mini, t_token *token)
{
	if (token->type = IN)
	{
		mini->fd_in =  open(token->next->value, O_RDONLY);
		if (mini->fd_in < 0)
			ft_error("Opening infile", mini);
	}
	return (mini->fd_in);
}


void	execution(t_mini *mini)
{
	t_token	*tmp;
	char	**paths;
	char	*path_with_token;
	int		i;

	tmp = mini->token;
	while (tmp)
	{
		mini->fd_in = get_infile(mini, tmp);
		if (tmp->type == COMMAND && execute_builtin(mini, tmp->cmd_tab[0]) == 0)
			return ;
		if (tmp->type == COMMAND)
		{
			paths = pars_path(mini);
			if (paths == NULL)
				return (ft_error("Malloc in exectution", mini));
			i = 0;
			while (paths[i])
			{
				path_with_token = join_path(mini, tmp->cmd_tab[0], paths[i]);
				if (access(path_with_token, X_OK) == 0)
				{
					if (execve(path_with_token, tmp->cmd_tab, mini->env_char) == -1)
						return (ft_error("execve Error", mini));
				}
				free(path_with_token);
				i++;
			}
			free(paths);
			printf("Command '%s' not found\n", tmp->cmd_tab[0]);
			return ;
		}
		tmp = tmp->next;
	}
}
