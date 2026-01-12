/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 01:29:04 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/31 01:31:01 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_file_and_directory_errors(char *cmd, char *type)
{
	if (!ft_strcmp(type, "no_such_file"))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (!ft_strcmp(type, "is_a_direc"))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
	}
	else if (!ft_strcmp(type, "Per_denied"))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
}

int	print_error(char *cmd, char *type)
{
	if (!ft_strcmp(type, "cmd_not_found"))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (!ft_strcmp(type, "pars_export"))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else if (!ft_strcmp(type, "fork"))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("fork: Resource temporarily unavailable\n", 2);
	}
	else
		print_file_and_directory_errors(cmd, type);
	return (0);
}

int	builtins_print_error(char *cmd, char *type)
{
	if (!ft_strcmp(type, "pars_export"))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	else if (!ft_strcmp(type, "pars__export"))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	else if (!ft_strcmp(type, "no_such_file"))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

int	check_for_errors(char *arg, int i, int *error)
{
	while (arg[i])
	{
		if ((arg[i] >= 9 && arg[i] <= 13) || arg[i] == 32)
		{
			while (arg[i])
			{
				if (arg[i] != 32)
				{
					*error = 1;
					break ;
				}
				*error = 0;
				i++;
			}
			break ;
		}
		if (!ft_isdigit(arg[i]))
			*error = 1;
		i++;
	}
	return (0);
}

void	is_error(char *cmd)
{
	if (check_is_dir(cmd) == 2)
	{
		print_error(cmd, "is_a_direc");
		exit (126);
	}
	if (check_is_dir(cmd) == 1)
	{
		print_error(cmd, "Per_denied");
		exit (126);
	}
	if (check_is_dir(cmd) == -1)
	{
		print_error(cmd, "no_such_file");
		exit (127);
	}
}
