/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 12:46:39 by obouhour          #+#    #+#             */
/*   Updated: 2025/02/27 00:04:05 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"
#include "libft.h"
#include "signals.h"
#include <unistd.h>
#include <fcntl.h>

// Déclaration de la fonction exec_error
static void	exec_error(char *cmd, char *msg)
{
	ft_putstr_fd((char *)cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

static int	setup_pipe_input(t_exec *exec, int cmd_index)
{
	if (cmd_index > 0)
	{
		if (dup2(exec->pipes[cmd_index - 1][0], STDIN_FILENO) == -1)
		{
			ft_putstr_fd("minishell: erreur de redirection stdin\n", 2);
			return (0);
		}
	}
	return (1);
}

static int	setup_pipe_output(t_exec *exec, int cmd_index)
{
	if (cmd_index < exec->cmd_count - 1)
	{
		if (dup2(exec->pipes[cmd_index][1], STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("minishell: erreur de redirection stdout\n", 2);
			return (0);
		}
	}
	return (1);
}

static void	close_all_pipes(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->cmd_count - 1)
	{
		close(exec->pipes[i][0]);
		close(exec->pipes[i][1]);
		i++;
	}
}

static void	setup_child_process(t_exec *exec, int cmd_index)
{
	t_command *current_cmd;
	int i;

	// Réinitialiser les gestionnaires de signaux pour le processus enfant
	// pour qu'ils aient le comportement par défaut
	reset_signals_for_child();
	signals_set_state(SIGNAL_CHILD);  // Utiliser l'état SIGNAL_CHILD pour configurer les signaux

	if (!setup_pipe_input(exec, cmd_index) || !setup_pipe_output(exec, cmd_index))
		exit(1);

	close_all_pipes(exec);

	// Trouver la commande correspondant à l'index
	current_cmd = exec->cmds;
	i = 0;
	while (current_cmd && i < cmd_index)
	{
		current_cmd = current_cmd->next;
		i++;
	}

	if (!current_cmd || !current_cmd->args || !current_cmd->args[0])
		exit(0);

	// Configurer les redirections
	if (setup_redirections(current_cmd, exec->ctx) != 0)
		exit(1);

	if (is_builtin(current_cmd->args[0]))
		exit(exec_builtin(current_cmd, exec->ctx));
	else
	{
		char *path = find_command_path(current_cmd->args[0], exec->ctx);
		if (!path)
		{
			exec_error(current_cmd->args[0], "command not found");
			exit(127);
		}

		char **env = env_to_array(exec->ctx->env);
		if (!env)
		{
			free(path);
			exit(1);
		}

		execve(path, current_cmd->args, env);
		// Si on arrive ici, c'est que execve a échoué
		exec_error(current_cmd->args[0], "execution failed");
		free(path);
		free_dbl_tab(env);
		exit(126);
	}
}

int	spawn_processes(t_exec *exec, int cmd_count)
{
	int	i;
	int	status;

	exec->cmd_count = cmd_count;
	exec->pids = malloc(sizeof(pid_t) * cmd_count);
	if (!exec->pids)
		return (-1);
	if (!create_pipes(exec, cmd_count))
	{
		free(exec->pids);
		return (-1);
	}

	i = 0;
	while (i < cmd_count)
	{
		exec->pids[i] = fork();
		if (exec->pids[i] == -1)
		{
			cleanup_pipes(exec);
			while (--i >= 0)
				waitpid(exec->pids[i], NULL, 0);
			free(exec->pids);
			return (-1);
		}
		if (exec->pids[i] == 0)
			setup_child_process(exec, i);
		i++;
	}

	// Fermer tous les pipes dans le processus parent après avoir créé tous les enfants
	close_all_pipes(exec);

	// Libérer la mémoire des pipes
	if (exec->pipes)
	{
		i = 0;
		while (i < exec->cmd_count - 1)
		{
			if (exec->pipes[i])
				free(exec->pipes[i]);
			i++;
		}
		free(exec->pipes);
		exec->pipes = NULL;
	}

	i = 0;
	while (i < cmd_count)
	{
		waitpid(exec->pids[i], &status, 0);
		if (WIFEXITED(status))
			exec->last_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exec->last_exit_code = 128 + WTERMSIG(status);
		i++;
	}

	free(exec->pids);
	exec->pids = NULL;
	return (exec->last_exit_code);
}

void	close_pipes(t_exec *exec)
{
	int	i;

	if (!exec || !exec->pipes)
		return ;
	i = 0;
	while (i < exec->cmd_count - 1)
	{
		if (exec->pipes[i])
		{
			// Vérifier si les descripteurs sont valides avant de les fermer
			if (fcntl(exec->pipes[i][PIPE_READ], F_GETFD) != -1)
				close(exec->pipes[i][PIPE_READ]);
			if (fcntl(exec->pipes[i][PIPE_WRITE], F_GETFD) != -1)
				close(exec->pipes[i][PIPE_WRITE]);
			// Ne pas libérer la mémoire ici, cela sera fait dans cleanup_pipes
		}
		i++;
	}
	// Ne pas libérer exec->pipes ici, cela sera fait dans cleanup_pipes
}

/* Fonctions de gestion des descripteurs de fichiers */
t_fd_backup	*save_fds(void)
{
	t_fd_backup	*backup;

	backup = malloc(sizeof(t_fd_backup));
	if (!backup)
		return (NULL);
	backup->stdin_fd = dup(STDIN_FILENO);
	if (backup->stdin_fd == -1)
	{
		free(backup);
		return (NULL);
	}
	backup->stdout_fd = dup(STDOUT_FILENO);
	if (backup->stdout_fd == -1)
	{
		close(backup->stdin_fd);
		free(backup);
		return (NULL);
	}
	backup->stderr_fd = dup(STDERR_FILENO);
	if (backup->stderr_fd == -1)
	{
		close(backup->stdin_fd);
		close(backup->stdout_fd);
		free(backup);
		return (NULL);
	}
	return (backup);
}

void	restore_fds(t_fd_backup *backup)
{
	if (!backup)
		return ;
	if (backup->stdin_fd != -1)
	{
		dup2(backup->stdin_fd, STDIN_FILENO);
		close(backup->stdin_fd);
	}
	if (backup->stdout_fd != -1)
	{
		dup2(backup->stdout_fd, STDOUT_FILENO);
		close(backup->stdout_fd);
	}
	if (backup->stderr_fd != -1)
	{
		dup2(backup->stderr_fd, STDERR_FILENO);
		close(backup->stderr_fd);
	}
	free(backup);
}

/* Fonction de gestion des pipes */
int	**create_pipes(t_exec *exec, int cmd_count)
{
	int	i;
	int	**pipes;

	if (cmd_count <= 1)
		return (NULL);
	pipes = malloc(sizeof(int *) * (cmd_count - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < cmd_count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			while (--i >= 0)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				free(pipes[i]);
			}
			free(pipes);
			return (NULL);
		}
		i++;
	}
	exec->pipes = pipes;
	return (pipes);
}

void	cleanup_pipes(t_exec *exec)
{
	int	i;

	if (!exec || !exec->pipes)
		return ;
	i = 0;
	while (i < exec->cmd_count - 1)
	{
		if (exec->pipes[i])
		{
			// Vérifier si les descripteurs sont valides avant de les fermer
			if (fcntl(exec->pipes[i][PIPE_READ], F_GETFD) != -1)
				close(exec->pipes[i][PIPE_READ]);
			if (fcntl(exec->pipes[i][PIPE_WRITE], F_GETFD) != -1)
				close(exec->pipes[i][PIPE_WRITE]);
			// Ne pas libérer la mémoire ici, cela sera fait dans cleanup_pipes
		}
		i++;
	}
	// Ne pas libérer exec->pipes ici, cela sera fait dans cleanup_pipes
}
