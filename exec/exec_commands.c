/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhour <obouhour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:19:10 by obouhour          #+#    #+#             */
/*   Updated: 2024/12/22 12:40:32 by obouhour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void exec_command(char **args, char **env)
{
	char	*path;

	if (!args || !args[0]) // Vérifie si les arguments sont valides
	{
		perror("minishell: invalid command");
		exit(127);
	}
	// if (is_builtin(args[0])) // À ajouter une fois que les built-ins sont gérés
	// {
	//     execute_builtin(args);
	//     return;
	// }
	path = path_finder(args[0], env); // Recherche du chemin de la commande
	if (!path || access(path, F_OK | X_OK) != 0)
	{
		perror("minishell: command not found");
		exit(127);
	}
	if (execve(path, args, env) == -1) // Exécute la commande
	{
		perror("minishell: execution failed");
		exit(126);
	}
}


void	init_executor(t_exec *exec, int pipe_count)
{
	int	i;

	i = 0;
	exec->pipe_count = pipe_count;
	exec->pipes = malloc(sizeof(int *) * pipe_count);
	while (i < pipe_count)
	{
		exec->pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(exec->pipes[i]) == -1)
		{
			perror("minishell: error creating pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	execute_commands(t_command **commands, int cmd_count, char **env)
{
	int		i;
	int		status;
	t_exec	exec;

	i = 0;
	init_executor(&exec, cmd_count - 1);
	spawn_processes(&exec, commands, cmd_count, env);
	close_pipes(&exec);
	while (i < cmd_count)
	{
		wait(&status); // Attendre tous les processus enfants
		if (WIFEXITED(status)) // Vérifie si le processus s'est terminé normalement
			exec.last_exit_code = WEXITSTATUS(status); // Sinon on recup le code d'erreur
		i++;
	}
}

/*Test par gpt*/
// t_command *create_command(char **args)
// {
//     t_command *cmd;

//     cmd = malloc(sizeof(t_command));
//     if (!cmd)
//     {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }

//     cmd->args = args;
//     cmd->redir = NULL; // Pas de redirection pour ce test
//     return cmd;
// }

// // Fonction utilitaire : libère les commandes
// void free_commands(t_command **commands, int cmd_count)
// {
//     for (int i = 0; i < cmd_count; i++)
//     {
//         free(commands[i]->args); // Libérer les arguments (s'ils ont été alloués dynamiquement)
//         free(commands[i]);       // Libérer la structure
//     }
//     free(commands); // Libérer le tableau de commandes
// }

// // Fonction principale
// int main(int ac, char **av, char **envp)
// {
//     t_command **commands;
//     int cmd_count;
//     int i;

//     if (ac < 2)
//     {
//         printf("Usage: %s <cmd1> [cmd2 ...]\n", av[0]);
//         return 1;
//     }

//     cmd_count = ac - 1;
//     commands = malloc(sizeof(t_command *) * cmd_count);
//     if (!commands)
//     {
//         perror("malloc");
//         return 1;
//     }

//     for (i = 0; i < cmd_count; i++)
//     {
//         // Diviser chaque commande entrée par l'utilisateur en arguments
//         char **args = ft_split(av[i + 1], ' '); // Remplacez par votre implémentation de ft_split
//         if (!args)
//         {
//             perror("ft_split");
//             free_commands(commands, i);
//             return 1;
//         }

//         commands[i] = create_command(args);
//     }

//     execute_commands(commands, cmd_count, envp);

//     free_commands(commands, cmd_count);

//     return 0;
// }