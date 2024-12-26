/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhour <obouhour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:58:07 by obouhour          #+#    #+#             */
/*   Updated: 2024/12/25 12:20:45 by obouhour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	setup_pipes(t_exec *exec, int cmd_index, int cmd_count)
{
	int	i;

	i = 0;
	if (cmd_index > 0)// Si ce n'est pas la première commande, rediriger l'entrée standard depuis le pipe précédent
	{
		if (dup2(exec->pipes[cmd_index - 1][0], STDIN_FILENO) == -1)
		{
			perror("minishell: error in dup2 (input)");
			exit(EXIT_FAILURE);
		}
	}
	if (cmd_index < cmd_count - 1)// Si ce n'est pas la dernière commande, rediriger la sortie standard vers le pipe actuel
	{
		if (dup2(exec->pipes[cmd_index][1], STDOUT_FILENO) == -1)
		{
			perror("minishell: error in dup2 (output)");
			exit(EXIT_FAILURE);
		}
	}
	while (i < exec->pipe_count)// Fermer tous les descripteurs de fichiers inutilisés dans ce processus enfant
	{
		close(exec->pipes[i][0]);
		close(exec->pipes[i][1]);
		i++;
	}
}


void	spawn_processes(t_exec *exec, t_command **commands, int cmd_count, char **env)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < cmd_count)
	{
		pid = fork();
		if (pid == 0)
		{
			setup_pipes(exec, i, cmd_count); // va gerer les pipes
			handle_redirection(commands[i]->redir); // va gerer les rediection de chaque commands
			exec_command(commands[i]->args, env); // execute la commande
		}
		i++;
	}
}

void	close_pipes(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->pipe_count)
	{
		close(exec->pipes[i][0]);
		close(exec->pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < exec->pipe_count)
	{
		free(exec->pipes[i]);
		i++;
	}
	free(exec->pipes);
}
