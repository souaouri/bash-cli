/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:59:50 by mal-mora          #+#    #+#             */
/*   Updated: 2024/08/04 09:45:47 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	allocation_error(char *s)
{
	free(s);
	printf(ERROR_IN_ALLOCATION);
	exit(0);
}

void	modify_exit_status(int nbr, t_env **env_list)
{
	char	*ex_st;

	ex_st = ft_strjoin("?=", ft_itoa(nbr));
	add_variable(*env_list, ex_st, 1);
}

void	error_msg(char *s, t_env **env_list)
{
	if (!ft_strcmp(s, SYNTAX_ERROR))
		modify_exit_status(258, env_list);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
}

void	free_lexer(t_lexer *lexer)
{
	t_lexer	*tmp;

	while (lexer)
	{
		tmp = lexer;
		lexer = lexer->next;
		free(tmp);
	}
}
