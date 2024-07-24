/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:16:30 by skanna            #+#    #+#             */
/*   Updated: 2024/07/24 16:01:30 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	execute_command(t_mini *mini, char **cmd, char **sh_argv)
{
	int		ret;

	ret = execve(cmd[0], cmd, mini->env_char);
	if (ret == -1)
	{
		if (errno == ENOEXEC)
		{
			ret = execve("/bin/sh", sh_argv, mini->env_char);
			if (ret == -1)
				return (ft_error(mini, NULL, strerror(errno)), -1);
		}
		else
			return (ft_error(mini, NULL, strerror(errno)), -1);
	}
	return (0);
}

int	is_absolute_or_relative_path(t_mini *mini, t_token *tmp)
{
	char	*sh_argv[3];
	int		ret;

	sh_argv[0] = "/bin/sh";
	sh_argv[1] = tmp->cmd_tab[0];
	sh_argv[2] = NULL;
	ret = 0;
	if (tmp->cmd_tab[0][0] == '/' || tmp->cmd_tab[0][0] == '.')
	{
		ret = access(tmp->cmd_tab[0], X_OK);
		if (ret == 0)
			return (execute_command(mini, tmp->cmd_tab, sh_argv));
		else
			return (-2);
	}
	return (1);
}
