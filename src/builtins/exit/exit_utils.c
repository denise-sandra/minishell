/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skanna <skanna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:19:57 by skanna            #+#    #+#             */
/*   Updated: 2024/07/29 17:33:46 by skanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_signs(t_mini *mini, char *arg)
{
	if (arg[0] && arg[1] && (arg[0] == '-' || arg[0] == '+') \
	&& (!ft_isdigit(arg[1])))
	{
		mini->exit_status = 2;
		mini->should_exit = 1;
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		return (-1);
	}
	return (0);
}
