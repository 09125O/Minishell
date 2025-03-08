/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_family.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"

static int	handle_redir_and_bltins(t_shell *ctx, t_exec *temp, int *exit_code)
{
	if (err_redirs(temp, ctx))
	{
		free_all_shell(ctx);
		ctx->exit_code = 1;
		*exit_code = ctx->exit_code;
		return (1);
	}
	if (check_is_builtin(temp->cmd))
	{
		*exit_code = exec_builtin(ctx, temp->cmd, temp->args);
		free_all_shell(ctx);
		return (1);
	}
	return (0);
}

static void	setup_redir(t_shell *ctx, int (*fd)[2], int i)
{
	signal(SIGQUIT, SIG_DFL);
	if (ctx->exec_count > 1)
	{
		if (i > 0)
		{
			dup2(fd[i - 1][0], STDIN_FILENO);
			exe_close(&fd[i - 1][0]);
		}
		if (i < ctx->exec_count - 1)
		{
			dup2(fd[i][1], STDOUT_FILENO);
			exe_close(&fd[i][1]);
		}
		close_fds(ctx->exec_count - 1, fd, i, false);
	}
	ft_close(ctx);
}

// we can exit here because we are in a child process
void	child_process(t_shell *ctx, int (*fd)[2], int i, t_exec *temp)
{
	int	exit_code;

	exit_code = 0;
	setup_redir(ctx, fd, i);
	if (handle_redir_and_bltins(ctx, temp, &exit_code))
	{
		exit(exit_code);
	}
	exit_code = ft_execution(ctx, temp);
	free_all_shell(ctx);
	if (exit_code == 127)
		exit(127);
	else if (exit_code == 126)
		exit(126);
	else if (exit_code != 0)
		exit(1);
	exit(0);
}

// MAX_FDS : The default limit for file descriptors (ulimit -n -> 1024)
int	exec_parent(t_shell *ctx)
{
	t_exec	*temp;
	int		fd[MAX_FDS][2];
	pid_t	pid;

	temp = ctx->exec;
	if (open_pipes(ctx->exec_count - 1, fd) == -1)
		return (err_pipe(errno, ctx));
	while (temp)
	{
		signal(SIGINT, sigint_exec);
		pid = fork();
		if (pid == -1)
			return (err_fork(errno, ctx, fd));
		else if (pid == 0)
			child_process(ctx, fd, ctx->pid_count, temp);
		ctx->pids[ctx->pid_count] = pid;
		ctx->pid_count++;
		temp = temp->next;
	}
	close_all(ctx->exec_count - 1, fd);
	set_std(ctx, 1);
	wait_children(ctx->pid_count, ctx);
	return (0);
}
