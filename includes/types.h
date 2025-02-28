#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>
# include <sys/types.h>

/* Types de commandes */
typedef enum e_cmd_type
{
	CMD_SIMPLE,
	CMD_PIPELINE
}	t_cmd_type;

/* Types d'erreurs */
typedef enum e_error
{
	E_NONE = 0,
	E_SYNTAX = 1,
	E_MEMORY = 2,
	E_COMMAND_EXPECTED = 3,
	E_ARGUMENT_COUNT = 4,
	E_MEMORY_ALLOCATION = 5,
	E_ARGUMENT_FILLING = 6,
	E_PIPE_CREATION = 7,
	E_FORK_FAILED = 8,
	E_REDIRECTION = 9
}	t_error;

/* Types de redirections */
typedef enum e_redir_type
{
	REDIR_IN = 3,      /* TOKEN_REDIRECT_IN */
	REDIR_OUT = 4,     /* TOKEN_REDIRECT_OUT */
	REDIR_APPEND = 5,  /* TOKEN_APPEND */
	REDIR_HEREDOC = 6  /* TOKEN_HEREDOC */
}	t_redir_type;

/* Structure pour les variables d'environnement */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* Structure pour les informations d'erreur */
typedef struct s_error_info
{
	int		code;
	char	*message;
}	t_error_info;

/* Structure pour le contexte du shell */
typedef struct s_shell_ctx
{
	t_env			*env;
	char			*cwd;
	char			*old_pwd;
	int				last_status;
	int				shell_pid;
	bool			is_interactive;
	t_error_info	last_error;
}	t_shell_ctx;

/* Structure pour les redirections */
typedef struct s_redirection
{
	int					type;
	char				*file;
	int					fd;
	struct s_redirection	*next;
}	t_redirection;

/* Structure pour les commandes */
typedef struct s_command
{
	t_cmd_type		type;
	char			**args;
	t_redirection	*redirections;
	int				pipe_in;
	int				pipe_out;
	int				pid;
	struct s_command	*commands;
	struct s_command	*next;
}	t_command;

/* Structure pour la gestion des descripteurs de fichiers */
typedef struct s_fd_backup
{
	int	stdin_fd;
	int	stdout_fd;
	int	stderr_fd;
}	t_fd_backup;

/* Structure pour l'exécution */
typedef struct s_exec
{
	t_command	*cmds;
	int		cmd_count;
	pid_t		*pids;
	int		**pipes;
	t_fd_backup	*fd_backup;
	int		last_exit_code;
	t_shell_ctx	*ctx;
}	t_exec;

#endif
