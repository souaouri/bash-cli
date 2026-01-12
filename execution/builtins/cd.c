/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:49:23 by souaouri          #+#    #+#             */
/*   Updated: 2024/08/04 02:14:27 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_path_ret(char *str, t_env *list_env)
{
	int	i;

	i = 0;
	while (list_env)
	{
		if (!ft_strncmp(list_env->content, str, ft_strlen(str)))
			return (ft_substr(list_env->content, ft_strlen(str),
					ft_strlen(list_env->content) - ft_strlen(str)));
		list_env = list_env->next;
	}
	return (NULL);
}

int	specific_path(t_env *list_env, char *str)
{
	char	*tmp;
	int		ret;

	tmp = find_path_ret(str, list_env);
	ret = chdir(tmp);
	if (ret != 0)
	{
		str = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" not set\n", 2);
	}
	return (ret);
}

void	add_path_to_env(t_tools *tools, t_env *list_env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (list_env)
	{
		if (!ft_strncmp(list_env->content, "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", tools->pwd);
			free(ft_strdup(list_env->content));
			list_env->content = tmp;
		}
		else if (!ft_strncmp(list_env->content, "OLDPWD=", 7) && tools->old_pwd)
		{
			tmp = ft_strjoin("OLDPWD=", tools->old_pwd);
			free(ft_strdup(list_env->content));
			list_env->content = tmp;
		}
		list_env = list_env->next;
	}
}

int	mini_cd(t_tools *tools, t_cmds *s_cmd, t_env *list_env)
{
	int		ret;
	int		re;
	char	*free_one;

	ret = 0;
	if (!ft_find_path(change_list_to_env(list_env), "PWD=", 4)
		|| !ft_find_path(change_list_to_env(list_env), "OLDPWD=", 4))
		set_pwd(tools, list_env);
	if (check_for_arg_cd(s_cmd->cmmd[1]))
		ret = specific_path(list_env, "HOME=");
	else
	{
		re = chdir_func(s_cmd, tools, list_env);
		if (re != 2)
			return (re);
	}
	if (ret != 0)
		return (1);
	free_one = change_path_cd(tools);
	if (!free_one)
		return (free(free_one), 0);
	add_path_to_env(tools, list_env);
	free (free_one);
	return (0);
}

int	cd_exec(t_cmds *cmds, t_env *list_env)
{
	t_tools	*tools;
	char	**env;
	int		re;

	tools = my_alloc(sizeof(t_tools), 0);
	if (tools == NULL)
		return (0);
	env = change_list_to_env(list_env);
	tools->pwd = ft_find_path(env, "PWD=", 4);
	tools->old_pwd = ft_find_path(env, "OLDPWD=", 7);
	re = mini_cd(tools, cmds, list_env);
	//free(tools);
	return (re);
}
