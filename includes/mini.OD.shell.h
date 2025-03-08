/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.OD.shell.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 23:51:55 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_OD_SHELL_H
# define MINI_OD_SHELL_H

# include "../includes/builtins.h"
# include "../includes/exec.h"
# include "../includes/parse_build.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE 1
# define FAILURE_VOID 2
# define BUILD_FAILURE -1
// note: return 0 : success
// note: return 1 : general error
// note: return 2 : Incorrect Usage or Invalid Option
//  * - BUILD_FAILURE (-1): Severe or unexpected error,
//  *   (often due to resource allocation failure or similar critical problems)
//  * - SUCCESS (0): Function succeeded without issues
//  * - FAILURE (1): General failure or expected failure condition
//  * - FAILURE_VOID (2): Specific type of failure,
//  *   (possibly for a void return or non-critical issue)
//  * - BUILD_FAILURE (-1): Severe or unexpected error,
//  *   (often due to resource allocation failure or similar critical problems)
//  * - SUCCESS (0): Function succeeded without issues
//  * - FAILURE (1): General failure or expected failure condition
//  * - FAILURE_VOID (2): Specific type of failure,
//  *   (possibly for a void return or non-critical issue)

# define PROMPT_NAME "mini.OD.shell"

# define IS_DIRECTORY 126
# define CMD_NOT_FOUND 127
# define SIG_OFFSET 128
//OFFSET usefull if we use echo $?

# define PROMPT "\001\033[1;36m\002mini.OD.shell> \001\033[0m\002"
# define DEFAULT_ENV "MINISHELL=mini.OD.shell"

typedef struct s_shell
{
	int				default_in;
	int				default_out;
	unsigned char	exit_code;
	pid_t			*pids;
	t_exec			*exec;
	int				pid_count;
	int				exec_count;
	t_env			*env;
}					t_shell;

typedef struct s_env
{
	char			*id;
	char			*value;
	char			*env_line;
	t_env			*next;
}					t_env;

typedef struct s_signal
{
	int				end_heredoc;
	int				signal_code;

}					t_signal;

extern t_signal		g_signal;

/************ MAIN *************/
/*main (shell)*/
t_shell			*init_shell(char *env[]);
int				process_input(t_shell *content, char *line);
int				init_exec(t_shell *content, t_token **token);
int				read_n_loop(t_shell *content);
t_env			*dup_env(char *env[]);
int				check_line_empty(char *line);

/*env*/
t_env			*env_create(char *env_id, char *env_value, char *env_line);
t_env			*set_default_env(void);
char			*get_env_id(char *env_line);
char			*get_env_value(char *env_line);
int				env_add_back(t_env **head, t_env *new);
void			env_free(t_env *env);
void			env_delete_1node(t_env *env);

/************ LEXING ************/
/*lexing*/
t_token			*lex_tokenize_each_wd(char *str, t_shell *content);
t_token			*lexing(t_shell *content, char *input_line);

/*lexing helper*/
t_token_type	lex_get_token_meta_type(char *str);
int				lex_ft_1tokenlen(char *str, t_token_type type);
int				ft_token_str_len(char *str);
int				check_meta_char(char c);

/*token*/
t_token			*token_create(char *token_value, int n, t_token_type type,
					t_shell *content);
int				token_add_back(t_token **head, t_token *new_token);
void			token_free(t_token *token);

/************ SIGNALS ************/
void			init_signals(void);
void			signals_heredoc(int signum);
void			sigint_exec(int signum);
int				sig_event(void);

/************ MAIN FREE ************/
void			free_all_shell(t_shell *content);
void			free_after_process(t_shell *content, t_token *token);

#endif
