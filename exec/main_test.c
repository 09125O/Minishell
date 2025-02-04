/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 12:32:13 by obouhour          #+#    #+#             */
/*   Updated: 2025/02/04 18:47:25 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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
// 	char **test;

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
//         test = ft_split(av[i + 1], ' '); // Remplacez par votre implémentation de ft_split
//         if (!test)
//         {
//             perror("ft_split");
//             free_commands(commands, i);
//             return 1;
//         }

//         commands[i] = create_command(test);
//     }

//     execute_commands(commands, cmd_count, envp);

//     free_commands(commands, cmd_count);
//     return 0;
// }


void free_cmd(t_command **commands)
{
	int	i;

	i = 0;
	if (!commands)
		return;
	while (commands[i])
	{
		if (commands[i]->args)
			free_dbl_tab(commands[i]->args);
		if (commands[i]->redir)
			free(commands[i]->redir);
		free(commands[i]);
		i++;
	}
	free(commands);
}

char	*cmd_used(char *arg)
{
	char	*cmd;

	cmd = malloc(sizeof(char) * ft_strlen(arg));
	if (!cmd)
		perror("petit malloc"); //oui oui il faudrait free les autre commandes oui
	return (cmd);
}

t_command **create_command(char **args, int cmd_count)
{
	int			i;
	t_command	**commands;

	commands = malloc(sizeof(t_command *) * (cmd_count + 1)); // +1 for NULL terminator
	if (!commands)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < cmd_count)
	{
		commands[i] = malloc(sizeof(t_command));
		if (!commands[i])
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		commands[i]->args = ft_split(args[i + 1], ' ');
		commands[i]->redir = NULL; // Pas de redirection pour ce test
		i++;
	}
	commands[i] = NULL; // NULL terminator
	return (commands);
	}

int	main(int ac, char **av, char **envp)
{
	int			cmd_count;
	t_command	**commands;
	t_env		*env;

	if (ac < 2)
	{
		printf("Usage: %s <cmd1> [cmd2 ...]\n", av[0]);
		return 1;
	}
	// Initialiser les variables d'environnement
	env = init_env(envp);
	if (!env)
	{
		perror("Failed to initialize environment");
		return EXIT_FAILURE;
	}
	// Configurer les signaux
	configure_signals();
	// Créer les commandes
	cmd_count = ac - 1;
	commands = create_command(av, cmd_count);
	// Exécuter les commandes
	execute_commands(commands, cmd_count, env->vars);
	// Libérer la mémoire
	free_cmd(commands);
	free_env(env);
	return 0;
}
