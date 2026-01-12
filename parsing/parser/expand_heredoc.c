/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:48:18 by mal-mora          #+#    #+#             */
/*   Updated: 2024/08/02 10:05:28 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*handel_hd(char *result, char *s, t_int *sin_t, t_env **env_list)
{
	int		k;
	char	*res;

	k = (++sin_t->i);
	while (s[sin_t->i])
	{
		if (s[sin_t->i] == DOUBLE_QUOTE)
		{
			res = ft_substr(s, k, sin_t->j);
			if (!res)
				return (NULL);
			if (str_chr(res, '$') != -1)
				result = ft_strjoin(result, expand_str(res, env_list));
			else
				result = ft_strjoin(result, res);
			break ;
		}
		(sin_t->j)++;
		(sin_t->i)++;
	}
	return (result);
}

int	handel_ctr(int fd_in, t_cmds **cmds)
{
	close(fd_in);
	if (cmds && *cmds)
		(*cmds)->stop_ex = 0;
	return (-2);
}

char	*handel_d_q_here2(char *result, char *s, t_int *sin_t, t_env **env)
{
	int		k;
	char	*res;

	k = (++sin_t->i);
	while (s[sin_t->i])
	{
		if (s[sin_t->i] == SINGLE_QUOTE)
		{
			res = ft_substr(s, k, sin_t->j);
			if (!res)
				return (NULL);
			if (str_chr(res, '$') != -1)
				result = ft_strjoin(result, expand_str(res, env));
			else
				result = ft_strjoin(result, res);
			break ;
		}
		(sin_t->j)++;
		(sin_t->i)++;
	}
	return (result);
}

char	*handel_expand_quotes_here(t_int *is, char *s, char **res, t_env **env)
{
	if (s[is->i] == DOUBLE_QUOTE)
		*res = handel_hd(*res, s, is, env);
	else
		*res = handel_d_q_here2(*res, s, is, env);
	return (*res);
}

char	*expanding_str_here(char *s, t_env **env)
{
	char	*res;
	t_int	*ints;

	ints = init_ints();
	res = NULL;
	while (s[ints->i])
	{
		ints->j = 0;
		if (is_quotes(s[ints->i]))
			(res = handel_expand_quotes_here(ints, s, &res, env));
		else if (s[ints->i] == '$' && (!s[ints->i + 1] || \
		(!is_real_char(s, ints->i + 1) && !is_quotes(s[ints->i + 1]))))
			res = ft_strjoin(res, ft_substr(&s[ints->i], 0, 1));
		else if (s[ints->i] == '$')
			(1) && (res = ft_strjoin(res, al_exp(s + (++(ints->i)),
			&ints->i, env)), ints->i--);
		else
			res = ft_strjoin(res, ft_substr(&s[ints->i], 0, 1));
		if (res == NULL)
			return (ft_strdup(""));
		ints->i++;
	}
	return (res);
}
