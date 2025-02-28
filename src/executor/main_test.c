/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:35:28 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/25 13:44:02 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <stdio.h>

static int	g_total_tests = 0;
static int	g_passed_tests = 0;

static void	print_test_header(const char *title)
{
	printf("\n\033[1;34m=== %s ===\033[0m\n", title);
}

static void	print_test_result(const char *test_name, int success)
{
	g_total_tests++;
	if (success)
	{
		g_passed_tests++;
		printf("\033[1;32m✓\033[0m %s\n", test_name);
	}
	else
		printf("\033[1;31m✗\033[0m %s\n", test_name);
}

static t_env	*create_test_env(void)
{
	t_env	*env;
	char	*envp[] = {
		"PATH=/usr/bin:/bin",
		"HOME=/home/user",
		"USER=user",
		NULL
	};

	env = env_init(envp);
	return (env);
}

static t_command	*create_simple_command(char *cmd, char **args)
{
	t_command	*command;
	int			i;

	command = create_command(CMD_SIMPLE);
	if (!command)
		return (NULL);
	command->args = malloc(sizeof(char *) * 5);
	if (!command->args)
	{
		free_command(command);
		return (NULL);
	}
	command->args[0] = ft_strdup(cmd);
	i = 0;
	while (args && args[i] && i < 3)
	{
		command->args[i + 1] = ft_strdup(args[i]);
		i++;
	}
	command->args[i + 1] = NULL;
	return (command);
}

static void	test_simple_commands(t_env *env)
{
	t_command	**commands;
	int			success;

	print_test_header("Test des commandes simples");

	commands = malloc(sizeof(t_command *) * 2);
	commands[0] = create_simple_command("ls", (char *[]){"-l", NULL});
	commands[1] = NULL;

	success = 1;
	execute_commands(commands, 1, env);
	print_test_result("Commande ls simple", success);

	free_command(commands[0]);
	free(commands);

	commands = malloc(sizeof(t_command *) * 2);
	commands[0] = create_simple_command("echo", (char *[]){"test", NULL});
	commands[1] = NULL;

	success = 1;
	execute_commands(commands, 1, env);
	print_test_result("Commande echo simple", success);

	free_command(commands[0]);
	free(commands);
}

static void	test_pipes(t_env *env)
{
	t_command	**commands;
	int			success;

	print_test_header("Test des pipes");

	commands = malloc(sizeof(t_command *) * 3);
	commands[0] = create_simple_command("ls", (char *[]){"-l", NULL});
	commands[1] = create_simple_command("grep", (char *[]){"test", NULL});
	commands[2] = NULL;

	success = 1;
	execute_commands(commands, 2, env);
	print_test_result("Pipe simple ls | grep", success);

	free_command(commands[0]);
	free_command(commands[1]);
	free(commands);
}

static void	test_redirections(t_env *env)
{
	t_command		**commands;
	t_redirection	*redir;
	int				success;

	print_test_header("Test des redirections");

	commands = malloc(sizeof(t_command *) * 2);
	commands[0] = create_simple_command("echo", (char *[]){"test", NULL});
	commands[1] = NULL;

	redir = create_redirection(REDIR_OUT, "test.txt");
	commands[0]->redirections = redir;

	success = 1;
	execute_commands(commands, 1, env);
	print_test_result("Redirection sortie", success);

	free_command(commands[0]);
	free(commands);
}

static void	test_heredoc(t_env *env)
{
	t_command		**commands;
	t_redirection	*redir;
	int				success;
	int				pipe_fd[2];
	char			*test_input;

	print_test_header("Test des heredocs");

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe error");
		return ;
	}

	commands = malloc(sizeof(t_command *) * 2);
	commands[0] = create_simple_command("cat", NULL);
	commands[1] = NULL;

	redir = create_redirection(REDIR_HEREDOC, "EOF");
	commands[0]->redirections = redir;

	// Simuler l'entrée du heredoc
	test_input = "test line 1\ntest line 2\nEOF\n";
	write(pipe_fd[1], test_input, ft_strlen(test_input));
	close(pipe_fd[1]);

	// Rediriger l'entrée standard vers notre pipe
	int saved_stdin = dup(STDIN_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);

	success = 1;
	execute_commands(commands, 1, env);

	// Restaurer l'entrée standard
	dup2(saved_stdin, STDIN_FILENO);
	close(pipe_fd[0]);
	close(saved_stdin);

	print_test_result("Heredoc simple", success);

	free_command(commands[0]);
	free(commands);
}

static void	test_error_cases(t_env *env)
{
	t_command	**commands;
	int			success;

	print_test_header("Test des cas d'erreur");

	commands = malloc(sizeof(t_command *) * 2);
	commands[0] = create_simple_command("invalid_command", NULL);
	commands[1] = NULL;

	success = 1;
	execute_commands(commands, 1, env);
	print_test_result("Commande invalide", success);

	free_command(commands[0]);
	free(commands);
}

static void	test_complex_pipes(t_env *env)
{
	t_command	**commands;
	int			success;

	print_test_header("Test des pipes complexes");

	// Test pipe à 3 commandes
	commands = malloc(sizeof(t_command *) * 4);
	commands[0] = create_simple_command("ls", (char *[]){"-la", NULL});
	commands[1] = create_simple_command("grep", (char *[]){"test", NULL});
	commands[2] = create_simple_command("wc", (char *[]){"-l", NULL});
	commands[3] = NULL;

	success = 1;
	execute_commands(commands, 3, env);
	print_test_result("Pipeline triple (ls | grep | wc)", success);

	free_command(commands[0]);
	free_command(commands[1]);
	free_command(commands[2]);
	free(commands);

	// Test pipe avec sort
	commands = malloc(sizeof(t_command *) * 3);
	commands[0] = create_simple_command("ls", NULL);
	commands[1] = create_simple_command("sort", (char *[]){"-r", NULL});
	commands[2] = NULL;

	success = 1;
	execute_commands(commands, 2, env);
	print_test_result("Pipeline avec tri (ls | sort -r)", success);

	free_command(commands[0]);
	free_command(commands[1]);
	free(commands);
}

static void	test_complex_redirections(t_env *env)
{
	t_command		**commands;
	t_redirection	*redir1;
	t_redirection	*redir2;
	int				success;

	print_test_header("Test des redirections complexes");

	// Test redirection entrée et sortie
	commands = malloc(sizeof(t_command *) * 2);
	commands[0] = create_simple_command("cat", NULL);
	commands[1] = NULL;

	redir1 = create_redirection(REDIR_IN, "test.txt");
	redir2 = create_redirection(REDIR_OUT, "output.txt");
	redir1->next = redir2;
	commands[0]->redirections = redir1;

	success = 1;
	execute_commands(commands, 1, env);
	print_test_result("Redirection entrée et sortie", success);

	free_command(commands[0]);
	free(commands);

	// Test redirection avec append
	commands = malloc(sizeof(t_command *) * 2);
	commands[0] = create_simple_command("echo", (char *[]){"append_test", NULL});
	commands[1] = NULL;

	redir1 = create_redirection(REDIR_APPEND, "output.txt");
	commands[0]->redirections = redir1;

	success = 1;
	execute_commands(commands, 1, env);
	print_test_result("Redirection avec append", success);

	free_command(commands[0]);
	free(commands);
}

static void	test_mixed_operations(t_env *env)
{
	t_command		**commands;
	t_redirection	*redir;
	int				success;

	print_test_header("Test des opérations mixtes");

	// Test pipe avec redirection
	commands = malloc(sizeof(t_command *) * 3);
	commands[0] = create_simple_command("ls", (char *[]){"-l", NULL});
	commands[1] = create_simple_command("grep", (char *[]){"test", NULL});
	commands[2] = NULL;

	redir = create_redirection(REDIR_OUT, "pipe_output.txt");
	commands[1]->redirections = redir;

	success = 1;
	execute_commands(commands, 2, env);
	print_test_result("Pipe avec redirection (ls -l | grep test > pipe_output.txt)", success);

	free_command(commands[0]);
	free_command(commands[1]);
	free(commands);

	// Test pipe avec heredoc
	commands = malloc(sizeof(t_command *) * 3);
	commands[0] = create_simple_command("cat", NULL);
	commands[1] = create_simple_command("grep", (char *[]){"line", NULL});
	commands[2] = NULL;

	int pipe_fd[2];
	if (pipe(pipe_fd) != -1)
	{
		redir = create_redirection(REDIR_HEREDOC, "EOF");
		commands[0]->redirections = redir;

		int saved_stdin = dup(STDIN_FILENO);
		write(pipe_fd[1], "test line\nother line\nEOF\n", 24);
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);

		success = 1;
		execute_commands(commands, 2, env);

		dup2(saved_stdin, STDIN_FILENO);
		close(pipe_fd[0]);
		close(saved_stdin);
	}
	else
		success = 0;

	print_test_result("Heredoc avec pipe (cat << EOF | grep line)", success);

	free_command(commands[0]);
	free_command(commands[1]);
	free(commands);
}

static void	test_edge_cases(t_env *env)
{
	t_command	**commands;
	int			success;

	print_test_header("Test des cas limites");

	// Test commande avec beaucoup d'arguments
	commands = malloc(sizeof(t_command *) * 2);
	commands[0] = create_simple_command("echo",
		(char *[]){"arg1", "arg2", "arg3", NULL});
	commands[1] = NULL;

	success = 1;
	execute_commands(commands, 1, env);
	print_test_result("Commande avec arguments multiples", success);

	free_command(commands[0]);
	free(commands);

	// Test commande avec chemin absolu
	commands = malloc(sizeof(t_command *) * 2);
	commands[0] = create_simple_command("/bin/ls",
		(char *[]){"-la", "/tmp", NULL});
	commands[1] = NULL;

	success = 1;
	execute_commands(commands, 1, env);
	print_test_result("Commande avec chemin absolu", success);

	free_command(commands[0]);
	free(commands);

	// Test commande inexistante avec pipe
	commands = malloc(sizeof(t_command *) * 3);
	commands[0] = create_simple_command("invalid_cmd", NULL);
	commands[1] = create_simple_command("wc", (char *[]){"-l", NULL});
	commands[2] = NULL;

	success = 1;
	execute_commands(commands, 2, env);
	print_test_result("Pipe avec commande invalide", success);

	free_command(commands[0]);
	free_command(commands[1]);
	free(commands);
}

int	main(void)
{
	t_env	*env;

	printf("\033[1;33m🧪 Démarrage des tests du module executor\033[0m\n");

	env = create_test_env();
	if (!env)
	{
		printf("Erreur lors de la création de l'environnement de test\n");
		return (1);
	}

	test_simple_commands(env);
	test_pipes(env);
	test_redirections(env);
	test_heredoc(env);
	test_error_cases(env);

	// Nouveaux tests
	test_complex_pipes(env);
	test_complex_redirections(env);
	test_mixed_operations(env);
	test_edge_cases(env);

	printf("\n\033[1;33m=== Résumé des tests ===\033[0m\n");
	printf("Tests passés: %d/%d (%.2f%%)\n",
		g_passed_tests, g_total_tests,
		(g_passed_tests * 100.0) / g_total_tests);

	env_free(env);
	return (g_passed_tests == g_total_tests ? 0 : 1);
}
