/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:04:10 by souaouri          #+#    #+#             */
/*   Updated: 2024/08/03 02:00:13 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	unset(t_env **list_env, char *arg)
{
	t_env	*tmp;
	char	*str;

	if (!list_env || !*list_env || !arg)
		return (0);
	if ((check_arg_is_valide(arg) || check_for_first_char(arg)))
		return (builtins_print_error(arg, "pars__export"));
	tmp = *list_env;
	str = get_env_eq(tmp->content);
	if (!ft_strcmp(str, arg))
	{
		*list_env = tmp->next;
		free(tmp);
	}
	else
		unset(&(*list_env)->next, arg);
	return (0);
}
