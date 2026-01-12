/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utile_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:39:51 by souaouri          #+#    #+#             */
/*   Updated: 2024/08/04 02:00:10 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_var_does_it_exist(char *arg, t_env *list_env)
{
	char	*var;

	var = get_var_from_beg_to_eq(arg);
	while (list_env)
	{
		if (ft_strncmp(list_env->content, var, ft_strlen(var)) == 0)
			return (1);
		list_env = list_env->next;
	}
	return (0);
}

int	check_arg_is_valide(char *arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		if ((arg[i] >= '0' && arg[i] <= '9')
			|| (arg[i] >= 'a' && arg[i] <= 'z')
			|| (arg[i] >= 'A' && arg[i] <= 'Z')
			|| arg[i] == '_')
			i++;
		else
			break ;
	}
	if (arg[i])
		return (1);
	return (0);
}

int	check_for_first_char(char *arg)
{
	if ((arg[0] >= 'a' && arg[0] <= 'z')
		|| (arg[0] >= 'A' && arg[0] <= 'Z')
		|| arg[0] == '_')
		return (0);
	else
		return (1);
}

char	*get_env_eq(char *new)
{
	char	*ptr;
	int		i;

	i = 0;
	while (new && new[i] && new[i] != '=')
		i++;
	ptr = my_alloc(i + 1, 0);
	if (!ptr)
		return (NULL);
	i = 0;
	while (new && new[i])
	{
		if (new[i] != '=')
			ptr[i] = new[i];
		else if (new[i] == '=')
			break ;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	check_var(char	*cmd, t_env *list_env)
{
	if (!ft_strchr(cmd, '='))
	{
		if (if_var_exist_return(cmd, list_env))
			return (0);
	}
	return (1);
}
