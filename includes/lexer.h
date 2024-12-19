/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:17:21 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/18 00:25:01 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_HEREDOC,
    TOKEN_APPEND,
    TOKEN_EOF
}   t_token_type;

typedef struct s_token
{
    char            *value;
    t_token_type    type;
    struct s_token  *next;
}   t_token;

/* lexer.c */
t_token     *lexer(char *input);

/* lexer_utils.c */
int         is_whitespace(char c);
int         is_operator(char c);
void        skip_whitespace(char *input, int *i);
int         is_quote(char c);
int         is_word_char(char c);

/* token_creator.c */
t_token     *create_word_token(char *input, int *i);
t_token     *create_operator_token(char *input, int *i);
char        *extract_word(char *input, int *i, int *status);

/* token_type.c */
t_token_type    get_token_type(char *input, int *i);
int             is_redirection(char c);

/* token_list.c */
t_token         *create_token(char *value, t_token_type type);
void            add_token(t_token **head, t_token *new_token);
void            free_token_list(t_token *token);
t_token         *get_last_token(t_token *head);

#endif
