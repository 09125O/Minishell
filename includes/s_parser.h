#ifndef S_PARSER_H
# define S_PARSER_H

# include <stdlib.h>
# include "types.h"
# include "s_lexer.h"

/* Déclarations anticipées */
// typedef struct s_token t_token;
// typedef enum e_token_type t_token_type;

/* Structure pour le contexte du parser */
typedef struct s_parser_ctx
{
	t_token			*current;
	t_error			error;
	char			*error_msg;
}	t_parser_ctx;

/* Fonctions principales */
t_command	**parse_tokens(t_token *tokens);
void		free_command(t_command *cmd);
void		free_commands(t_command **commands);
int			count_commands(t_command **commands);
int			count_command_list(t_command *cmd);
int			is_redirection_token(t_token_type type);
void		skip_whitespace_tokens(t_token **current);

/* Gestion des erreurs */
void		set_parser_error(t_parser_ctx *ctx, t_error error, const char *msg);
void		init_parser_context(t_parser_ctx *ctx, t_token *tokens);

/* Navigation des tokens */
t_token		*next_token(t_parser_ctx *ctx);
t_token		*peek_token(t_parser_ctx *ctx);

/* Fonctions de parsing */
t_command		*parse_simple_command(t_parser_ctx *ctx);
t_command		*parse_pipeline(t_parser_ctx *ctx);
t_redirection	*parse_redirection(t_parser_ctx *ctx);

/* Fonctions utilitaires */
t_command		*create_command(t_cmd_type type);
t_redirection	*create_redirection(t_redir_type type, char *file);
void			free_redirections(t_redirection *redir);
void			free_command_args(char **args);

/* Fonctions de traitement des arguments */
int				count_args(t_token *token);
char			**create_args_array(t_token *token, int count);
void			add_redirection(t_redirection **head, t_redirection *new);
int				is_redirection_token(t_token_type type);
t_redir_type	get_redirection_type(t_token_type token_type);

/* Validation et traitement des arguments */
int				fill_args_array(char **args, t_token *token, int count);
int				validate_args(t_token *token, int count);
int				check_args_limit(int count);
int				prepare_args(t_token *token, int *count);
char			**process_args(t_token *token, int count);

#endif
