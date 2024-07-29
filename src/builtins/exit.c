/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derjavec <derjavec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:38:05 by skanna            #+#    #+#             */
/*   Updated: 2024/07/29 12:29:46 by derjavec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	verify_spaces(t_mini *minishell, char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '\0')
	{
		minishell->exit_status = 0;
		return (-1);
	}
	return (i);
}

static void	is_arg_valid(t_mini *minishell, char *exit_arg, int sign)
{
	long long	arg;
	int			err;

	err = 0;
	arg = ft_atoll(exit_arg, &err) * sign;
	if (err || arg < LLONG_MIN + 1 || arg > LLONG_MAX)
	{
		minishell->exit_status = 2;
		minishell->should_exit = 1;
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		return ;
	}
	if (arg < 0)
		arg = 256 + (arg % 256);
	minishell->exit_status = (arg % 256);
	minishell->should_exit = 1;
}

static void	is_var_valid(t_mini *minishell, char *var_name)
{
	char	*var_value;
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	var_value = get_env_value(minishell->env, var_name);
	if (var_value == NULL)
	{
		minishell->exit_status = 0;
		minishell->should_exit = 1;
		return ;
	}
	else
	{
		if (var_value[i] == '-')
			sign = -1;
		if (var_value[i] == '-' || var_value[i] == '+')
			is_arg_valid(minishell, var_value + ++i, sign);
		if (ft_isdigit(var_value[i]))
			is_arg_valid(minishell, var_value + i, sign);
	}
}

static void	process_exit_arg(t_mini *minishell, char *arg)
{
	int	sign;
	int	i;

	sign = 1;
	i = 0;
	if (arg[0] && arg[1] && (arg[0] == '-' || arg[0] == '+') \
	&& (!ft_isdigit(arg[1])))
		return (ft_error(minishell, \
		"minishell: exit: numeric argument required", NULL));
	while (arg[i])
	{
		if (arg[i] == '-')
			sign = -1;
		if (arg[i] == '-' || arg[i] == '+')
			return (is_arg_valid(minishell, arg + ++i, sign));
		if (arg[i] == '$')
			return (is_var_valid(minishell, arg + ++i));
		if (ft_isdigit(arg[i]))
			return (is_arg_valid(minishell, arg + i, sign));
		else
		{
			minishell->exit_status = 2;
			minishell->should_exit = 1;
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			return ;
		}
	}
}

void	exit_cmd(t_mini *minishell, char **cmd_tab)
{
	int	i;

	ft_putstr_fd("exit\n", 1);
	if (!cmd_tab[1])
	{
		minishell->exit_status = 0;
		minishell->should_exit = 1;
		return ;
	}
	if (cmd_tab[2])
		return (ft_error(minishell, \
		"minishell: exit: too many arguments", NULL));
	if (cmd_tab[1][0] == '\0')
	{
		minishell->exit_status = 2;
		minishell->should_exit = 1;
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		return ;
	}
	i = 0;
	if (cmd_tab[1][i] == '"' || cmd_tab[1][i] == '\'' )
		i = verify_spaces(minishell, ++cmd_tab[1]);
	if (i == -1)
		return ;
	process_exit_arg(minishell, cmd_tab[1] + i);
}
