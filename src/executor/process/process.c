/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:52:32 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/17 16:18:39 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	setup_child_pipes(t_pipe *in_pipe, t_pipe *out_pipe)
{
   if (in_pipe)
   {
   	dup2(in_pipe->read_fd, STDIN_FILENO);
   	close(in_pipe->read_fd);
   	close(in_pipe->write_fd);
   }
   if (out_pipe)
   {
   	dup2(out_pipe->write_fd, STDOUT_FILENO);
   	close(out_pipe->read_fd);
   	close(out_pipe->write_fd);
   }
}

static int	handle_child_redirections(t_command *cmd)
{
   if (setup_input_redirect(cmd) == -1)
   	exit(1);
   if (setup_output_redirect(cmd) == -1)
   	exit(1);
   return (0);
}

static void	execute_child_command(t_shell *shell, t_command *cmd)
{
   char	*path;

   if (is_builtin(cmd->args[0]))
   {
   	execute_builtin(shell, cmd);
   	exit(shell->exit_status);
   }
   path = find_command_path(cmd->args[0], shell->env_array);
   if (!path)
   	exit(127);
   execve(path, cmd->args, shell->env_array);
   free(path);
   exit(127);
}

void	child_process(t_shell *shell, t_command *cmd, t_pipe *in, t_pipe *out)
{
   setup_child_pipes(in, out);
   handle_child_redirections(cmd);
   execute_child_command(shell, cmd);
}

int	create_process(t_shell *shell, t_command *cmd, t_pipe *in, t_pipe *out)
{
   pid_t	pid;

   pid = fork();
   if (pid == -1)
   	return (-1);
   if (pid == 0)
   	child_process(shell, cmd, in, out);
   return (pid);
}
