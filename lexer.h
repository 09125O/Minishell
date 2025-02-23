/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:53:11 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/23 14:55:15 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>

// Types d'erreurs
typedef enum {
    LEXER_SUCCESS = 0,
    LEXER_ERROR_UNCLOSED_QUOTE = 1,
    LEXER_ERROR_INVALID_TOKEN = 2,
    LEXER_ERROR_INVALID_OPERATOR = 3,
    LEXER_ERROR_INVALID_ENV_VAR = 4,
    LEXER_ERROR_UNEXPECTED_EOF = 5,
    LEXER_ERROR_MEMORY = 6
} LexerError;

// Structure pour les messages d'erreur
typedef struct s_error_info {
    LexerError code;
    char *message;
    int position;
} t_error_info;

// Types de tokens
typedef enum {
    TOKEN_WORD,        // Mot ou argument
    TOKEN_PIPE,        // Opérateur de pipeline (|)
    TOKEN_REDIRECT_IN, // Redirection d'entrée (<)
    TOKEN_REDIRECT_OUT,// Redirection de sortie (>)
    TOKEN_APPEND,      // Redirection de sortie en mode append (>>)
    TOKEN_HEREDOC,     // Redirection d'entrée avec heredoc (<<)
    TOKEN_ENV_VAR,     // Variable d'environnement ($VAR)
    TOKEN_SQUOTE,      // Contenu entre quotes simples (pas d'interprétation)
    TOKEN_DQUOTE,      // Contenu entre quotes doubles (interprétation de $)
    TOKEN_EOF          // Fin de l'entrée
} t_token_type;

// Structure d'un token
typedef struct s_token {
    char *value;           // Valeur du token (par exemple, le nom d'un fichier)
    t_token_type type;     // Type du token
    struct s_token *next;  // Pointeur vers le token suivant
} t_token;

// Prototypes de fonctions principales
t_token *lexer(char *input, int *error_code);
void free_token_list(t_token *token);
void add_token(t_token **head, t_token *new_token);
t_token *get_last_token(t_token *head);

// Fonctions de traitement des tokens
int process_token(t_token **head, char *input, int *i, t_error_info *error);
int process_word(t_token **head, char *input, int *i);
int process_operator(t_token **head, char *input, int *i);

// Fonctions utilitaires
int is_whitespace(char c);
int is_operator(char c);
int is_quote(char c);
int is_word_char(char c);
int is_escapable_char(char c);
int is_escaped(char *input, int i);
int is_env_char(char c);
void skip_whitespace(char *input, int *i);

// Fonctions de création de tokens
t_token *create_token(char *value, t_token_type type);
t_token *create_word_token(char *input, int *i);
t_token *create_operator_token(char *input, int *i);
t_token *create_env_var_token(char *input, int *i);
t_token_type get_token_type(char *input, int *i);

// Fonctions d'extraction de mots
char *extract_word(char *input, int *i);
int get_word_length(char *input, int i);

// Fonctions de gestion d'erreurs
void set_error(t_error_info *error, LexerError code, char *message, int position);
int validate_env_var(char *input, int i, t_error_info *error);
int validate_operator(char *input, int i, t_error_info *error);

// Fonctions de gestion des quotes
char *extract_quoted_word(char *input, int *i, char quote_type, t_error_info *error);
int process_quotes(t_token **head, char *input, int *i, t_error_info *error);

#endif
