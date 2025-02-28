/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: d9125 <d9125@me.com>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:00:00 by d9125             #+#    #+#           */
/*   Updated: 2024/03/19 11:30:00 by d9125            ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "env.h"
#include "shell_ctx.h"
#include "libft.h"
#include "utils.h"

static void	exec_error(char *cmd, char *msg)
{
	ft_putstr_fd((char *)cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

int	exec_builtin(t_command *cmd, t_shell_ctx *ctx)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (-1);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd->args));
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(cmd->args, ctx));
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(cmd->args, ctx->env));
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(cmd->args, ctx->env));
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(ctx->env));
	if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		return (ft_exit(cmd->args));
	}
	return (-1);
}

int	exec_single_command(t_command *cmd, t_shell_ctx *ctx)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**env;
	int		ret;
	t_fd_backup	*backup;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);

	// Si c'est une commande builtin, l'exécuter directement avec redirections
	if (is_builtin(cmd->args[0]))
	{
		// Sauvegarder les descripteurs de fichiers standard
		backup = save_fds();
		if (!backup)
			return (1);

		// Configurer les redirections
		if (setup_redirections(cmd, ctx) != 0)
		{
			restore_fds(backup);
			return (1);
		}

		// Exécuter la commande builtin
		ret = exec_builtin(cmd, ctx);

		// Restaurer les descripteurs de fichiers standard
		restore_fds(backup);
		return (ret);
	}

	// Pour les commandes externes, créer un processus enfant
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("minishell: fork failed\n", STDERR_FILENO);
		return (1);
	}

	if (pid == 0)
	{
		// Processus enfant
		reset_signals_for_child();

		// Configurer les redirections
		if (setup_redirections(cmd, ctx) != 0)
			exit(1);

		path = find_command_path(cmd->args[0], ctx);
		if (!path)
		{
			exec_error(cmd->args[0], "command not found");
			exit(127);
		}

		env = env_to_array(ctx->env);
		if (!env)
		{
			free(path);
			exit(1);
		}

		execve(path, cmd->args, env);
		// Si on arrive ici, c'est que execve a échoué
		exec_error(cmd->args[0], "execution failed");
		free(path);
		free_dbl_tab(env);
		exit(126);
	}

	// Processus parent
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));

	return (1);
}

int	execute_commands(t_command **commands, int cmd_count, t_shell_ctx *ctx)
{
	t_exec	exec;
	int		status;
	int		real_cmd_count;

	if (!commands || !*commands)
		return (1);

	// Vérifier si c'est une pipeline et compter les commandes réelles
	if ((*commands)->type == CMD_PIPELINE)
	{
		real_cmd_count = count_command_list((*commands)->commands);

		// Pour les pipelines, utiliser spawn_processes
		exec.cmds = (*commands)->commands;
		exec.cmd_count = real_cmd_count;
		exec.pids = ft_calloc(real_cmd_count, sizeof(pid_t));
		if (!exec.pids)
			return (1);
		exec.pipes = NULL;
		exec.fd_backup = NULL;
		exec.last_exit_code = 0;
		exec.ctx = ctx;

		status = spawn_processes(&exec, real_cmd_count);
	}
	else
	{
		// Pour toutes les commandes simples, utiliser exec_single_command
		exec.cmds = *commands;
		exec.cmd_count = cmd_count;
		exec.pids = ft_calloc(cmd_count, sizeof(pid_t));
		if (!exec.pids)
			return (1);
		exec.pipes = NULL;
		exec.fd_backup = NULL;
		exec.last_exit_code = 0;
		exec.ctx = ctx;

		if (cmd_count == 1)
			status = exec_single_command(*commands, ctx);
		else
			status = spawn_processes(&exec, cmd_count);
	}

	free(exec.pids);
	return (status);
}

char	*find_command_path(char *cmd, t_shell_ctx *ctx)
{
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	return (path_finder(cmd, ctx->env));
}
