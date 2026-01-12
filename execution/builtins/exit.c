/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:46:38 by souaouri          #+#    #+#             */
/*   Updated: 2024/08/02 17:13:47 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	check_out_of_range(int sign, unsigned long long num, int *error)
{
	if ((sign == 1 && num > LONG_MAX)
		|| (sign == -1 && num > -(unsigned long)LONG_MIN))
		*error = 1;
	return (*error);
}

unsigned long long	ft_atoi_long(char *str, int *error)
{
	unsigned long long	num;
	int					sign;
	int					i;

	(void)error;
	num = 0;
	i = 0;
	sign = 1;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		if (check_out_of_range(sign, num, error))
			break ;
		i++;
	}
	return (num * sign);
}

int	get_exit_code(char *arg, int *error)
{
	unsigned long long	i;

	i = 0;
	if (!arg)
		return (0);
	while ((arg[i] >= 9 && arg[i] <= 13) || arg[i] == 32)
		i++;
	if (arg[i] == '\0')
		*error = 1;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!ft_isdigit(arg[i]))
		*error = 1;
	check_for_errors(arg, i, error);
	i = ft_atoi_long(arg, error);
	return (i % 256);
}

int	exit_builtins(t_cmds *cmd, char **args, int len, t_env *list_env)
{
	int		checker;

	(void)cmd;
	checker = check_to_print_exit(len);
	if (!checker)
	{
		ft_putstr_fd("exit\n", 2);
		if (!args[1])
			exit (ft_atoi(extract_exit_status(list_env)));
	}
	if (!args[1])
		exit (0);
	else
	{
		exit_with_exit_status(cmd, args);
		return (1);
	}
	return (0);
}
