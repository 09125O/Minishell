/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:06:54 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/18 00:17:03 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	save_io(int *saved)
{
	if ((saved[0] = dup(STDIN_FILENO)) == -1
		|| (saved[1] = dup(STDOUT_FILENO)) == -1)
	{
		perror("dup");
		exit(1);
	}
}

void	restore_io(int *saved)
{
	if (dup2(saved[0], STDIN_FILENO) == -1 || dup2(saved[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(saved[0]);
	close(saved[1]);
}

void	close_pipe(t_pipe *pipe)
{
	if (!pipe)
		return ;
	if (pipe->read_fd != -1)
		close(pipe->read_fd);
	if (pipe->write_fd != -1)
		close(pipe->write_fd);
	pipe->read_fd = -1;
	pipe->write_fd = -1;
}
