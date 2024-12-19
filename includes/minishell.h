/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:16:46 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/18 01:01:59 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* minishell.h */
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include "libft.h"

/* Seule variable globale autorisée pour les signaux */
extern int g_signal_status;

/* Structures de base */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*env;
	char	**env_array;
	int		exit_status;
	int		in_heredoc;
	char	*input;
	char	*pwd;
	char	*oldpwd;
}	t_shell;

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define ERROR -1

/* Inclure les autres headers après la définition des structures */
# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "signals.h"
# include "utils.h"
# include "builtins.h"

/* Prototypes pour main/ uniquement */
int		main(int argc, char **argv, char **envp);
void	init_shell(t_shell *shell, char **envp);

#endif
