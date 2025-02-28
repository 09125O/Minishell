/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:30:21 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/26 23:42:17 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "shell_ctx.h"
#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include "libft.h"

t_global	g_global;

static void	init_terminal(void)
{
	struct termios	term;

	ft_putstr_fd("DEBUG: Initialisation du terminal\n", 2);

	// Vérifier si l'entrée standard est un terminal
	if (!isatty(STDIN_FILENO))
	{
		ft_putstr_fd("DEBUG: L'entrée standard n'est pas un terminal, initialisation ignorée\n", 2);
		return;
	}

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		ft_putstr_fd("minishell: error getting terminal attributes\n", 2);
		exit(1);
	}

	// Désactiver l'affichage des caractères de contrôle (comme Ctrl+C, Ctrl+\)
	term.c_lflag &= ~ECHOCTL;

	// Désactiver également d'autres flags qui pourraient interférer
	term.c_lflag |= ISIG;    // Activer les signaux générés par le terminal
	term.c_lflag &= ~ECHO;   // Désactiver l'écho temporairement
	term.c_lflag |= ECHO;    // Réactiver l'écho

	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		ft_putstr_fd("minishell: error setting terminal attributes\n", 2);
		exit(1);
	}
	ft_putstr_fd("DEBUG: Terminal initialisé avec succès\n", 2);
}

static int	process_input(char *input, t_shell_ctx *ctx)
{
	t_token		*tokens;
	t_command	**commands;
	int			status;

	ft_putstr_fd("DEBUG: Traitement de l'entrée: ", 2);
	ft_putstr_fd(input, 2);
	ft_putstr_fd("\n", 2);

	status = 0;
	if (!input || !*input)
		return (0);
	add_history(input);

	// Vérifier si c'est la commande exit sans arguments
	if (ft_strcmp(input, "exit") == 0)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		return (EXIT_SHELL);
	}

	tokens = lexer(input, ctx->env);
	if (!tokens)
	{
		set_shell_error(ctx, 1, "Lexer error");
		g_global.exit_status = 1;
		return (0);
	}
	commands = parse_tokens(tokens);
	if (!commands)
	{
		set_shell_error(ctx, 1, "Parser error");
		free_tokens(tokens);
		g_global.exit_status = 1;
		return (0);
	}
	if (commands)
	{
		// Sauvegarder les descripteurs de fichiers standard
		t_fd_backup *backup = save_fds();

		status = execute_commands(commands, count_commands(commands), ctx);

		// Mettre à jour le statut de sortie
		g_global.exit_status = status;
		ctx->last_status = status;

		// Restaurer les descripteurs de fichiers standard
		if (backup)
			restore_fds(backup);

		free_commands(commands);

		// Si execute_commands retourne EXIT_SHELL, c'est que la commande exit a été exécutée
		if (status == EXIT_SHELL)
			return (EXIT_SHELL);
	}
	free_tokens(tokens);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	int			status;
	int			is_pipe_input;
	char		buffer[4096];
	ssize_t		bytes_read;

	ft_putstr_fd("DEBUG: Démarrage du minishell\n", 2);

	(void)argc;
	(void)argv;
	g_global.ctx = init_shell_ctx(envp);
	if (!g_global.ctx)
	{
		ft_putstr_fd("minishell: error initializing shell context\n", 2);
		return (1);
	}
	ft_putstr_fd("DEBUG: Contexte du shell initialisé\n", 2);

	init_terminal();
	signals_set_state(SIGNAL_INTERACTIVE);
	g_global.exit_status = 0;
	g_global.signal_received = 0;

	ft_putstr_fd("DEBUG: Entrée dans la boucle principale\n", 2);

	// Vérifier si l'entrée provient d'un pipe
	is_pipe_input = !isatty(STDIN_FILENO);

	if (is_pipe_input)
	{
		// Lire depuis l'entrée standard (pipe)
		bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			// Supprimer le caractère de nouvelle ligne à la fin si présent
			if (bytes_read > 0 && buffer[bytes_read - 1] == '\n')
				buffer[bytes_read - 1] = '\0';

			ft_putstr_fd("DEBUG: Entrée reçue du pipe: ", 2);
			ft_putstr_fd(buffer, 2);
			ft_putstr_fd("\n", 2);

			process_input(buffer, g_global.ctx);
		}

		ft_putstr_fd("DEBUG: Sortie de la boucle principale\n", 2);
		clear_history();
		free_shell_ctx(g_global.ctx);
		return (g_global.exit_status);
	}

	while (1)  // Boucle infinie, on ne sort que sur commande exit ou Ctrl+D
	{
		// Réinitialiser le signal reçu
		g_global.signal_received = 0;

		// S'assurer que les signaux sont correctement configurés pour le mode interactif
		signals_set_state(SIGNAL_INTERACTIVE);

		// Mettre à jour le contexte du shell
		update_shell_ctx(g_global.ctx);

		ft_putstr_fd("DEBUG: Attente de l'entrée utilisateur\n", 2);
		input = readline("\033[1;32mminishell\033[0m$ ");
		ft_putstr_fd("DEBUG: Entrée reçue: ", 2);
		if (input)
			ft_putstr_fd(input, 2);
		else
			ft_putstr_fd("NULL (Ctrl+D)", 2);
		ft_putstr_fd("\n", 2);

		if (!input)  // Ctrl+D
		{
			ft_putstr_fd("\nexit\n", 1);
			break;
		}

		if (*input)  // Si l'entrée n'est pas vide
		{
			status = process_input(input, g_global.ctx);
			if (status == EXIT_SHELL)  // Sortir uniquement si EXIT_SHELL est retourné
			{
				free(input);
				break;
			}
		}

		free(input);
	}

	ft_putstr_fd("DEBUG: Sortie de la boucle principale\n", 2);
	clear_history();
	free_shell_ctx(g_global.ctx);
	return (g_global.exit_status);
}
