/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:44:57 by souaouri          #+#    #+#             */
/*   Updated: 2024/08/04 09:58:57 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_emergency_env(t_env **env)
{
	t_env	*first_line;
	t_env	*second_line;
	t_env	*third_line;
	t_env	*path;
	char	*ptr;

	ptr = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	path = ft_lstnew_env(ptr);
	first_line = ft_lstnew_env("PWD=/Users/souaouri/Desktop/mn_sh");
	second_line = ft_lstnew_env("SHLVL=1");
	third_line = ft_lstnew_env("_=/usr/bin/env");
	ft_lstadd_back_env(env, first_line);
	ft_lstadd_back_env(env, second_line);
	ft_lstadd_back_env(env, third_line);
	ft_lstadd_back_env(env, path);
}

void	write_env(t_env *env)
{
	int		i;
	int		size;

	size = ft_lstsize_env(env);
	i = 1;
	if (size == 5)
		size--;
	while (env && size--)
	{
		if (ft_strchr(env->content, '='))// && ft_strncmp(env->content, "?", 1))
		{
			ft_putstr_fd(env->content, 1);
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
}
