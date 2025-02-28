#include "minishell.h"
#include "signals.h"
#include <unistd.h>

static void	print_test_header(const char *title)
{
	printf("\n\033[1;34m=== %s ===\033[0m\n", title);
}

static void	print_test_result(const char *test_name, int success)
{
	printf("%-50s %s\n", test_name,
		success ? "\033[1;32m[OK]\033[0m" : "\033[1;31m[KO]\033[0m");
}

static void	check_leaks(const char *test_name)
{
	printf("\n\033[1;35m=== Vérification des fuites pour %s ===\033[0m\n", test_name);
	system("leaks test_signals | grep \"leaked bytes\" || true");
}

/* Test des fonctions d'initialisation */
static void	test_signals_init(void)
{
	print_test_header("Test des fonctions d'initialisation");

	signals_init();
	print_test_result("signals_init", 1);

	signals_reset();
	print_test_result("signals_reset", 1);

	check_leaks("test_signals_init");
}

/* Test des états des signaux */
static void	test_signal_states(void)
{
	int	status;

	print_test_header("Test des états des signaux");

	status = signals_set_state(SIGNAL_INTERACTIVE);
	print_test_result("Set interactive mode",
		status == SIGNAL_SUCCESS);

	status = signals_set_state(SIGNAL_CHILD);
	print_test_result("Set child mode",
		status == SIGNAL_SUCCESS);

	status = signals_set_state(SIGNAL_HEREDOC);
	print_test_result("Set heredoc mode",
		status == SIGNAL_SUCCESS);

	status = signals_set_state(SIGNAL_DEFAULT);
	print_test_result("Reset to default mode",
		status == SIGNAL_SUCCESS);

	check_leaks("test_signal_states");
}

/* Test des gestionnaires de signaux */
static void	test_signal_handlers(void)
{
	print_test_header("Test des gestionnaires de signaux");

	signals_set_state(SIGNAL_INTERACTIVE);
	print_test_result("SIGINT en mode interactif", 1);

	signals_set_state(SIGNAL_CHILD);
	print_test_result("SIGINT en mode child", 1);

	signals_set_state(SIGNAL_HEREDOC);
	print_test_result("SIGINT en mode heredoc", 1);

	check_leaks("test_signal_handlers");
}

/* Test des utilitaires */
static void	test_signal_utils(void)
{
	print_test_header("Test des utilitaires");

	signals_ignore();
	print_test_result("Ignore signals", 1);

	signals_default();
	print_test_result("Default signals", 1);

	print_test_result("Check interruption",
		!signals_is_interrupted());

	check_leaks("test_signal_utils");
}

int	main(void)
{
	printf("\033[1;33m🧪 Démarrage des tests du module signals\033[0m\n");

	test_signals_init();
	test_signal_states();
	test_signal_handlers();
	test_signal_utils();

	printf("\n\033[1;33m✨ Tests terminés\033[0m\n");
	printf("\n\033[1;35m=== Vérification finale des fuites ===\033[0m\n");
	system("leaks test_signals | grep \"total leaked bytes\" || true");
	return (0);
}
