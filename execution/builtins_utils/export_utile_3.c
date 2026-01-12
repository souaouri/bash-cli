/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utile_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:39:57 by souaouri          #+#    #+#             */
/*   Updated: 2024/08/04 02:00:20 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_lstsize_env(t_env *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

static	int	is_valid(char *arg)
{
	int	i;

	i = 0;
	while (arg[i + 1])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	check_for_plus_and_eq(char *arg, int w)
{
	int		i;
	char	*first_part;

	i = 0;
	first_part = get_var_from_beg_to_eq(arg);
	if (is_valid(arg))
		i = -1;
	if ((check_arg_is_valide(first_part)
			|| check_for_first_char(first_part)) && i == -1)
	{
		if (w == 1)
		{
			builtins_print_error(arg, "pars_export");
			return (-1);
		}
	}
	if (is_valid(arg))
		return (1);
	return (0);
}

char	*remove_plus(char *new)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	ptr = my_alloc(ft_strlen(new) + 1, 0);
	while (new[i])
	{
		if (new[i] != '+')
		{
			ptr[j] = new[i];
			j++;
		}
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*find_var(t_env *list_env, char	*var)
{
	while (list_env)
	{
		if (ft_strncmp(list_env->content, var, ft_strlen(var)) == 0)
		{
			return (list_env->content);
		}
		list_env = list_env->next;
	}
	return (NULL);
}
