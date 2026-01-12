/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:35:55 by mal-mora          #+#    #+#             */
/*   Updated: 2024/08/04 10:05:47 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*al_exp(char *str, int *pos, t_env **env_list)
{
	int		i;
	int		len_env;
	char	*res;
	char	*reset;

	len_env = 0;
	i = 0;
	reset = NULL;
	while (is_real_char(str, i++))
		len_env++;
	i = 0;
	while (!end_of_proccessing(str, i++))
		(*pos)++;
	reset = ft_substr(str, len_env, get_len_ep(str) - len_env);
	if (!*reset)
		reset = NULL;
	res = ft_strjoin(m_get_env(ft_strncpy(str, len_env), env_list), reset);
	if (!ft_strncmp(str, "?", 1) && (!res || (res && !*res)))
		return (ft_strdup("0"));
	if (res == NULL)
		return (ft_strdup(""));
	return (res);
}

char	*expand_str(char *s, t_env **env_list)
{
	int		i;
	int		cnt;
	char	*result;
	char	*befor_dollar;

	result = NULL;
	i = 0;
	if (!init_expand(s, &i, &cnt))
		return (ft_strdup("$"));
	befor_dollar = ft_substr(s, 0, i);
	while (s[i])
	{
		if (s[i] == '$' && !is_real_char(s, i + 1))
		{
			result = ft_strjoin(befor_dollar, ft_substr(&s[i++], 0, 1));
			continue ;
		}
		if (s[i] == '$' && !is_q_withspaces(s[i + 1]) && !cnt)
			result = ft_strjoin(befor_dollar, al_exp(s + (++i), &i, env_list));
		else if (s[i] == '$' && !(cnt) && is_q_withspaces(s[i + 1]))
			result = ft_strjoin(befor_dollar, ft_substr(&s[i++], 0, 1));
		(1) && (result = handel_other_cases(s, &result, &i, env_list), cnt++);
	}
	// free(befor_dollar);
	return (result);
}

char	*expanding_str(t_lexer **tmp, t_env **env)
{
	char	*res;
	char	*s;
	t_int	*ints;

	ints = init_ints();
	s = (*tmp)->str;
	res = NULL;
	while (s[ints->i])
	{
		ints->j = 0;
		if (is_quotes(s[ints->i]))
			(1) && (res = handel_ex_q(ints, tmp, &res, env), (*tmp)->has_q = 1);
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

char	*m_get_env(char *str, t_env **env_list)
{
	t_env	*env;
	char	*res;

	if (str == NULL)
		return (NULL);
	env = *env_list;
	res = NULL;
	while (env)
	{
		if (!ft_strncmp(env->content, str, ft_strlen(str)) && \
		env->content[ft_strlen(str)] == '=')
			res = get_eq_to_fin(env->content);
		env = env->next;
	}
	return (res);
}

void	handel_expanding(t_lexer **lexer, t_env **env_list)
{
	t_lexer	*tmp;
	int		i;

	tmp = *lexer;
	i = 0;
	while (tmp && tmp->str)
	{
		if (check_if_noexpand(&tmp))
		{
			tmp = tmp->next;
			continue ;
		}
		tmp->expanded = 1;
		tmp->has_q = 0;
		expanding_cases(&tmp, env_list);
		if (!tmp->str || (*tmp->str == '\0' && tmp->token == word && \
			tmp->has_q == 0))
		{
			i = tmp->i;
			tmp = tmp->next;
			ft_lst_remove(lexer, i);
		}
		else
			tmp = tmp->next;
	}
}
