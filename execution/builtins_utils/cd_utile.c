/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:03:08 by souaouri          #+#    #+#             */
/*   Updated: 2024/08/02 17:04:41 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_pwd(t_tools *tools, t_env *list_env)
{
	char	*join;
	char	*g_pwd;

	if (tools->pwd)
	{
		change_path_cd(tools);
		if (!tools->old_pwd)
		{
			g_pwd = getcwd(NULL, 0);
			join = ft_strjoin("export OLDPWD=", g_pwd);
			export_exe(ft_split_exe(join, 32), list_env);
			free(g_pwd);
		}
		else
		{
			join = ft_strjoin("export OLDPWD=", tools->old_pwd);
			export_exe(ft_split_exe(join, 32), list_env);
		}
	}
	g_pwd = getcwd(NULL, 0);
	join = ft_strjoin("export PWD=", g_pwd);
	export_exe(ft_split_exe(join, 32), list_env);
	free (g_pwd);
}

int	chdir_func(t_cmds *s_cmd, t_tools *tools, t_env *list_env)
{
	int		ret;
	char	*free_two;

	ret = chdir(s_cmd->cmmd[1]);
	free_two = getcwd(NULL, sizeof(NULL));
	if (!free_two)
	{
		add_emergency_pwd(tools, list_env);
		return (0);
	}
	free(free_two);
	if (ret != 0)
		return (builtins_print_error(s_cmd->cmmd[1], "no_such_file"));
	return (2);
}
