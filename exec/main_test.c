/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhour <obouhour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 12:32:13 by obouhour          #+#    #+#             */
/*   Updated: 2024/12/25 14:05:15 by obouhour         ###   ########.fr       */
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


void	free_cmd(t_command	**commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		free(commands[i]);
		i++;
	}
	free (commands);
}

char	*cmd_used(char *arg)
{
	char	*cmd;

	cmd = malloc(sizeof(char) * ft_strlen(arg));
	if (!cmd)
		perror("petit malloc"); //oui oui il faudrait free les autre commandes oui
	return (cmd);
}

t_command	**create_command(char **args, int cmd_count)
{
	int			i;
	t_command	**command;

	i = 0;
	command = malloc(sizeof(t_command *) * cmd_count);
	if (!command)
		perror("malloc");
	while (i < cmd_count)
	{
		command.args[i] =  cmd_used(args[i + 1]);
		i++;
	}
	command[i] = NULL;
	return (command);
}

int	main(int ac, char **av, char **envp)
{
	int			i;
	int			cmd_count;
	t_command	**commands;

	i = 0;
	cmd_count = ac - 1;
	commands = create_command(av, cmd_count);
	execute_commands(commands, cmd_count, envp);
	free_cmd(commands);
	return (0);
}
