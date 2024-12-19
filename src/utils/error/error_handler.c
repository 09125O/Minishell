/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:58:10 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/17 11:33:19 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	handle_cmd_error(t_shell *shell, const char *cmd, int err_code)
{
	if (err_code == ENOENT)
		print_command_error(cmd, "command not found");
	else if (err_code == EACCES)
		print_command_error(cmd, "permission denied");
	else if (err_code == EISDIR)
		print_command_error(cmd, "is a directory");
	shell->exit_status = 127;
}

void	handle_system_error(t_shell *shell, const char *msg)
{
	print_error(NULL, NULL, msg);
	shell->exit_status = 1;
}

int	set_error_code(t_shell *shell, int code)
{
	shell->exit_status = code;
	return (code);
}
