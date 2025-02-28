#include "s_lexer.h"
#include <stdio.h>
#include <string.h>
#include "minishell.h"
#include "test_utils.h"

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

static void	test_token_creation(void)
{
	t_token	*token;
	char	*value;

	print_test_header("Test de création de tokens");

	value = strdup("test");
	token = create_token(value, TOKEN_WORD);
	print_test_result("Création token simple",
		token && strcmp(token->value, "test") == 0
		&& token->type == TOKEN_WORD);
	free_token_list(token);

	token = create_token(NULL, TOKEN_PIPE);
	print_test_result("Création token sans valeur",
		token && token->value == NULL && token->type == TOKEN_PIPE);
	free_token_list(token);
}

static void	test_token_list(void)
{
	t_token	*head;
	t_token	*token;
	char	*value1;
	char	*value2;

	print_test_header("Test de la liste de tokens");

	head = NULL;
	value1 = strdup("first");
	token = create_token(value1, TOKEN_WORD);
	add_token(&head, token);
	print_test_result("Ajout premier token",
		head && strcmp(head->value, "first") == 0);

	value2 = strdup("second");
	token = create_token(value2, TOKEN_WORD);
	add_token(&head, token);
	print_test_result("Ajout second token",
		head->next && strcmp(head->next->value, "second") == 0);

	token = head->next;
	print_test_result("Récupération dernier token",
		token && strcmp(token->value, "second") == 0);

	free_token_list(head);
}

static void	test_operators(void)
{
	t_token		*head;
	int			i;
	t_error_info	error;

	print_test_header("Test des opérateurs");

	head = NULL;
	i = 0;
	error.code = LEXER_SUCCESS;
	print_test_result("Validation pipe",
		validate_operator("|", 0, &error));

	i = 0;
	print_test_result("Traitement pipe",
		process_operator(&head, "|", &i) == 1
		&& head && head->type == TOKEN_PIPE);

	free_token_list(head);
	head = NULL;
	i = 0;
	print_test_result("Traitement redirection",
		process_operator(&head, ">", &i) == 1
		&& head && head->type == TOKEN_REDIRECT_OUT);

	free_token_list(head);
}

static void	test_quotes(void)
{
	t_token		*head;
	int			i;
	t_error_info	error;

	print_test_header("Test des quotes");

	head = NULL;
	i = 0;
	error.code = LEXER_SUCCESS;
	print_test_result("Quote simple valide",
		process_quotes(&head, "'test'", &i, &error) == 1
		&& head && strcmp(head->value, "test") == 0);

	free_token_list(head);
	head = NULL;
	i = 0;
	print_test_result("Quote double valide",
		process_quotes(&head, "\"test\"", &i, &error) == 1
		&& head && strcmp(head->value, "test") == 0);

	free_token_list(head);
	head = NULL;
	i = 0;
	error.code = LEXER_SUCCESS;
	process_quotes(&head, "'test", &i, &error);
	print_test_result("Quote non fermée",
		error.code == LEXER_ERROR_UNCLOSED_QUOTE);

	free_token_list(head);
}

static void	test_words(void)
{
	t_token	*head;
	int		i;

	print_test_header("Test des mots");

	head = NULL;
	i = 0;
	print_test_result("Mot simple",
		process_word(&head, "test", &i) == 1
		&& head && strcmp(head->value, "test") == 0);

	free_token_list(head);
	head = NULL;
	i = 0;
	print_test_result("Mot avec caractères spéciaux",
		process_word(&head, "test_123", &i) == 1
		&& head && strcmp(head->value, "test_123") == 0);

	free_token_list(head);
}

static void	test_env_vars(void)
{
	t_token		*head;
	int			i;
	t_error_info	error;

	print_test_header("Test des variables d'environnement");

	head = NULL;
	i = 0;
	error.code = LEXER_SUCCESS;
	print_test_result("Variable valide",
		validate_env_var("$TEST", 0, &error));

	print_test_result("Variable invalide",
		!validate_env_var("$123", 0, &error)
		&& error.code == LEXER_ERROR_INVALID_ENV_VAR);

	i = 0;
	head = create_env_var_token("$HOME", &i);
	print_test_result("Création token variable",
		head && head->type == TOKEN_WORD);

	free_token_list(head);
}

static void	test_lexer_full(void)
{
	t_token	*tokens;
	int		error_code;

	print_test_header("Test complet du lexer");

	tokens = lexer("echo test > file", &error_code);
	print_test_result("Commande simple",
		tokens && error_code == LEXER_SUCCESS);
	free_token_list(tokens);

	tokens = lexer("ls -la | grep test", &error_code);
	print_test_result("Commande avec pipe",
		tokens && error_code == LEXER_SUCCESS);
	free_token_list(tokens);

	tokens = lexer("echo \"test\" 'test'", &error_code);
	print_test_result("Commande avec quotes",
		tokens && error_code == LEXER_SUCCESS);
	free_token_list(tokens);

	tokens = lexer("cat << EOF", &error_code);
	print_test_result("Commande avec heredoc",
		tokens && error_code == LEXER_SUCCESS);
	free_token_list(tokens);
}

static void	test_edge_cases_quotes(void)
{
	t_token		*head;
	int			i;
	t_error_info	error;

	print_test_header("Test des cas limites - Quotes");

	head = NULL;
	i = 0;
	error.code = LEXER_SUCCESS;
	print_test_result("Quote vide",
		process_quotes(&head, "''", &i, &error) == 1
		&& head && strcmp(head->value, "") == 0);
	free_token_list(head);

	head = NULL;
	i = 0;
	error.code = LEXER_SUCCESS;
	print_test_result("Quote avec espaces",
		process_quotes(&head, "'   '", &i, &error) == 1
		&& head && strcmp(head->value, "   ") == 0);
	free_token_list(head);

	head = NULL;
	i = 0;
	error.code = LEXER_SUCCESS;
	print_test_result("Quote avec caractères spéciaux",
		process_quotes(&head, "'!@#$%^&*()'", &i, &error) == 1
		&& head && strcmp(head->value, "!@#$%^&*()") == 0);
	free_token_list(head);

	head = NULL;
	i = 0;
	error.code = LEXER_SUCCESS;
	process_quotes(&head, "'", &i, &error);
	print_test_result("Quote simple seule",
		error.code == LEXER_ERROR_UNCLOSED_QUOTE);
	free_token_list(head);

	head = NULL;
	i = 0;
	error.code = LEXER_SUCCESS;
	process_quotes(&head, "\"", &i, &error);
	print_test_result("Quote double seule",
		error.code == LEXER_ERROR_UNCLOSED_QUOTE);
	free_token_list(head);
}

static void	test_edge_cases_operators(void)
{
	t_error_info	error;

	print_test_header("Test des cas limites - Opérateurs");

	error.code = LEXER_SUCCESS;
	print_test_result("Double pipe invalide",
		!validate_operator("||", 0, &error)
		&& error.code == LEXER_ERROR_INVALID_OPERATOR);

	error.code = LEXER_SUCCESS;
	print_test_result("Triple redirection invalide",
		!validate_operator(">>>", 0, &error)
		&& error.code == LEXER_ERROR_INVALID_OPERATOR);

	error.code = LEXER_SUCCESS;
	print_test_result("Redirection inverse invalide",
		!validate_operator("><", 0, &error)
		&& error.code == LEXER_ERROR_INVALID_OPERATOR);
}

static void	test_edge_cases_env_vars(void)
{
	t_token		*head;
	int			i;
	t_error_info	error;

	print_test_header("Test des cas limites - Variables d'environnement");

	head = NULL;
	i = 0;
	error.code = LEXER_SUCCESS;
	print_test_result("Variable avec underscore seul",
		!validate_env_var("$_", 0, &error));

	print_test_result("Variable commençant par chiffre",
		!validate_env_var("$1TEST", 0, &error)
		&& error.code == LEXER_ERROR_INVALID_ENV_VAR);

	print_test_result("Variable avec caractères spéciaux",
		!validate_env_var("$TEST@VAR", 0, &error)
		&& error.code == LEXER_ERROR_INVALID_ENV_VAR);

	i = 0;
	head = create_env_var_token("$", &i);
	print_test_result("Dollar seul",
		head == NULL);
	free_token_list(head);

	i = 0;
	head = create_env_var_token("$NONEXISTENT", &i);
	print_test_result("Variable inexistante",
		head && head->type == TOKEN_WORD
		&& strcmp(head->value, "") == 0);
	free_token_list(head);
}

static void	test_edge_cases_words(void)
{
	t_token	*head;
	int		i;

	print_test_header("Test des cas limites - Mots");

	head = NULL;
	i = 0;
	print_test_result("Mot avec caractères échappés",
		process_word(&head, "test\\$PATH", &i) == 1
		&& head && strcmp(head->value, "test$PATH") == 0);
	free_token_list(head);

	head = NULL;
	i = 0;
	print_test_result("Mot avec espaces échappés",
		process_word(&head, "test\\ word", &i) == 1
		&& head && strcmp(head->value, "test word") == 0);
	free_token_list(head);

	head = NULL;
	i = 0;
	print_test_result("Mot avec quotes échappées",
		process_word(&head, "test\\'quote\\'", &i) == 1
		&& head && strcmp(head->value, "test'quote'") == 0);
	free_token_list(head);
}

static void	test_edge_cases_lexer(void)
{
	t_token	*tokens;
	int		error_code;

	print_test_header("Test des cas limites - Lexer");

	tokens = lexer("", &error_code);
	print_test_result("Chaîne vide",
		tokens == NULL && error_code == LEXER_SUCCESS);
	free_token_list(tokens);

	tokens = lexer("     ", &error_code);
	print_test_result("Espaces uniquement",
		tokens == NULL && error_code == LEXER_SUCCESS);
	free_token_list(tokens);

	tokens = lexer("echo \"test'", &error_code);
	print_test_result("Quote non fermée",
		tokens == NULL && error_code == LEXER_ERROR_UNCLOSED_QUOTE);
	free_token_list(tokens);

	tokens = lexer("echo test ||", &error_code);
	print_test_result("Opérateur invalide",
		tokens == NULL && error_code == LEXER_ERROR_INVALID_OPERATOR);
	free_token_list(tokens);

	tokens = lexer("echo $123", &error_code);
	print_test_result("Variable invalide",
		tokens == NULL && error_code == LEXER_ERROR_INVALID_ENV_VAR);
	free_token_list(tokens);

	tokens = lexer("echo test > > file", &error_code);
	print_test_result("Double redirection invalide",
		tokens == NULL && error_code == LEXER_ERROR_INVALID_OPERATOR);
	free_token_list(tokens);
}

static void	test_nested_quotes(void)
{
	t_token		*head;
	int			i;
	t_error_info	error;

	print_test_header("Test des quotes imbriquées");

	head = NULL;
	i = 0;
	error.code = LEXER_SUCCESS;
	print_test_result("Quotes simples dans quotes doubles",
		process_quotes(&head, "\"'test'\"", &i, &error) == 1
		&& head && strcmp(head->value, "'test'") == 0);
	free_token_list(head);

	head = NULL;
	i = 0;
	error.code = LEXER_SUCCESS;
	print_test_result("Quotes doubles dans quotes simples",
		process_quotes(&head, "'\"test\"'", &i, &error) == 1
		&& head && strcmp(head->value, "\"test\"") == 0);
	free_token_list(head);

	head = NULL;
	i = 0;
	error.code = LEXER_SUCCESS;
	print_test_result("Quotes multiples",
		process_quotes(&head, "\"'test'\"'autre test'", &i, &error) == 1
		&& head && strcmp(head->value, "'test'") == 0);
	free_token_list(head);

	head = NULL;
	i = 0;
	error.code = LEXER_SUCCESS;
	process_quotes(&head, "\"'test\"'", &i, &error);
	print_test_result("Quotes non fermées imbriquées",
		error.code == LEXER_ERROR_UNCLOSED_QUOTE);
	free_token_list(head);

	head = NULL;
	i = 0;
	error.code = LEXER_SUCCESS;
	print_test_result("Variable dans quotes doubles",
		process_quotes(&head, "\"$HOME\"", &i, &error) == 1
		&& head && head->type == TOKEN_DQUOTE);
	free_token_list(head);

	head = NULL;
	i = 0;
	error.code = LEXER_SUCCESS;
	print_test_result("Variable dans quotes simples",
		process_quotes(&head, "'$HOME'", &i, &error) == 1
		&& head && strcmp(head->value, "$HOME") == 0);
	free_token_list(head);
}

static void	test_memory_leaks(void)
{
	t_token		*tokens;
	int			error_code;
	t_token		*head;
	int			i;
	t_error_info	error;

	print_test_header("Test des fuites de mémoire");

	// Test 1: Cas d'erreur avec quotes non fermées
	tokens = lexer("echo \"test", &error_code);
	free_token_list(tokens);

	// Test 2: Cas d'erreur avec allocation échouée
	head = NULL;
	i = 0;
	error.code = LEXER_SUCCESS;
	process_quotes(&head, "'test'", &i, &error);
	free_token_list(head);

	// Test 3: Cas complexe avec plusieurs types de tokens
	tokens = lexer("echo test > file | grep \"pattern\" | sort '$VAR'", &error_code);
	free_token_list(tokens);

	// Test 4: Cas avec beaucoup de variables d'environnement
	tokens = lexer("echo $HOME$PATH$USER$SHELL$PWD", &error_code);
	free_token_list(tokens);

	// Test 5: Cas avec quotes imbriquées multiples
	tokens = lexer("echo \"'test'\"'\"autre test\"'\"dernier 'test'\"", &error_code);
	free_token_list(tokens);

	printf("\nPour vérifier les fuites de mémoire, exécutez:\n");
	printf("leaks --atExit -- ./test_lexer\n");
}

static void	test_operator_validation(void)
{
	t_error	error;
	int		result;

	printf("🧪 Test de validation des opérateurs\n");

	error.code = LEXER_SUCCESS;
	error.message = NULL;
	error.position = 0;
	result = validate_operator("|", 0, &error);
	assert_int_equal(result, 1, "Validation de l'opérateur pipe");

	error.code = LEXER_SUCCESS;
	error.message = NULL;
	error.position = 0;
	result = validate_operator("||", 0, &error);
	assert_int_equal(result, 0, "Rejet de l'opérateur OR");
	assert_int_equal(error.code, LEXER_ERROR_INVALID_OPERATOR,
		"Code d'erreur pour opérateur OR");

	error.code = LEXER_SUCCESS;
	error.message = NULL;
	error.position = 0;
	result = validate_operator("<<<", 0, &error);
	assert_int_equal(result, 0, "Rejet de triple redirection");
	assert_int_equal(error.code, LEXER_ERROR_INVALID_OPERATOR,
		"Code d'erreur pour triple redirection");
}

static void	test_operator_processing(void)
{
	t_token		*head;
	t_lexer_ctx	ctx;
	int			result;

	printf("🧪 Test du traitement des opérateurs\n");

	head = NULL;
	ctx.input = "|";
	ctx.position = 0;
	ctx.error.code = LEXER_SUCCESS;
	ctx.error.message = NULL;
	ctx.error.position = 0;
	result = process_operator(&head, &ctx);
	assert_int_equal(result, 1, "Traitement de l'opérateur pipe");
	assert_str_equal(head->value, "|", "Valeur du token pipe");
	assert_int_equal(head->type, TOKEN_OPERATOR, "Type du token pipe");
	free_token_list(head);

	head = NULL;
	ctx.input = ">";
	ctx.position = 0;
	ctx.error.code = LEXER_SUCCESS;
	ctx.error.message = NULL;
	ctx.error.position = 0;
	result = process_operator(&head, &ctx);
	assert_int_equal(result, 1, "Traitement de l'opérateur redirection");
	assert_str_equal(head->value, ">", "Valeur du token redirection");
	assert_int_equal(head->type, TOKEN_OPERATOR, "Type du token redirection");
	free_token_list(head);

	head = NULL;
	ctx.input = ">>";
	ctx.position = 0;
	ctx.error.code = LEXER_SUCCESS;
	ctx.error.message = NULL;
	ctx.error.position = 0;
	result = process_operator(&head, &ctx);
	assert_int_equal(result, 1, "Traitement de l'opérateur append");
	assert_str_equal(head->value, ">>", "Valeur du token append");
	assert_int_equal(head->type, TOKEN_OPERATOR, "Type du token append");
	free_token_list(head);
}

int	main(void)
{
	printf("\033[1;33m🧪 Démarrage des tests du module lexer\033[0m\n");

	test_token_creation();
	test_token_list();
	test_operators();
	test_quotes();
	test_words();
	test_env_vars();
	test_lexer_full();

	/* Tests des cas limites */
	test_edge_cases_quotes();
	test_edge_cases_operators();
	test_edge_cases_env_vars();
	test_edge_cases_words();
	test_edge_cases_lexer();
	test_nested_quotes();
	test_memory_leaks();

	test_operator_validation();
	test_operator_processing();

	printf("\n\033[1;33m=== Résumé des tests ===\033[0m\n");
	printf("Tests passés: %d/%d (%.2f%%)\n",
		g_passed_tests, g_total_tests,
		(g_passed_tests * 100.0) / g_total_tests);

	return (g_passed_tests == g_total_tests ? 0 : 1);
}
