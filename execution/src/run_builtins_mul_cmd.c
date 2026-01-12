/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins_mul_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:45:26 by souaouri          #+#    #+#             */
/*   Updated: 2024/08/03 00:35:54 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*to_lowercase(char *str)
{
	int		i;
	char	*ptr;

	ptr = ft_strncpy(str, ft_strlen(str));
	i = -1;
	while (ptr[++i])
	{
		if (ptr[i] >= 'A' && ptr[i] <= 'Z')
			ptr[i] += ' ';
	}
	return (ptr);
}

int	run_built_mul_cmd_2(t_env **list_env, char **nood, t_cmds *cmds)
{
	int	exit_status;

	exit_status = 0;
	if (!ft_strcmp("echo", to_lowercase(nood[0])))
		echo(nood, cmds);
	else if (!ft_strcmp("pwd", to_lowercase(nood[0])))
		ft_find_pwd(*list_env);
	else if (!ft_strcmp("env", to_lowercase(nood[0])))
		write_env(*list_env);
	else
		return (-1);
	return (exit_status);
}

int	run_built_mul_cmd_1(t_env **list_env, char **nood, t_cmds *cmds, int len)
{
	int	i;
	int	exit_status;

	i = -1;
	exit_status = 0;
	if (!ft_strcmp("cd", nood[0]))
		exit_status = cd_exec(cmds, *list_env);
	else if (!ft_strcmp("exit", nood[0]))
		exit_status = exit_builtins(cmds, nood, len, *list_env);
	else if (!ft_strcmp("export", nood[0]))
		exit_status = export_exe(nood, *list_env);
	else if (!ft_strcmp("unset", nood[0]))
	{
		while (nood[++i])
			exit_status = unset(list_env, nood[i]);
	}
	else
		return (-1);
	return (exit_status);
}

int	run_bui_p(t_env **list_env, char **nood, t_cmds *cmds, int len)
{
	char	*pwd;
	char	**env;
	int		exit_status;

	pwd = NULL;
	env = change_list_to_env(*list_env);
	if (nood == NULL)
		return (0);
	exit_status = run_built_mul_cmd_1(list_env, nood, cmds, len);
	if (exit_status == -1)
		exit_status = run_built_mul_cmd_2(list_env, nood, cmds);
	if (exit_status == -1 && ft_strcmp(nood[0], "CD"))
		print_error(nood[0], "cmd_not_found");
	exit (exit_status);
}
