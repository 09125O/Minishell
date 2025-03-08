/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"

static int	handle_single_redir(t_shell *ctx, t_exec *temp)
{
	if (err_redirs(temp, ctx))
	{
		ctx->exit_code = 1;
		return (ctx->exit_code);
	}
	unlink_all(ctx);
	set_std(ctx, 1);
	return (0);
}

static int	handle_single_builtin(t_shell *ctx, t_exec *temp)
{
	if (err_redirs(temp, ctx))
	{
		ctx->exit_code = 1;
		return (ctx->exit_code);
	}
	if (check_is_builtin(temp->cmd) == 2)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	unlink_all(ctx);
	ctx->exit_code = exec_builtin(ctx, temp->cmd, temp->args);
	set_std(ctx, 1);
	return (ctx->exit_code);
}

// store STDIN & STDOUT
// 1 command and its a builtin (no loop)
// if errors in redirections, exit
// unlink (close) all the N_HEREDOC(unlink in the else also)
int	exec(t_shell *ctx)
{
	t_exec	*temp;

	if (ctx->exec_count == 0)
		return (0);
	set_std(ctx, 0);
	temp = ctx->exec;
	if (ctx->exec_count == 1)
	{
		if (temp->cmd == NULL && temp->redirs != NULL)
			return (handle_single_redir(ctx, temp));
		if (check_is_builtin(temp->cmd))
			return (handle_single_builtin(ctx, temp));
	}
	exec_parent(ctx);
	return (0);
}
