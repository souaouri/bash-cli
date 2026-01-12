/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:53:57 by mal-mora          #+#    #+#             */
/*   Updated: 2024/08/04 10:02:18 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_q_withspaces(char c)
{
	return (is_withspaces(c) || is_quotes(c));
}

char	*handel_other_cases(char *s, char **result, int *i, t_env **env)
{
	if (s[*i] == '$' && (!is_q_withspaces(s[*i + 1])))
		(*result) = ft_strjoin((*result), al_exp(s + (++(*i)), i, env));
	else if (s[*i] == '$' && is_q_withspaces(s[*i + 1]))
		(*result) = ft_strjoin((*result), ft_substr(&s[(*i)++], 0, 1));
	else
		(*result) = ft_strjoin((*result), ft_substr(&s[(*i)++], 0, 1));
	return (*result);
}

char	*handel_ex_q(t_int *is, t_lexer **t, char **res, t_env **env)
{
	if (!ft_strcmp("\"$\"", (*t)->str))
		return (ft_strdup("$"));
	if ((*t)->str[is->i] == DOUBLE_QUOTE)
	{
		*res = handel_double_q(*res, (*t)->str, is, env);
		(*t)->has_q = 1;
	}
	else
		*res = handel_singleq(*res, (*t)->str, &is->i, &is->j);
	return (*res);
}

t_int	*init_ints(void)
{
	t_int	*ints;

	ints = my_alloc(sizeof(t_int) + 1, 0);
	ints->i = 0;
	return (ints);
}
