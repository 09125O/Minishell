/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:58:21 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/25 12:56:35 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_parser.h"
#include "../libft/inc/libft.h"
#include <stdio.h>
#include <string.h>

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

static t_env	*create_minimal_env(void)
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

static t_token	*create_test_tokens(const char *cmd)
{
	int		error_code;
	t_token	*tokens;
	char	*cmd_copy;
	t_env	*env;

	printf("DEBUG: create_test_tokens avec commande: '%s'\n", cmd);
	cmd_copy = ft_strdup(cmd);
	if (!cmd_copy)
	{
		printf("DEBUG: Erreur lors de la copie de la commande\n");
		return (NULL);
	}
	env = create_minimal_env();
	if (!env)
	{
		printf("DEBUG: Erreur lors de l'initialisation de l'environnement\n");
		free(cmd_copy);
		return (NULL);
	}
	tokens = lexer(cmd_copy, env, &error_code);
	printf("DEBUG: Après lexer, error_code = %d\n", error_code);
	free(cmd_copy);
	env_free(env);
	if (error_code != LEXER_SUCCESS)
	{
		printf("DEBUG: Erreur du lexer\n");
		return (NULL);
	}
	if (tokens)
	{
		printf("DEBUG: Tokens générés avec succès\n");
		t_token *current = tokens;
		while (current)
		{
			printf("'%s' ", current->value);
			current = current->next;
		}
		printf("\n");
	}
	else
		printf("DEBUG: Aucun token généré\n");
	return (tokens);
}

static void	test_simple_command(void)
{
	t_token		*tokens;
	t_command	*cmd;

	print_test_header("Test des commandes simples");

	tokens = create_test_tokens("echo test");
	cmd = parse_tokens(tokens);
	print_test_result("Commande simple basique",
		cmd && cmd->type == CMD_SIMPLE && cmd->args
		&& strcmp(cmd->args[0], "echo") == 0
		&& strcmp(cmd->args[1], "test") == 0);
	free_command(cmd);
	free_token_list(tokens);

	tokens = create_test_tokens("ls -la");
	cmd = parse_tokens(tokens);
	print_test_result("Commande avec options",
		cmd && cmd->type == CMD_SIMPLE && cmd->args
		&& strcmp(cmd->args[0], "ls") == 0
		&& strcmp(cmd->args[1], "-la") == 0);
	free_command(cmd);
	free_token_list(tokens);
}

static void	test_redirections(void)
{
	t_token		*tokens;
	t_command	*cmd;

	print_test_header("Test des redirections");

	tokens = create_test_tokens("echo test > file.txt");
	cmd = parse_tokens(tokens);
	print_test_result("Redirection sortie",
		cmd && cmd->redirections && cmd->redirections->type == REDIR_OUT
		&& strcmp(cmd->redirections->file, "file.txt") == 0);
	free_command(cmd);
	free_token_list(tokens);

	tokens = create_test_tokens("cat < input.txt");
	cmd = parse_tokens(tokens);
	print_test_result("Redirection entrée",
		cmd && cmd->redirections && cmd->redirections->type == REDIR_IN
		&& strcmp(cmd->redirections->file, "input.txt") == 0);
	free_command(cmd);
	free_token_list(tokens);
}

static void	test_pipelines(void)
{
	t_token		*tokens;
	t_command	*cmd;

	print_test_header("Test des pipelines");

	tokens = create_test_tokens("ls -l | grep test");
	cmd = parse_tokens(tokens);
	print_test_result("Pipeline simple",
		cmd && cmd->type == CMD_PIPELINE && cmd->commands
		&& cmd->commands->next);
	free_command(cmd);
	free_token_list(tokens);

	tokens = create_test_tokens("cat file.txt | grep pattern | sort");
	cmd = parse_tokens(tokens);
	print_test_result("Pipeline multiple",
		cmd && cmd->type == CMD_PIPELINE && cmd->commands
		&& cmd->commands->next && cmd->commands->next->next);
	free_command(cmd);
	free_token_list(tokens);
}

static void	test_error_cases(void)
{
	t_token		*tokens;
	t_command	*cmd;

	print_test_header("Test des cas d'erreur");

	tokens = create_test_tokens("|");
	cmd = parse_tokens(tokens);
	print_test_result("Pipe seul",
		cmd == NULL);
	free_command(cmd);
	free_token_list(tokens);

	tokens = create_test_tokens("echo >");
	cmd = parse_tokens(tokens);
	print_test_result("Redirection sans fichier",
		cmd == NULL);
	free_command(cmd);
	free_token_list(tokens);

	tokens = create_test_tokens("ls | | grep");
	cmd = parse_tokens(tokens);
	print_test_result("Double pipe",
		cmd == NULL);
	free_command(cmd);
	free_token_list(tokens);
}

static void	test_memory_management(void)
{
	t_token		*tokens;
	t_command	*cmd;

	print_test_header("Test de la gestion mémoire");

	tokens = create_test_tokens("echo test > file | grep pattern > out");
	cmd = parse_tokens(tokens);
	free_command(cmd);
	free_token_list(tokens);
	print_test_result("Libération complexe", 1);

	tokens = create_test_tokens("cat < in1 < in2 | sort > out1 > out2");
	cmd = parse_tokens(tokens);
	free_command(cmd);
	free_token_list(tokens);
	print_test_result("Libération redirections multiples", 1);

	printf("\nPour vérifier les fuites de mémoire, exécutez:\n");
	printf("leaks --atExit -- ./test_parser\n");
}

static void	test_edge_cases_commands(void)
{
	t_token		*tokens;
	t_command	*cmd;

	print_test_header("Test des cas limites - Commandes");

	tokens = create_test_tokens("   echo    test   ");
	cmd = parse_tokens(tokens);
	print_test_result("Espaces multiples",
		cmd && cmd->type == CMD_SIMPLE && cmd->args
		&& strcmp(cmd->args[0], "echo") == 0
		&& strcmp(cmd->args[1], "test") == 0);
	free_command(cmd);
	free_token_list(tokens);

	tokens = create_test_tokens("cmd1 arg1 | cmd2 arg2 | cmd3 arg3 | cmd4 arg4");
	cmd = parse_tokens(tokens);
	print_test_result("Pipeline long (4 commandes)",
		cmd && cmd->type == CMD_PIPELINE && cmd->commands
		&& cmd->commands->next && cmd->commands->next->next
		&& cmd->commands->next->next->next);
	free_command(cmd);
	free_token_list(tokens);

	tokens = create_test_tokens("cmd arg1 arg2 arg3 arg4");
	cmd = parse_tokens(tokens);
	print_test_result("Maximum d'arguments (4)",
		cmd && cmd->type == CMD_SIMPLE && cmd->args
		&& cmd->args[4] == NULL);
	free_command(cmd);
	free_token_list(tokens);

	tokens = create_test_tokens("cmd arg1 arg2 arg3 arg4 arg5");
	cmd = parse_tokens(tokens);
	print_test_result("Dépassement du maximum d'arguments",
		cmd == NULL);
	free_command(cmd);
	free_token_list(tokens);
}

static void	test_edge_cases_redirections(void)
{
	t_token		*tokens;
	t_command	*cmd;

	print_test_header("Test des cas limites - Redirections");

	tokens = create_test_tokens("cmd > file1 > file2 > file3");
	cmd = parse_tokens(tokens);
	print_test_result("Redirections multiples sortie",
		cmd && cmd->redirections && cmd->redirections->next
		&& cmd->redirections->next->next);
	free_command(cmd);
	free_token_list(tokens);

	tokens = create_test_tokens("cmd < file1 < file2 < file3");
	cmd = parse_tokens(tokens);
	print_test_result("Redirections multiples entrée",
		cmd && cmd->redirections && cmd->redirections->next
		&& cmd->redirections->next->next);
	free_command(cmd);
	free_token_list(tokens);

	tokens = create_test_tokens("cmd > file1 < file2 >> file3 << EOF");
	cmd = parse_tokens(tokens);
	print_test_result("Redirections mixtes",
		cmd && cmd->redirections && cmd->redirections->next
		&& cmd->redirections->next->next
		&& cmd->redirections->next->next->next);
	free_command(cmd);
	free_token_list(tokens);

	tokens = create_test_tokens("cmd >");
	cmd = parse_tokens(tokens);
	print_test_result("Redirection sans fichier",
		cmd == NULL);
	free_command(cmd);
	free_token_list(tokens);

	tokens = create_test_tokens("cmd > file1 >");
	cmd = parse_tokens(tokens);
	print_test_result("Redirection incomplète après valide",
		cmd == NULL);
	free_command(cmd);
	free_token_list(tokens);
}

static void	test_edge_cases_pipelines(void)
{
	t_token		*tokens;
	t_command	*cmd;

	print_test_header("Test des cas limites - Pipelines");

	tokens = create_test_tokens("|cmd");
	cmd = parse_tokens(tokens);
	print_test_result("Pipe au début",
		cmd == NULL);
	free_command(cmd);
	free_token_list(tokens);

	tokens = create_test_tokens("cmd|");
	cmd = parse_tokens(tokens);
	print_test_result("Pipe à la fin",
		cmd == NULL);
	free_command(cmd);
	free_token_list(tokens);

	tokens = create_test_tokens("cmd1||cmd2");
	cmd = parse_tokens(tokens);
	print_test_result("Double pipe",
		cmd == NULL);
	free_command(cmd);
	free_token_list(tokens);

	tokens = create_test_tokens("cmd1 | cmd2 | | cmd3");
	cmd = parse_tokens(tokens);
	print_test_result("Pipe vide au milieu",
		cmd == NULL);
	free_command(cmd);
	free_token_list(tokens);
}

static void	test_edge_cases_mixed(void)
{
	t_token		*tokens;
	t_command	*cmd;

	print_test_header("Test des cas limites - Cas mixtes");

	tokens = create_test_tokens("cmd1 > file1 | cmd2 < file2 | cmd3 >> file3");
	cmd = parse_tokens(tokens);
	print_test_result("Pipeline avec redirections",
		cmd && cmd->type == CMD_PIPELINE
		&& cmd->commands && cmd->commands->redirections
		&& cmd->commands->next && cmd->commands->next->redirections
		&& cmd->commands->next->next
		&& cmd->commands->next->next->redirections);
	free_command(cmd);
	free_token_list(tokens);

	tokens = create_test_tokens("cmd1 arg1 arg2 > file1 > file2 | cmd2");
	cmd = parse_tokens(tokens);
	print_test_result("Arguments max + redirections multiples + pipe",
		cmd && cmd->type == CMD_PIPELINE
		&& cmd->commands && cmd->commands->args
		&& cmd->commands->redirections
		&& cmd->commands->redirections->next);
	free_command(cmd);
	free_token_list(tokens);

	tokens = create_test_tokens("cmd1 > file1 > file2 > file3 | cmd2 > out");
	cmd = parse_tokens(tokens);
	print_test_result("Redirections multiples dans pipeline",
		cmd && cmd->type == CMD_PIPELINE
		&& cmd->commands && cmd->commands->redirections
		&& cmd->commands->redirections->next
		&& cmd->commands->redirections->next->next);
	free_command(cmd);
	free_token_list(tokens);
}

int	main(void)
{
	printf("\033[1;33m🧪 Démarrage des tests du module parser\033[0m\n");

	test_simple_command();
	test_redirections();
	test_pipelines();
	test_error_cases();
	test_memory_management();

	// Tests des cas limites
	test_edge_cases_commands();
	test_edge_cases_redirections();
	test_edge_cases_pipelines();
	test_edge_cases_mixed();

	printf("\n\033[1;33m=== Résumé des tests ===\033[0m\n");
	printf("Tests passés: %d/%d (%.2f%%)\n",
		g_passed_tests, g_total_tests,
		(g_passed_tests * 100.0) / g_total_tests);

	return (g_passed_tests == g_total_tests ? 0 : 1);
}
