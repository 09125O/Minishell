/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:06:52 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/19 11:10:48 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	init_pipes(t_pipe *pipes, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		pipes[i].read_fd = -1;
		pipes[i].write_fd = -1;
		i++;
	}
}

int	create_pipes(t_pipe *pipes, int count)
{
	int	i;
	int	pipefd[2];

	i = 0;
	while (i < count - 1)
	{
		if (pipe(pipefd) == -1)
		{
			while (--i >= 0)
			{
				close(pipes[i].read_fd);
				close(pipes[i].write_fd);
			}
			return (-1);
		}
		pipes[i].read_fd = pipefd[0];
		pipes[i].write_fd = pipefd[1];
		i++;
	}
	return (0);
}

int	setup_pipeline(t_process *proc, t_pipe *pipes, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		if (i > 0)
			proc[i].pipe_in = pipes[i - 1].read_fd;
		else
			proc[i].pipe_in = -1;
		if (i < cmd_count - 1)
			proc[i].pipe_out = pipes[i].write_fd;
		else
			proc[i].pipe_out = -1;
		proc[i].pid = -1;
		proc[i].status = 0;
		i++;
	}
	return (0);
}
