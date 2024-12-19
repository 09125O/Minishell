/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:27:59 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/19 17:50:12 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	restore_std_fds(int saved_fds[2])
{
	dup2(saved_fds[0], STDIN_FILENO);
	dup2(saved_fds[1], STDOUT_FILENO);
	close(saved_fds[0]);
	close(saved_fds[1]);
}

static int	save_std_fds(int saved_fds[2])
{
	saved_fds[0] = dup(STDIN_FILENO);
	saved_fds[1] = dup(STDOUT_FILENO);
	if (saved_fds[0] == -1 || saved_fds[1] == -1)
		return (0);
	return (1);
}

int	execute_ast(t_shell *shell, t_ast *ast)
{
	int	status;
	int	saved_fds[2];

	if (!ast || !ast->cmd || !ast->cmd->args || !ast->cmd->args[0])
	{
		printf("DEBUG: Invalid AST structure\n");
		return (1);
	}
	if (!save_std_fds(saved_fds))
		return (1);
	if (!ast->right)
		status = execute_command(shell, ast->cmd);
	else
		status = execute_pipeline(shell, ast);
	restore_std_fds(saved_fds);
	return (status);
}