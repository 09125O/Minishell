#ifndef S_LEXER_H
# define S_LEXER_H

# include <stdlib.h>
# include "types.h"

/* Déclaration anticipée */
typedef struct s_shell_ctx t_shell_ctx;

/* Types d'erreurs */
typedef enum e_lexer_error
{
	LEXER_SUCCESS = 0,
	LEXER_ERROR_UNCLOSED_QUOTE = 1,
	LEXER_ERROR_INVALID_TOKEN = 2,
	LEXER_ERROR_INVALID_OPERATOR = 3,
	LEXER_ERROR_INVALID_ENV_VAR = 4,
	LEXER_ERROR_UNEXPECTED_EOF = 5,
	LEXER_ERROR_MEMORY = 6
}	t_lexer_error;

/* Structure pour les erreurs du lexer */
typedef struct s_lexer_error_info
{
	t_lexer_error	code;
	char			*message;
	int				position;
}	t_lexer_error_info;

/* Types de tokens */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_OPERATOR,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_EOF
}	t_token_type;

/* Structure pour les tokens */
typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

/* Structure pour le contexte du lexer */
typedef struct s_lexer_ctx
{
	char				*input;
	int					position;
	t_lexer_error_info	error;
	struct s_env		*env;
	t_shell_ctx			*shell_ctx;
}	t_lexer_ctx;

/* Fonctions principales */
t_token		*lexer(char *input, struct s_env *env);
void		free_token(t_token *token);
void		free_token_list(t_token *head);

/* Fonctions utilitaires */
t_token		*create_token(t_token_type type, char *value);
void		add_token(t_token **head, t_token *new_token);
int			is_operator_char(char c);
int			is_whitespace(char c);
int			is_quote(char c);
int			is_special_char(char c);

/* Fonctions de parsing */
char		*parse_word(char *input, int *pos);
char		*parse_operator(char *input, int *pos);
char		*parse_quoted_string(char *input, int *pos, char quote);
t_token		*handle_operator(char *input, int *pos);

/* Gestion des erreurs */
void		set_lexer_error(int *error_code, int code);
int			handle_lexer_error(t_token **head, int error_code);

/* Fonctions de gestion des tokens */
t_token		*get_last_token(t_token *head);

/* Fonctions de traitement */
int			process_operator(t_token **head, t_lexer_ctx *ctx);
int			process_quotes(t_token **head, char *input, int *i,
				t_lexer_ctx *ctx);
int			process_word(t_token **head, char *input, int *i);
t_token		*create_word_token(char *input, int *i);
t_token		*create_env_var_token(char *input, int *i, struct s_env *env);

/* Fonctions de validation */
int			validate_env_var(char *input, int i, t_lexer_error_info *error);
int			validate_operator(char *input, int i, t_lexer_error_info *error);
void		set_error(t_lexer_error_info *error, t_lexer_error code,
				char *message, int position);

/* Fonctions utilitaires */
int			is_word_char(char c);
int			is_escapable_char(char c);
int			is_escaped(char *input, int i);
int			is_env_char(char c);
int			is_env_first_char(char c);
int			is_operator(char c);

#endif
