/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:52:38 by skanna            #+#    #+#             */
/*   Updated: 2024/08/09 16:06:50 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*pwd_cmd_char(t_mini *mini)
{
	char	*cwd;
	int		size;

	size = 1024;
	cwd = malloc((size) * sizeof(char));
	if (cwd == NULL)
		return (ft_error(mini, NULL, strerror(errno)), NULL);
	if (getcwd(cwd, size) == NULL)
		return (free(cwd), ft_error(mini, NULL, strerror(errno)), NULL);
	return (cwd);
}

void	go_back(t_mini *mini)
{
	char	*path;
	char	*new_path;
	char	*root;
	int		c;

	path = pwd_cmd_char(mini);
	root = ft_strdup("/");
	if (!path || !root || \
		ft_strncmp(path, root, longer_len((char *)path, root)) == 0)
		return (free(path), free(root));
	free(root);
	c = ft_strrchr_int(path, '/');
	if (c == -1)
		return (free (path), ft_error(mini, "invalid path", NULL));
	new_path = malloc((c + 1) * sizeof(char));
	if (new_path == NULL)
		return (free(path), ft_error(mini, NULL, strerror(errno)));
	ft_strlcpy(new_path, path, c + 1);
	free(path);
	if (chdir(new_path) != 0)
	{
		free(new_path);
		return (ft_error(mini, NULL, strerror(errno)));
	}
	free(new_path);
}

void	update_env(t_mini *mini)
{
	char		*old_pwd;
	t_lst_env	*new_node;
	char		cwd[1024];

	old_pwd = get_env_value(mini->env, "PWD");
	if (!old_pwd)
		return (ft_error(mini, NULL, strerror(errno)));
	free_env_node(mini, mini->env, "OLDPWD");
	new_node = ft_lstnew_env("OLDPWD", old_pwd);
	free(old_pwd);
	if (!new_node)
		return (ft_error(mini, NULL, strerror(errno)));
	ft_lstadd_back_env(&mini->env, new_node);
	free_env_node(mini, mini->env, "PWD");
	if (getcwd(cwd, 1024) == NULL)
		return (ft_error(mini, NULL, strerror(errno)));
	new_node = ft_lstnew_env("PWD", cwd);
	if (!new_node)
		return (ft_error(mini, NULL, strerror(errno)));
	ft_lstadd_back_env(&mini->env, new_node);
}

void	update_export(t_mini *mini)
{
	char		*old_pwd;
	t_lst_env	*new_node;
	char		cwd[1024];

	old_pwd = get_env_value(mini->export, "PWD");
	if (!old_pwd)
		return (ft_error(mini, NULL, strerror(errno)));
	free_env_node(mini, mini->export, "OLDPWD");
	new_node = ft_lstnew_env("OLDPWD", old_pwd);
	free(old_pwd);
	if (!new_node)
		return (ft_error(mini, NULL, strerror(errno)));
	ft_lstadd_back_env(&mini->export, new_node);
	free_env_node(mini, mini->export, "PWD");
	if (getcwd(cwd, 1024) == NULL)
		return (ft_error(mini, NULL, strerror(errno)));
	new_node = ft_lstnew_env("PWD", cwd);
	if (new_node == NULL)
		return (ft_error(mini, NULL, strerror(errno)));
	ft_lstadd_back_env(&mini->export, new_node);
}
