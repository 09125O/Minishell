/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:53:11 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/10 22:54:22 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>

typedef enum {
    TOKEN_WORD,        // Mot ou argument
    TOKEN_PIPE,        // Opérateur de pipeline (|)
    TOKEN_REDIRECT_IN, // Redirection d'entrée (<)
    TOKEN_REDIRECT_OUT,// Redirection de sortie (>)
    TOKEN_APPEND,      // Redirection de sortie en mode append (>>)
    TOKEN_HEREDOC,     // Redirection d'entrée avec heredoc (<<)
    TOKEN_EOF          // Fin de l'entrée
} t_token_type;

// Structure d'un token
typedef struct s_token {
    char *value;           // Valeur du token (par exemple, le nom d'un fichier)
    t_token_type type;     // Type du token
    struct s_token *next;  // Pointeur vers le token suivant
} t_token;

// Prototypes de fonctions
t_token *lexer(char *input, int *error_code);
void free_token_list(t_token *token);

// Fonctions utilitaires
int is_whitespace(char c);
int is_operator(char c);
int is_quote(char c);
int is_word_char(char c);
void skip_whitespace(char *input, int *i);

// Fonctions de création de tokens
t_token *create_token(char *value, t_token_type type);
t_token *create_word_token(char *input, int *i);
t_token *create_operator_token(char *input, int *i);

// Gestion des erreurs
typedef enum {
    LEXER_SUCCESS = 0,
    LEXER_ERROR_UNCLOSED_QUOTE = 1,
    LEXER_ERROR_INVALID_TOKEN = 2,
} LexerError;

#endif
