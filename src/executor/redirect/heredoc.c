/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:27:22 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/17 16:27:41 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	create_heredoc_pipe(void)
{
   int	pipefd[2];

   if (pipe(pipefd) == -1)
   	return (-1);
   if (dup2(pipefd[0], STDIN_FILENO) == -1)
   {
   	close(pipefd[0]);
   	close(pipefd[1]);
   	return (-1);
   }
   close(pipefd[0]);
   return (pipefd[1]);
}

static void	write_to_heredoc(int fd, char *line)
{
   write(fd, line, ft_strlen(line));
   write(fd, "\n", 1);
   free(line);
}

static int	heredoc_loop(char *delim, int fd)
{
   char	*line;

   while (1)
   {
   	line = readline("> ");
   	if (!line)
   		break ;
   	if (ft_strcmp(line, delim) == 0)
   	{
   		free(line);
   		break ;
   	}
   	write_to_heredoc(fd, line);
   }
   return (0);
}

int	handle_heredoc(char *delim)
{
   int		fd;
   int		status;

   fd = create_heredoc_pipe();
   if (fd == -1)
   	return (-1);
   status = heredoc_loop(delim, fd);
   close(fd);
   return (status);
}

void	cleanup_heredoc(void)
{
   close(STDIN_FILENO);
}
