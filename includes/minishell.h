/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:35:21 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/26 20:19:53 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Includes système */
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

/* Includes locaux */
# include "libft.h"
# include "types.h"
# include "env.h"
# include "shell_ctx.h"
# include "executor.h"
# include "s_parser.h"
# include "s_lexer.h"
# include "signals.h"
# include "builtins.h"
# include "utils.h"

/* Constantes */
# define EXIT_SHELL 42
# define MAX_PATH_LEN 4096
# define MAX_ARGS 4096
# define MAX_ENV_SIZE 4096
# define PIPE_READ 0
# define PIPE_WRITE 1

/* Structure globale */
typedef struct s_global
{
	int			exit_status;
	int			signal_received;
	t_shell_ctx	*ctx;
}	t_global;

/* Variable globale */
extern t_global	g_global;

/* Fonctions de gestion des signaux */
void	setup_signals(void);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);

/* Fonctions de gestion des tokens */
void	free_tokens(t_token *tokens);
int		count_tokens(t_token *tokens);

/* Fonctions de gestion des commandes */
int		count_commands(t_command **commands);
void	free_commands(t_command **commands);

/* Fonctions d'erreur */
void	ft_error(const char *cmd, const char *arg, const char *msg);
void	print_error(const char *prefix, const char *msg);
void	exit_error(const char *msg, int code);

#endif
