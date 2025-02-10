/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:54:52 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/10 22:55:12 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include "lexer.h"

// Structure d'une redirection
typedef struct s_redirect {
    char *file;                // Fichier de redirection
    t_token_type type;         // Type de redirection (<, >, >>, <<)
    struct s_redirect *next;   // Pointeur vers la redirection suivante
} t_redirect;

// Structure d'une commande
typedef struct s_command {
    char **args;               // Arguments de la commande
    t_redirect *redirects;     // Liste des redirections
    struct s_command *next;    // Pointeur vers la commande suivante (pour les pipelines)
} t_command;

// Structure d'un nœud AST
typedef struct s_ast {
    t_command *cmd;            // Commande associée au nœud
    struct s_ast *left;        // Sous-arbre gauche (non utilisé dans un pipeline simple)
    struct s_ast *right;       // Sous-arbre droit (pour les pipelines)
} t_ast;

// Prototypes de fonctions
t_ast *parser(t_token *tokens, int *error_code);
void free_ast(t_ast *ast);

// Fonctions de création de structures
t_command *create_command(void);
t_redirect *create_redirect(char *file, t_token_type type);
t_ast *create_ast_node(t_command *cmd);

// Fonctions utilitaires
void add_arg_to_command(t_command *cmd, char *arg);
void add_redirect_to_command(t_command *cmd, t_redirect *redir);
void free_command(t_command *cmd);
void free_redirect(t_redirect *redirect);

// Gestion des erreurs
typedef enum {
    PARSER_SUCCESS = 0,
    PARSER_ERROR_INVALID_SYNTAX = 1,
    PARSER_ERROR_MISSING_ARGUMENT = 2,
} ParserError;

#endif
