/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:49:51 by mal-mora          #+#    #+#             */
/*   Updated: 2024/08/03 22:01:25 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	read_herdoc(char *del, char *line, int fd_in, t_env **env)
{
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, del) == 0)
		{
			free(line);
			break ;
		}
		if (str_chr(line, '$') != -1)
			line = ft_strdup(expanding_str_here(line, env));
		ft_putstr_fd(line, fd_in);
		ft_putstr_fd("\n", fd_in);
		free(line);
	}
}

static void	handel_hd_child(char *del, char *line, int fd_in, t_env **env)
{
	signal(SIGINT, SIG_DFL);
	rl_catch_signals = 1;
	read_herdoc(del, line, fd_in, env);
	(close(fd_in), exit(0));
}

int	handel_heredoc(char *del, t_cmds **cmds, t_env **env)
{
	int		fd_in;
	char	*line;
	int		pid;
	int		exit_status;

	line = NULL;
	pid = fork();
	fd_in = open("/tmp/test.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pid == -1)
		return (perror("Error forking process"), -1);
	else if (pid == 0)
		handel_hd_child(del, line, fd_in, env);
	else
	{
		wait(&exit_status);
		if (WIFSIGNALED(exit_status) && WTERMSIG(exit_status) == SIGINT)
			return (handel_ctr(fd_in, cmds));
	}
	close(fd_in);
	fd_in = open("/tmp/test.txt", O_RDONLY, 0644);
	return (fd_in);
}

int	handel_if_file(t_lexer ***lexer, int fd)
{
	while (**lexer && (**lexer)->token != mpipe)
		(**lexer) = (**lexer)->next;
	return (fd);
}

int	save_heredoc(t_lexer **lexer, t_cmds **cmds, t_env **env)
{
	int		len;
	char	*del;
	int		fd;

	len = 0;
	del = NULL;
	(*lexer) = (*lexer)->next;
	while ((*lexer) && ((*lexer)->token == delimiter || \
	(*lexer)->token == heredoc || (*lexer)->token == file))
	{
		if ((*lexer)->token == delimiter)
		{
			del = ft_strdup((*lexer)->str);
			fd = handel_heredoc(del, cmds, env);
			if (!(*cmds)->cmd)
				close(fd);
			if ((*cmds)->stop_ex == 0)
				break ;
		}
		if ((*lexer)->token == file)
			return (handel_if_file(&lexer, fd));
		(*lexer) = (*lexer)->next;
	}
	return (fd);
}
