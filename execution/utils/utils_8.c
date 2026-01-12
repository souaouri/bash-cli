/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 00:51:39 by souaouri          #+#    #+#             */
/*   Updated: 2024/08/03 00:30:39 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_list(t_cmds *list)
{
	list->cmmd = NULL;
	list->cmmd = join_cmd_arg(list->cmd, list->args);
}

void	execut(t_var *var, t_env **env_list, t_cmds *list)
{
	if (var->hold_fd_in > 0)
		close(var->hold_fd_in);
	execut_cmd(env_list, list->cmmd, list);
}

int	ft_atoi(const char	*str)
{
	int		i;
	int		sign;
	size_t	res;

	i = 0;
	sign = 1;
	res = 0;
	if (!str)
		return (0);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + str[i] - 48;
		i++;
	}
	return (res * sign);
}

char	*extract_exit_status(t_env *env_list)
{
	while (env_list)
	{
		if (!ft_strncmp(env_list->content, "?=", 2))
			return (get_eq_to_fin(env_list->content));
		env_list = env_list->next;
	}
	return (NULL);
}

void	exec_if_path_eq_null(char **cmd, char **env)
{
	if (execve(*cmd, cmd, env) == -1)
	{
		if (ft_strchr(cmd[0], '/'))
		{
			is_error(cmd[0]);
			print_error(cmd[0], "Per_denied");
			exit (126);
		}
		if (!ft_strcmp(cmd[0], ".."))
		{
			print_error(cmd[0], "is_a_direc");
			exit (126);
		}
		print_error(cmd[0], "no_such_file");
		exit (127);
	}
}
