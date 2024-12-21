/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhour <obouhour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:36:49 by obouhour          #+#    #+#             */
/*   Updated: 2024/12/21 16:43:20 by obouhour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	open_file(const char *file, int flags, mode_t mode)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd < 0)
	{
		perror("minishell: error opening file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	handle_redirection(t_redirection *redir)
{
	int	fd;

	if (!redir)
		return ;
	if (redir->input_file)
	{
		fd = open_file(redir->input_file, O_RDONLY, 0);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (redir->output_file)
	{
		fd = open_file(redir->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (redir->append_file)
	{
		fd = open_file(redir->append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
