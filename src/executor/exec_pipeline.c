/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:06:52 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/19 17:43:41 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	count_commands(t_ast *pipeline)
{
	int	count;

	count = 1;
	while (pipeline->right)
	{
		count++;
		pipeline = pipeline->right;
	}
	return (count);
}

static void	close_all_pipes(t_pipe *pipes, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		close_pipe(&pipes[i]);
		i++;
	}
}

static void	create_child_processes(t_shell *shell, t_ast *pipeline,
		t_process *proc, t_pipe *pipes)
{
	int		i;
	t_ast	*current;
	int		cmd_count;

	i = 0;
	current = pipeline;
	cmd_count = count_commands(pipeline);
	while (current && current->cmd)
	{
		if (cmd_count == 1)
			proc[i].pid = execute_command(shell, current->cmd);
		else if (i == 0)
			proc[i].pid = create_process(shell, current->cmd, NULL, &pipes[0]);
		else if (i == cmd_count - 1)
			proc[i].pid = create_process(shell, current->cmd, &pipes[i - 1],
				NULL);
		else
			proc[i].pid = create_process(shell, current->cmd, &pipes[i - 1],
				&pipes[i]);
		current = current->right;
		i++;
	}
}

int	execute_pipeline(t_shell *shell, t_ast *pipeline)
{
	t_pipe		*pipes;
	t_process	*processes;
	int			cmd_count;
	int			status;

	if (!pipeline || !pipeline->cmd)
		return (1);
	/*printf("DEBUG: Pipeline command: %s\n", pipeline->cmd->args[0]); // Debug*/
	cmd_count = count_commands(pipeline);
	/*printf("DEBUG: Command count: %d\n", cmd_count); // Debug*/
	if (cmd_count == 1 && pipeline->cmd->args[0])
	{
		/*printf("DEBUG: Single command detected\n"); // Debug*/
		if (is_builtin(pipeline->cmd->args[0]))
		{
			/*printf("DEBUG: Executing builtin directly\n"); // Debug*/
			return (execute_command(shell, pipeline->cmd));
		}
	}
	processes = ft_calloc(cmd_count, sizeof(t_process));
	pipes = ft_calloc(cmd_count - 1, sizeof(t_pipe));
	if (!processes || !pipes)
		return (free(processes), free(pipes), 1);
	if (create_pipes(pipes, cmd_count - 1) == -1)
		return (free(processes), free(pipes), 1);
	create_child_processes(shell, pipeline, processes, pipes);
	close_all_pipes(pipes, cmd_count);
	status = wait_processes(processes, cmd_count);
	free(processes);
	free(pipes);
	return (status);
}
