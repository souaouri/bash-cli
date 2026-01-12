/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:43:37 by souaouri          #+#    #+#             */
/*   Updated: 2024/08/03 03:55:10 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_export(t_env *list_env)
{
	t_env	*head;
	t_env	*copy_env;

	copy_env = env_dup(list_env);
	ft_sort_env(copy_env);
	head = copy_env;
	while (head)
	{
		if (!ft_strchr(get_env_eq(head->content), '?'))
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(add_double_quotes(head->content), 1);
			ft_putstr_fd("\n", 1);
		}
		head = head->next;
	}
}

void	add_var_exist(char *cmd, t_env *list_env, int error)
{
	char	*var;

	var = ft_strjoin(get_var_from_beg_to_eq(cmd), "=");
	if (!find_var(list_env, var))
	{
		cmd = remove_plus(cmd);
		add_variable(list_env, cmd, error);
	}
	else
		add_variable(list_env, cmd, error);
}

int	if_var_exist_return(char *cmd, t_env *list_env)
{
	char	*var;

	var = ft_strjoin(cmd, "=");
	if (find_var(list_env, var))
		return (1);
	return (0);
}

int	add(t_env *list_env, char *cmd, int error)
{
	if (error && error != -1 && !check_for_first_char(get_env_eq(cmd)))
		add_var_exist(cmd, list_env, error);
	else if (!check_arg_is_valide(get_env_eq(cmd))
		&& !check_for_first_char(get_env_eq(cmd)))
		add_variable(list_env, cmd, error);
	else if (error != -1)
		return (builtins_print_error(cmd, "pars_export"));
	return (0);
}

int	export_exe(char **cmd, t_env *list_env)
{
	int		i;
	int		x;
	int		error;

	i = 1;
	x = 0;
	if (cmd [0] == NULL || cmd == NULL)
		return (0);
	while (cmd[i])
	{
		if (!check_var(cmd[i], list_env))
			return (0);
		error = check_for_plus_and_eq(cmd[i], 1);
		if (error == -1)
			x++;
		if (add(list_env, cmd[i], error))
			x++;
		i++;
	}
	if (!ft_strcmp(cmd[0], "export") && !cmd[1])
		print_export(list_env);
	if (x != 0)
		return (1);
	else
		return (0);
}
