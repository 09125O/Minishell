/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:36:49 by obouhour          #+#    #+#             */
/*   Updated: 2025/02/26 00:38:46 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <fcntl.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

static int	open_file(const char *file, int flags, t_shell_ctx *ctx)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd == -1)
	{
		set_shell_error(ctx, E_REDIRECTION, "erreur d'ouverture du fichier");
		return (-1);
	}
	return (fd);
}

static int	setup_redirection(int fd, int target_fd, t_shell_ctx *ctx)
{
	if (dup2(fd, target_fd) == -1)
	{
		set_shell_error(ctx, E_REDIRECTION, "erreur de redirection");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static void	read_heredoc_input(int fd, const char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

int	handle_heredoc(const char *delimiter, t_shell_ctx *ctx)
{
	int		pipe_fd[2];
	int		saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
	{
		set_shell_error(ctx, E_REDIRECTION, "erreur de sauvegarde stdin");
		return (-1);
	}
	if (pipe(pipe_fd) == -1)
	{
		set_shell_error(ctx, E_PIPE_CREATION, "erreur de création du pipe");
		close(saved_stdin);
		return (-1);
	}
	read_heredoc_input(pipe_fd[PIPE_WRITE], delimiter);
	close(pipe_fd[PIPE_WRITE]);
	if (setup_redirection(pipe_fd[PIPE_READ], STDIN_FILENO, ctx) == -1)
	{
		close(pipe_fd[PIPE_READ]);
		close(saved_stdin);
		return (-1);
	}
	return (saved_stdin);
}

static int	handle_input_redir(t_redirection *redir, t_shell_ctx *ctx)
{
	int	fd;

	fd = open_file(redir->file, O_RDONLY, ctx);
	if (fd == -1)
		return (-1);
	return (setup_redirection(fd, STDIN_FILENO, ctx));
}

static int	handle_output_redir(t_redirection *redir, t_shell_ctx *ctx)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	flags |= (redir->type == REDIR_APPEND) ? O_APPEND : O_TRUNC;
	fd = open_file(redir->file, flags, ctx);
	if (fd == -1)
		return (-1);
	return (setup_redirection(fd, STDOUT_FILENO, ctx));
}

int	handle_redirection(t_redirection *redir, t_shell_ctx *ctx)
{
	int	ret;

	if (!redir)
		return (0);
	while (redir)
	{
		if (redir->type == REDIR_IN)
			ret = handle_input_redir(redir, ctx);
		else if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
			ret = handle_output_redir(redir, ctx);
		else if (redir->type == REDIR_HEREDOC)
			ret = (handle_heredoc(redir->file, ctx) == -1) ? -1 : 0;
		else
			ret = 0;
		if (ret == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}

int	setup_redirections(t_command *cmd, t_shell_ctx *ctx)
{
	if (!cmd)
		return (0);

	// Utiliser handle_redirection pour configurer les redirections
	if (handle_redirection(cmd->redirections, ctx) == -1)
	{
		ft_putstr_fd("minishell: erreur de redirection\n", STDERR_FILENO);
		return (1);
	}

	return (0);
}

int	restore_redirections(void)
{
	t_fd_backup	*backup;

	backup = save_fds();
	if (!backup)
		return (1);

	restore_fds(backup);
	return (0);
}
