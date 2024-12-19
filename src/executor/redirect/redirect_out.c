/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:53:25 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/17 16:25:42 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	check_file_permissions(char *file)
{
	struct stat	st;

	if (stat(file, &st) != -1 && S_ISDIR(st.st_mode))
		return (print_error(file, NULL, "Is a directory"), -1);
	if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
		return (print_error(file, NULL, "Permission denied"), -1);
	return (0);
}

int	apply_output_redirect(char *file, int append)
{
	int	flags;
	int	fd;

	if (check_file_permissions(file) == -1)
		return (-1);
	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(file, flags, 0644);
	if (fd == -1)
		return (print_error(file, NULL, strerror(errno)), -1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (print_error("dup2", NULL, strerror(errno)), -1);
	}
	close(fd);
	return (0);
}

int	setup_output_redirect(t_command *cmd)
{
	t_redirect	*redir;
	int			append;

	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == TOKEN_REDIRECT_OUT || redir->type == TOKEN_APPEND)
		{
			append = (redir->type == TOKEN_APPEND);
			if (apply_output_redirect(redir->file, append) == -1)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}
