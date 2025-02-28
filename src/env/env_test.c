#include "../../includes/env.h"
#include <stdio.h>
#include <string.h>
#include <signal.h>

static int	g_total_tests = 0;
static int	g_passed_tests = 0;
static int	g_test_interrupted = 0;

static void	handle_signal(int signo)
{
	if (signo == SIGINT)
		g_test_interrupted = 1;
}

static void	print_separator(const char *title)
{
	printf("\n=== Test: %s ===\n", title);
}

static void	test_result(const char *test_name, int success)
{
	if (g_test_interrupted)
		return ;
	g_total_tests++;
	if (success)
	{
		g_passed_tests++;
		printf("✅ %s\n", test_name);
	}
	else
		printf("❌ %s\n", test_name);
}

static void	test_env_init_edge_cases(void)
{
	t_env	*env;

	print_separator("Tests d'initialisation - Cas limites");

	// Test avec NULL
	env = env_init(NULL);
	test_result("Init avec NULL", env == NULL);

	// Test avec tableau vide
	char *empty[] = {NULL};
	env = env_init(empty);
	test_result("Init avec tableau vide", env == NULL);

	// Test avec variables invalides
	char *invalid[] = {"TEST=value", NULL};
	env = env_init(invalid);
	if (env)
	{
		test_result("Init avec variables valides", true);
		env_free(env);
	}
	else
		test_result("Init avec variables valides", false);
}

static void	test_env_operations_edge_cases(char **envp)
{
	t_env	*env;
	int		status;

	print_separator("Tests opérations - Cas limites");
	env = env_init(envp);
	if (!env)
		return ;

	status = env_add(&env, NULL, "value");
	test_result("Ajout avec clé NULL", status == ENV_INVALID_KEY);

	status = env_add(&env, "KEY", NULL);
	test_result("Ajout avec valeur NULL", status == ENV_INVALID_KEY);

	status = env_add(&env, "", "value");
	test_result("Ajout avec clé vide", status == ENV_INVALID_KEY);

	status = env_add(&env, "=invalid", "value");
	test_result("Ajout avec clé invalide", status == ENV_INVALID_KEY);

	status = env_add(&env, "123invalid", "value");
	test_result("Ajout avec clé commençant par un chiffre",
		status == ENV_INVALID_KEY);

	env_free(env);
}

static void	test_env_memory_operations(char **envp)
{
	t_env	*env;
	t_env	*dup_env;
	char	**env_array;
	char	*long_value;
	int		i;
	int		status;

	print_separator("Tests mémoire et opérations lourdes");
	env = env_init(envp);
	if (!env)
		return ;

	// Test de duplication
	dup_env = env_dup(env);
	test_result("Duplication de l'environnement", dup_env != NULL);
	env_free(dup_env);

	// Test avec beaucoup de variables
	i = 0;
	while (i < 1000)
	{
		char key[32];
		snprintf(key, sizeof(key), "TEST_VAR_%d", i);
		status = env_add(&env, key, "value");
		i++;
	}
	test_result("Ajout de 1000 variables", env_get(env, "TEST_VAR_999") != NULL);

	// Test avec une très longue valeur
	long_value = malloc(10000);
	if (long_value)
	{
		memset(long_value, 'A', 9998);
		long_value[9998] = 'B';
		long_value[9999] = '\0';
		status = env_add(&env, "LONG_VALUE", long_value);
		test_result("Ajout d'une très longue valeur",
			status == ENV_SUCCESS);
		free(long_value);
	}

	// Test de conversion en tableau
	env_array = env_to_array(env);
	test_result("Conversion en tableau", env_array != NULL);
	env_array_free(env_array);

	env_free(env);
}

static void	test_env_expansion_edge_cases(char **envp)
{
	t_env	*env;
	char	*expanded;

	print_separator("Tests expansion - Cas limites");
	env = env_init(envp);
	if (!env)
		return ;

	expanded = env_expand_var(env, "$");
	test_result("Expansion $ seul",
		expanded && strcmp(expanded, "$") == 0);
	free(expanded);

	expanded = env_expand_var(env, "$$");
	test_result("Expansion $$ (PID)", expanded && *expanded != '\0');
	free(expanded);

	expanded = env_expand_var(env, "$?");
	test_result("Expansion $? sans statut précédent",
		expanded && strcmp(expanded, "0") == 0);
	free(expanded);

	expanded = env_expand_var(env, "$NONEXISTENT");
	test_result("Expansion variable inexistante",
		expanded && *expanded == '\0');
	free(expanded);

	// Test des accolades
	env_add(&env, "TEST_VAR", "success");
	expanded = env_expand_var(env, "${TEST_VAR}");
	test_result("Expansion avec accolades simple",
		expanded && strcmp(expanded, "success") == 0);
	free(expanded);

	expanded = env_expand_var(env, "${TEST_VAR}suffix");
	test_result("Expansion avec accolades et suffixe",
		expanded && strcmp(expanded, "successsuffix") == 0);
	free(expanded);

	expanded = env_expand_var(env, "prefix${TEST_VAR}");
	test_result("Expansion avec accolades et préfixe",
		expanded && strcmp(expanded, "prefixsuccess") == 0);
	free(expanded);

	expanded = env_expand_var(env, "${NONEXISTENT}");
	test_result("Expansion avec accolades - variable inexistante",
		expanded && *expanded == '\0');
	free(expanded);

	expanded = env_expand_var(env, "${?}");
	test_result("Expansion avec accolades - variable spéciale",
		expanded && strcmp(expanded, "0") == 0);
	free(expanded);

	env_free(env);
}

static void	test_env_sync_operations(char **envp)
{
	t_env	*env;
	int		status;
	char	*value;

	print_separator("Tests synchronisation");
	env = env_init(envp);
	if (!env)
		return ;

	env_lock();
	status = env_add(&env, "SYNC_TEST", "value1");
	value = env_get(env, "SYNC_TEST");
	test_result("Opération sous verrou",
		status == ENV_SUCCESS && value && strcmp(value, "value1") == 0);
	env_unlock();

	status = env_update_from_child(&env, (char *[]){"NEW_VAR=value", NULL});
	test_result("Mise à jour depuis processus enfant", status == 1);

	env_free(env);
}

static void	test_simple_expansion(void)
{
	t_env	*env;
	char	*expanded;

	printf("\n=== Test: Expansion simple ===\n");
	env = NULL;
	env_add(&env, "TEST", "value");
	env_add(&env, "EMPTY", "");
	env_add(&env, "SPACE", "hello world");

	expanded = env_expand_var(env, "$TEST");
	test_result("Variable simple",
		expanded && strcmp(expanded, "value") == 0);
	free(expanded);

	expanded = env_expand_var(env, "$EMPTY");
	test_result("Variable vide",
		expanded && strcmp(expanded, "") == 0);
	free(expanded);

	expanded = env_expand_var(env, "$SPACE");
	test_result("Variable avec espaces",
		expanded && strcmp(expanded, "hello world") == 0);
	free(expanded);

	env_free(env);
}

static void	test_special_chars(void)
{
	t_env	*env;
	char	*expanded;

	printf("\n=== Test: Caractères spéciaux ===\n");
	env = NULL;
	env_add(&env, "VAR_WITH_UNDER", "under");
	env_add(&env, "VAR123", "numbers");

	expanded = env_expand_var(env, "$VAR_WITH_UNDER");
	test_result("Variable avec underscore",
		expanded && strcmp(expanded, "under") == 0);
	free(expanded);

	expanded = env_expand_var(env, "$VAR123");
	test_result("Variable avec chiffres",
		expanded && strcmp(expanded, "numbers") == 0);
	free(expanded);

	env_free(env);
}

static void	test_complex_expansion(void)
{
	t_env	*env;
	char	*expanded;

	printf("\n=== Test: Expansion complexe ===\n");
	env = NULL;
	env_add(&env, "USER", "john");
	env_add(&env, "HOME", "/home/john");

	expanded = env_expand_var(env, "Hello $USER!");
	test_result("Préfixe et suffixe",
		expanded && strcmp(expanded, "Hello john!") == 0);
	free(expanded);

	expanded = env_expand_var(env, "$USER$HOME");
	test_result("Variables consécutives",
		expanded && strcmp(expanded, "john/home/john") == 0);
	free(expanded);

	expanded = env_expand_var(env, "Path: $HOME/documents");
	test_result("Variable dans un chemin",
		expanded && strcmp(expanded, "Path: /home/john/documents") == 0);
	free(expanded);

	env_free(env);
}

static void	test_edge_cases(void)
{
	t_env	*env;
	char	*expanded;

	printf("\n=== Test: Cas limites ===\n");
	env = NULL;

	expanded = env_expand_var(env, "");
	test_result("Chaîne vide", expanded == NULL);
	free(expanded);

	expanded = env_expand_var(env, "$");
	test_result("Dollar seul",
		expanded && strcmp(expanded, "$") == 0);
	free(expanded);

	expanded = env_expand_var(env, "$$");
	test_result("Double dollar",
		expanded && expanded[0] != '\0');
	free(expanded);

	expanded = env_expand_var(env, "$?");
	test_result("Code de retour",
		expanded && strcmp(expanded, "0") == 0);
	free(expanded);

	env_free(env);
}

static void	test_braces_expansion(void)
{
	t_env	*env;
	char	*expanded;

	printf("\n=== Test: Expansion avec accolades ===\n");
	env = NULL;
	env_add(&env, "TEST", "value");
	env_add(&env, "LONG_VAR", "long_value");

	expanded = env_expand_var(env, "${TEST}");
	test_result("Accolades simples",
		expanded && strcmp(expanded, "value") == 0);
	free(expanded);

	expanded = env_expand_var(env, "prefix${TEST}suffix");
	test_result("Accolades avec préfixe et suffixe",
		expanded && strcmp(expanded, "prefixvaluesuffix") == 0);
	free(expanded);

	expanded = env_expand_var(env, "${TEST}${LONG_VAR}");
	test_result("Accolades multiples",
		expanded && strcmp(expanded, "valuelong_value") == 0);
	free(expanded);

	expanded = env_expand_var(env, "${UNDEFINED}");
	test_result("Accolades avec variable indéfinie",
		expanded && strcmp(expanded, "") == 0);
	free(expanded);

	env_free(env);
}

static void	test_quoted_expansion(void)
{
	t_env	*env;
	char	*expanded;

	printf("\n=== Test: Expansion avec quotes ===\n");
	env = NULL;
	env_add(&env, "TEST", "value");

	expanded = env_expand_quoted(env, "$TEST", '\'');
	test_result("Quote simple - pas d'expansion",
		expanded && strcmp(expanded, "$TEST") == 0);
	free(expanded);

	expanded = env_expand_quoted(env, "$TEST", '\"');
	test_result("Quote double - expansion",
		expanded && strcmp(expanded, "value") == 0);
	free(expanded);

	env_free(env);
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa;

	(void)argc;
	(void)argv;

	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	printf("🧪 Tests du module env\n");

	test_env_init_edge_cases();
	if (g_test_interrupted)
		goto end;

	test_env_operations_edge_cases(envp);
	if (g_test_interrupted)
		goto end;

	test_env_memory_operations(envp);
	if (g_test_interrupted)
		goto end;

	test_env_expansion_edge_cases(envp);
	if (g_test_interrupted)
		goto end;

	test_env_sync_operations(envp);
	if (g_test_interrupted)
		goto end;

	test_simple_expansion();
	if (g_test_interrupted)
		goto end;

	test_special_chars();

end:
	if (g_test_interrupted)
		printf("\nTests interrompus par l'utilisateur\n");
	else
	{
		printf("\n=== Résumé des tests ===\n");
		printf("Tests passés: %d/%d (%.2f%%)\n",
			g_passed_tests, g_total_tests,
			(g_passed_tests * 100.0) / g_total_tests);
	}

	return (g_test_interrupted ? 1 : (g_passed_tests == g_total_tests ? 0 : 1));
}
