/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:52:09 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/19 17:42:11 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	is_builtin(char *cmd)
{
   return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
   	|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
   	|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
   	|| !ft_strcmp(cmd, "exit"));
}

static int	handle_redirections(t_command *cmd)
{
   if (setup_input_redirect(cmd) == -1)
   	return (-1);
   if (setup_output_redirect(cmd) == -1)
   	return (-1);
   return (0);
}

int	execute_builtin(t_shell *shell, t_command *cmd)
{
	char	*command;

	if (!cmd->args[0])
		return (1);
	command = cmd->args[0];
	/*printf("DEBUG: executing builtin: %s\n", command); // Debug*/
	
	if (!ft_strcmp(command, "echo"))
		return (ft_echo(cmd->args));
	if (!ft_strcmp(command, "cd"))
		return (ft_cd(shell, cmd->args));
	if (!ft_strcmp(command, "pwd"))
		return (ft_pwd(shell));
	if (!ft_strcmp(command, "export"))
		return (ft_export(shell, cmd->args));
	if (!ft_strcmp(command, "unset"))
		return (ft_unset(shell, cmd->args));
	if (!ft_strcmp(command, "env"))
		return (ft_env(shell));
	if (!ft_strcmp(command, "exit"))
		return (ft_exit(shell, cmd->args));
	return (1);
}

int	execute_external(t_shell *shell, t_command *cmd)
{
   char	*path;
   pid_t	pid;
   int		status;

   path = find_command_path(cmd->args[0], shell->env_array);
   if (!path)
   	return (handle_cmd_error(shell, cmd->args[0], ENOENT), 127);
   pid = fork();
   if (pid == -1)
   	return (handle_system_error(shell, "fork failed"), 1);
   if (pid == 0)
   {
   	execve(path, cmd->args, shell->env_array);
   	exit(127);
   }
   free(path);
   waitpid(pid, &status, 0);
   return (get_exit_status(status));
}

int	execute_command(t_shell *shell, t_command *cmd)
{
	int	status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	/*printf("DEBUG: Executing command: %s\n", cmd->args[0]); // Debug*/
	status = handle_redirections(cmd);
	if (status == -1)
		return (1);
	if (is_builtin(cmd->args[0]))
	{
		/*printf("DEBUG: Is a builtin\n"); // Debug*/
		return (execute_builtin(shell, cmd));
	}
	/*printf("DEBUG: Is external command\n"); // Debug*/
	return (execute_external(shell, cmd));
}
