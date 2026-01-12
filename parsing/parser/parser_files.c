/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:36:03 by mal-mora          #+#    #+#             */
/*   Updated: 2024/08/04 00:18:14 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	show_file_error(int fd, int to, char *s, t_cmds **cmds)
{
	if (fd == -1 && to == redirect_out)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": Error in open file", 2);
		ft_putstr_fd("\n", 2);
		(*cmds)->is_error = 1;
	}
	else if (fd == -1 && (to == redirect_in || to == redirect_app))
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": No such file or directory", 2);
		ft_putstr_fd("\n", 2);
		(*cmds)->is_error = 1;
	}
}

int	check_files_error(t_cmds **cm)
{
	if (cm && *cm)
	{
		if ((*cm)->in_file == -1 || (*cm)->aout_file == -1 || \
			(*cm)->out_file == -1)
			return (1);
	}
	return (0);
}

int	open_files_after_check(int token, char *mfile)
{
	int	fd;

	if (token == redirect_out)
		fd = open(mfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (token == redirect_in)
		fd = open(mfile, O_RDONLY, 0644);
	if (token == redirect_app)
		fd = open(mfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	return (fd);
}

int	open_files(t_lexer **lexer, t_token token, t_cmds **cmds, t_env **env)
{
	t_lexer	tmp2;
	int		fd;
	t_lexer	*tmp;

	(*lexer) = (*lexer)->next;
	tmp = *lexer;
	while ((*lexer) && fd != -1 && ((*lexer)->token == file \
		|| (*lexer)->token == token))
	{
		if ((*lexer)->token == file)
		{
			(1) && (tmp2.str = ft_strdup((*lexer)->str),
					tmp2.expanded = (*lexer)->expanded);
			if (tmp2.str && (!*tmp2.str && tmp2.expanded))
			{
				(*cmds)->is_ambugious = 1;
				return (error_msg(AMBIGUOUS_REDIRECT, env), -1);
			}
			fd = open_files_after_check(token, tmp2.str);
			if (!check_files_error(cmds))
				show_file_error(fd, token, tmp->str, cmds);
		}
		(*lexer) = (*lexer)->next;
	}
	return (fd);
}

int	handel_files(t_lexer **tmp, t_cmds *cmds, t_env **env)
{
	int	res;

	res = 0;
	if (*tmp && (*tmp)->token == redirect_in)
		cmds->in_file = open_files(tmp, redirect_in, &cmds, env);
	else if (*tmp && (*tmp)->token == redirect_out)
		cmds->out_file = open_files(tmp, redirect_out, &cmds, env);
	else if (*tmp && (*tmp)->token == heredoc)
	{
		res = save_heredoc(tmp, &cmds, env);
		if (res == -2)
			return (-1);
		cmds->heredoc = res;
	}
	else if (*tmp && (*tmp)->token == redirect_app)
		cmds->aout_file = open_files(tmp, redirect_app, &cmds, env);
	while (*tmp && (*tmp)->token != mpipe)
		*tmp = (*tmp)->next;
	return (res);
}
