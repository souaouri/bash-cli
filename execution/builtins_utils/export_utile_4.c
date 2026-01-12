/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utile_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:40:01 by souaouri          #+#    #+#             */
/*   Updated: 2024/08/04 02:53:22 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*env_dup(t_env *list)
{
	t_env	*nood;
	t_env	*new_list;

	new_list = NULL;
	if (list == NULL)
		return (NULL);
	while (list)
	{
		nood = ft_lstnew_env(list->content);
		ft_lstadd_back_env(&new_list, nood);
		list = list->next;
	}
	return (new_list);
}

int	_remove_var(t_env *list, char *new)
{
	char	*ptr;
	t_env	*temp;

	temp = list;
	while (temp)
	{
		ptr = ft_strjoin(get_env_eq(new), "=");
		if (!ft_strncmp(temp->content, ptr, ft_strlen(ptr))
			|| !ft_strcmp(temp->content, get_env_eq(new)))
		{
			temp->content = ft_strdup(new);
			//free(ptr);
			return (1);
		}
		// free(ptr);
		temp = temp->next;
	}
	return (0);
}

int	preparing_var(t_env *list, char *new)
{
	char	*join;
	char	*join_1;
	char	*ptr;

	while (list)
	{
		ptr = get_var_from_beg_to_eq(new);
		if (!ft_strncmp(list->content, ptr, ft_strlen(ptr)))
		{
			if (!ft_strchr(list->content, '='))
			{
				join = ft_strjoin(list->content, "=");
				list->content = ft_strjoin(join, get_eq_to_fin(new));
			}
			else
			{
				join_1 = get_eq_to_fin(new);
				list->content = ft_strjoin(list->content, join_1);
			}
			return (1);
		}
		list = list->next;
	}
	return (0);
}

void	add_variable(t_env *list_env, char *new, int error)
{
	t_env	*var;
	t_env	*temp;

	temp = list_env;
	if (check_for_plus_and_eq(new, 0))
		if (preparing_var(list_env, new))
			return ;
	if (_remove_var(temp, new))
		return ;
	if (error != -1)
	{
		var = ft_lstnew_env(new);
		ft_lstadd_back_env(&list_env, var);
	}
}

void	add_emergency_pwd(t_tools *tools, t_env *list_env)
{
	cd_error();
	add_path_to_env(tools, list_env);
	export_exe(ft_split_exe("export PWD+=/..", ' '), list_env);
}
