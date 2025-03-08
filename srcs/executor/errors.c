/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:59:34 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"
#include <string.h>

// stores copy of STDOUT
// redirects STDOUT to STDERR
// printf can now write in STDERR
// restores STDOUT
// free the copy
void	err_open(int err_no, char *file)
{
	int	temp_fd;

	temp_fd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s: %s: %s\n", PROMPT_NAME, file, strerror(err_no));
	dup2(temp_fd, STDOUT_FILENO);
	exe_close(&(temp_fd));
}

// dup2 so printf can write in stderr
// open_pipes already closed fds if error
int	err_pipe(int err_no, t_shell *ctx)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s: %s\n", PROMPT_NAME, strerror(err_no));
	set_std(ctx, 1);
	ctx->exit_code = 2;
	return (2);
}

int	err_fork(int err_no, t_shell *ctx, int fd[][2])
{
	int	pipe_nb;
	int	fork_success;

	pipe_nb = ctx->pid_count - 1;
	fork_success = ctx->pid_count;
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s: %s\n", PROMPT_NAME, strerror(err_no));
	close_all(pipe_nb, fd);
	set_std(ctx, 1);
	wait_children(fork_success, ctx);
	ctx->exit_code = 2;
	return (2);
}

// if child process terminated by signal
void	exe_err_coredump(int pid)
{
	int	fd_backup;

	fd_backup = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("[%d]: Quit (core dumped)\n", pid);
	dup2(fd_backup, STDOUT_FILENO);
	exe_close(&fd_backup);
}

// stat(path, &stats) !stores information abour path in stat
// returns -1 if no exist or permission denied
// S_ISDIR(stats.st_mode) == 1 if its directory
void	err_execve(char *path, int err_no)
{
	int			fd_tmp;
	struct stat	stats;

	fd_tmp = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (err_no == ENOENT && !strchr(path, '/'))
		printf("%s: %s: command not found\n", PROMPT_NAME, path);
	else if (err_no == ENOENT)
		printf("%s: %s: No such file or directory\n", PROMPT_NAME, path);
	else if (stat(path, &stats) != -1)
	{
		if (S_ISDIR(stats.st_mode) == 1)
			printf("%s: %s: Is a directory\n", PROMPT_NAME, path);
		else if (err_no == EACCES)
			printf("%s: %s: Permission denied\n", PROMPT_NAME, path);
		else
			printf("%s: %s: %s\n", PROMPT_NAME, path, strerror(err_no));
	}
	else
		printf("%s: %s: No such file or directory\n", PROMPT_NAME, path);
	dup2(fd_tmp, STDOUT_FILENO);
	exe_close(&(fd_tmp));
}
