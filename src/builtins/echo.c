/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:52:38 by skanna            #+#    #+#             */
/*   Updated: 2024/08/05 11:35:51 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_after_dash(t_token *cur, int *n, int *i)
{
	int	j;

	j = 1;
	while (cur->cmd_tab[*i][j])
	{
		if (cur->cmd_tab[*i][j] != 'n')
			return (-1);
		j++;
	}
	if (cur->cmd_tab[*i][j] == '\0')
	{
		++(*i);
		++(*n);
	}
	return (0);
}

static int	echo_opt(t_token *cur, int *n)
{
	int	i;

	i = 1;
	while (cur->cmd_tab[i] && ft_strncmp(cur->cmd_tab[i], "-n", 2) == 0)
	{
		if (ft_strlen(cur->cmd_tab[i]) > 2)
		{
			if (check_after_dash(cur, n, &i) < 0)
				break ;
		}
		else
		{
			i++;
			++(*n);
		}
	}
	return (i);
}

static void	is_cd(t_mini *mini, t_token *cur, int *i)
{
	char	*home;

	printf("cd");
	if (cur->cmd_tab[*i])
		printf(" ");
	if (cur->cmd_tab[*i] && ft_strncmp(cur->cmd_tab[*i], "~", \
		longer_len(cur->cmd_tab[*i], "~")) == 0)
	{
		home = get_env_value(mini->env, "HOME");
		if (!home)
			return (ft_error(mini, NULL, strerror(errno)));
		printf("cd %s", home);
		free(home);
		if (cur->cmd_tab[*i + 1])
			printf(" ");
		(*i)++;
	}
}

static int	echo_print(t_token *cur, int i, int j)
{
	while (cur->cmd_tab[i] && cur->cmd_tab[i][j])
	{
		printf("%c", cur->cmd_tab[i][j]);
		j++;
	}
	if (cur->cmd_tab[i + 1])
		printf(" ");
	return (j);
}

void	echo_command(t_mini *mini, t_token *cur)
{
	int	i;
	int	j;
	int	n;

	n = 0;
	i = echo_opt(cur, &n);
	while (cur->cmd_tab[i])
	{
		j = 0;
		if (ft_strncmp(cur->cmd_tab[i], "cd", \
			longer_len(cur->cmd_tab[i], "cd")) == 0)
		{
			i++;
			is_cd(mini, cur, &i);
			if (!cur->cmd_tab[i])
				break ;
		}
		j = echo_print(cur, i, j);
		i++;
	}
	if (n == 0)
		printf("\n");
	if (mini->error == 0)
		mini->exit_status = 0;
}
