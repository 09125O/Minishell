/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:10:21 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/25 14:10:06 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "s_parser.h"
#include "s_lexer.h"
#include "signals.h"
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
		"PWD=/current/dir",
		"OLDPWD=/old/dir",
		"USER=user",
		NULL
	};

	env = env_init(envp);
	return (env);
}

static void	test_echo(void)
{
	print_test_header("Test de echo");

	char *args1[] = {"echo", "Hello World", NULL};
	print_test_result("echo simple",
		ft_echo(args1) == 0);

	char *args2[] = {"echo", "-n", "Hello World", NULL};
	print_test_result("echo avec option -n",
		ft_echo(args2) == 0);

	char *args3[] = {"echo", NULL};
	print_test_result("echo sans arguments",
		ft_echo(args3) == 0);
}

static void	test_pwd(void)
{
	print_test_header("Test de pwd");
	print_test_result("pwd simple",
		ft_pwd() == 0);
}

static void	test_cd(t_env *env)
{
	print_test_header("Test de cd");

	char *args1[] = {"cd", "/tmp", NULL};
	print_test_result("cd vers répertoire absolu",
		ft_cd(args1, env) == 0);

	char *args2[] = {"cd", "..", NULL};
	print_test_result("cd vers répertoire relatif",
		ft_cd(args2, env) == 0);

	char *args3[] = {"cd", NULL};
	print_test_result("cd sans arguments (HOME)",
		ft_cd(args3, env) == 0);
}

static void	test_env(t_env *env)
{
	print_test_header("Test de env");
	print_test_result("env sans arguments",
		ft_env(env) == 0);
}

static void	test_export(t_env *env)
{
	print_test_header("Test de export");

	char *args1[] = {"export", "TEST=value", NULL};
	print_test_result("export variable simple",
		ft_export(args1, env) == 0);

	char *args2[] = {"export", "TEST", NULL};
	print_test_result("export sans valeur",
		ft_export(args2, env) == 0);

	char *args3[] = {"export", NULL};
	print_test_result("export sans arguments",
		ft_export(args3, env) == 0);
}

static void	test_unset(t_env *env)
{
	print_test_header("Test de unset");

	char *args1[] = {"unset", "TEST", NULL};
	print_test_result("unset variable existante",
		ft_unset(args1, env) == 0);

	char *args2[] = {"unset", "NONEXISTENT", NULL};
	print_test_result("unset variable inexistante",
		ft_unset(args2, env) == 0);

	char *args3[] = {"unset", NULL};
	print_test_result("unset sans arguments",
		ft_unset(args3, env) == 0);
}

int	main(void)
{
	t_env	*env;

	printf("\033[1;33m🧪 Démarrage des tests du module builtins\033[0m\n");

	env = create_test_env();
	if (!env)
	{
		printf("Erreur lors de la création de l'environnement de test\n");
		return (1);
	}

	test_echo();
	test_pwd();
	test_cd(env);
	test_env(env);
	test_export(env);
	test_unset(env);

	printf("\n\033[1;33m=== Résumé des tests ===\033[0m\n");
	printf("Tests passés: %d/%d (%.2f%%)\n",
		g_passed_tests, g_total_tests,
		(g_passed_tests * 100.0) / g_total_tests);

	env_free(env);
	return (g_passed_tests == g_total_tests ? 0 : 1);
}
