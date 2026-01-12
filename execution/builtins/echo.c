/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:49:32 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/04 09:49:32 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	int	check_arg_is_null(char *cmd)
{
	if (cmd == NULL)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	return (1);
}

int	search_for_char_n(char *arg)
{
	int	i;

	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	print_args(char	**arg, int i)
{
	ft_putstr_fd(arg[i], 1);
	if (arg[i + 1])
		ft_putstr_fd(" ", 1);
}

void	echo(char **cmd, t_cmds *cmds)
{
	int	i;
	int	v;

	i = 1;
	v = 0;
	if (!check_arg_is_null(cmd[i]))
		return ;
	while (cmd[i] && !ft_strncmp(cmd[i], "-n", 2))
	{
		if (!search_for_char_n(cmd[i]))
			v++;
		else
			break ;
		i++;
	}
	if (ft_strlen_1(cmds->args) == i - 1)
		return ;
	while (cmd[i])
	{
		print_args(cmd, i);
		i++;
	}
	if (!v)
		ft_putstr_fd("\n", 1);
}
