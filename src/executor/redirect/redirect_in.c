/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:28:30 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/18 00:15:29 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	check_file_access(char *file)
{
	struct stat	st;

	if (stat(file, &st) == -1)
		return (print_error(file, NULL, "No such file or directory"), -1);
	if (S_ISDIR(st.st_mode))
		return (print_error(file, NULL, "Is a directory"), -1);
	if (access(file, R_OK) == -1)
		return (print_error(file, NULL, "Permission denied"), -1);
	return (0);
}

int	apply_input_redirect(char *file)
{
	int	fd;

	if (check_file_access(file) == -1)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (print_error(file, NULL, strerror(errno)), -1);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (print_error("dup2", NULL, strerror(errno)), -1);
	}
	close(fd);
	return (0);
}

static int	handle_input_type(t_redirect *redir)
{
	if (redir->type == TOKEN_REDIRECT_IN)
		return (apply_input_redirect(redir->file));
	else if (redir->type == TOKEN_HEREDOC)
		return (handle_heredoc(redir->file));
	return (0);
}

int	setup_input_redirect(t_command *cmd)
{
	t_redirect	*redir;

	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == TOKEN_REDIRECT_IN || redir->type == TOKEN_HEREDOC)
		{
			if (handle_input_type(redir) == -1)
			{
				print_error("Redirection input failed", redir->file, NULL);
				return (-1);
			}
		}
		redir = redir->next;
	}
	return (0);
}
