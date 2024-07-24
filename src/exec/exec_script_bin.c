/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_script_bin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:03:22 by skanna            #+#    #+#             */
/*   Updated: 2024/07/24 14:19:13 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	exec_bin(t_mini *mini, char *name, int script)
{
	char	*args[2];

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

static int	exec_script(t_mini *mini, char *name, int script)
{
	char	*args[3];

	close(script);
	script = open(name, O_RDONLY);
	if (script == -1)
	{
		mini->exit_status = 127;
		return (ft_error(mini, NULL, strerror(errno)), -1);
	}
	args[0] = get_shebang(mini, script);
	if (!args[0])
		return (close(script), 1);
	args[1] = name;
	args[2] = NULL;
	if (execve(args[0], args, mini->env_char) == -1)
	{
		mini->exit_status = 127;
		return (close(script), ft_error(mini, NULL, strerror(errno)), 1);
	}
	close(script);
	return (0);
}

static int	check_file(int script)
{
	char buf[1024];
	int	byte;
	int	i;

	ft_bzero(buf , 1024);
	byte = read(script, buf, 1023);
	i = 0;
	if (byte < 0)
		return (-1) ;
	while (buf[i])
	{
		printf("c: %c\n", buf[i]);
		if (buf[i] == '#')
			return (1);
		i++;
	}
	return (0);
}

int	exec_script_bin(t_mini *mini, t_token *tmp)
{
	char		*name;
	int		script;

	name = get_name(tmp);
	if (name)
	{
		if ( process_file(mini, name, &script) < 0)
			return (1);
		if (ft_strncmp(name, "minishell", longer_len(name, "minishell")) == 0)
		{
			if (handle_shlvl(mini) != 0)
				return (1);
		}
		if (check_file(script) == 1)
			exec_script(mini, name, script);
		else
			exec_bin(mini, name, script);
	}
	return (0);
}
