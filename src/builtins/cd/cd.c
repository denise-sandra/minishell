/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:52:38 by skanna            #+#    #+#             */
/*   Updated: 2024/08/12 09:19:04 by skanna           ###   ########.fr       */
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

static void	go_to_oldpwd(t_mini *mini)
{
	char		*old_pwd;

	old_pwd = get_env_value(mini->env, "OLDPWD");
	if (!old_pwd)
		return (ft_error(mini, NULL, strerror(errno)));
	if (chdir(old_pwd) != 0)
		return (free(old_pwd), ft_error(mini, NULL, strerror(errno)));
	free(old_pwd);
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
		go_to_oldpwd(mini);
	else if (ft_strncmp(path, "-", 1) == 0)
	{
		mini->exit_status = 2;
		return (ft_error(mini, "cd : invalid option", NULL));
	}
	else if (chdir(path) != 0)
		return (ft_error(mini, NULL, strerror(errno)));
	update_env_cd(mini);
	update_export_cd(mini);
	if (mini->error == 0)
		mini->exit_status = 0;
}
