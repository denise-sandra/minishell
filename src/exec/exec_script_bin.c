/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_script.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/23 15:16:49 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	exec_bin(t_mini *mini, t_token *tmp, char *args)
{

     args[0] = name;
     args[1] = NULL;
     if (execve(args[0], args, mini->env_char) == -1)
     {
          mini->exit_status = 127;
          return (close(script), ft_error(mini, NULL, strerror(errno)), 1);
     }
     close(script);
	return (0);
}

int	exec_script(t_mini *mini, t_token *tmp, char *args)
{
	if (execve(args[0], args, mini->env_char) == -1)
	{
		mini->exit_status = 127;
		return (close(script), ft_error(mini, NULL, strerror(errno)), 1);
	}
	close(script);
	return (0);
}

int	exec_script_bin(t_mini *mini, t_token *tmp)
{
	char	*name;
	int		script;
	char	*args[3];

	name = get_name(tmp);
	if (name)
	{
		init_args(args);
		if (process_script(mini, name, &script) != 0)
			return (1);
		if (ft_strncmp(name, "minishell", longer_len(name, "minishell")) == 0)
		{
			if (handle_shlvl(mini) != 0)
				return (1);
		}
		if (ft_strncmp(name + ft_strlen(name) - 3, ".sh", 3) == 0)
			args[0] = get_shebang(mini, script, args[0]);
		if (!args[0])
			return (close(script), 1);
		if (args[0][0] == '\0')
			exec_bin(mini, tmp, args)
		else
			exec_script(mini, tmp, args)
	}
	return (0);
}
