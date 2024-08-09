/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:52:38 by skanna            #+#    #+#             */
/*   Updated: 2024/08/09 14:13:28 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_mini *mini, t_token *cur)
{
	int	count;

	if (!cur->cmd_tab)
		return (-1);
	count = 0;
	while (cur->cmd_tab[count])
		count++;
	if (count >= 3)
		return (ft_error(mini, "cd: Too many arguments", NULL), -1);
	return (count);
}

static void	go_home(t_mini *mini, t_token *cur, char **cmd_tab)
{
	char	*path;
	char	*value;

	value = NULL;
	path = get_env_value(mini->env, "HOME");
	if (path == NULL)
		return (ft_error(mini, NULL, strerror(errno)));
	if (count_args(mini, cur) == 1 && path[0] == '\0')
		return (free(path), ft_error(mini, "cd: HOME not set", NULL));
	if (cmd_tab[1] && ft_strncmp(cmd_tab[1], "~", \
		longer_len((char *)cmd_tab[1], "~")) == 0)
	{
		free(path);
		value = get_env_value(mini->env, "USER");
		if (!value)
			return (ft_error(mini, NULL, strerror(errno)));
		path = ft_strjoin("/home/", value);
		free(value);
		if (!path)
			return (ft_error(mini, NULL, strerror(errno)));
	}
	if (chdir(path) != 0)
		return (free(path), ft_error(mini, NULL, strerror(errno)));
	else
		free (path);
}

static void	go_back_utils(t_mini *mini, const char *path)
{
	char	*cpy_path;
	int		i;

	cpy_path = (char *)path;
	i = 0;
	while (cpy_path[i])
	{
		if (ft_isalpha(cpy_path[i]) != 0)
		{
			if (chdir(cpy_path) != 0)
				ft_error(mini, NULL, strerror(errno));
			return ;
		}
		i++;
	}
	while (ft_strncmp(cpy_path, "..", 2) == 0)
	{
		go_back(mini);
		if (cpy_path[2] == '/' && cpy_path[3])
			cpy_path = cpy_path + 3;
		else
			break ;
	}
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
	if (new_node == NULL)
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

void	cd_cmd(t_mini *mini, t_token *cur)
{
	const char	*path;

	if (count_args(mini, cur) < 0)
		return ;
	path = cur->cmd_tab[1];
	if (count_args(mini, cur) == 1 || !path \
		|| ft_strncmp(path, "~", longer_len((char *)path, "~")) == 0)
		go_home(mini, cur, cur->cmd_tab);
	else if (ft_strncmp(path, "..", longer_len((char *)path, "..")) == 0 \
		|| ft_strncmp(path, "../", 3) == 0)
		go_back_utils(mini, path);
	else if (ft_strncmp(path, "-", longer_len((char *)path, "-")) == 0)
		
	else if (chdir(path) != 0)
		return (ft_error(mini, NULL, strerror(errno)));
	update_env(mini);
	if (mini->error == 0)
		mini->exit_status = 0;
	update_export(mini);
	if (mini->error == 0)
		mini->exit_status = 0;
}
