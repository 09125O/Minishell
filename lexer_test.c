/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:08:41 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/23 14:21:24 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

// Fonction utilitaire pour afficher le type de token
const char *token_type_to_str(t_token_type type)
{
    switch (type)
    {
        case TOKEN_WORD: return "WORD";
        case TOKEN_PIPE: return "PIPE";
        case TOKEN_REDIRECT_IN: return "REDIR_IN";
        case TOKEN_REDIRECT_OUT: return "REDIR_OUT";
        case TOKEN_APPEND: return "APPEND";
        case TOKEN_HEREDOC: return "HEREDOC";
        case TOKEN_ENV_VAR: return "ENV_VAR";
        case TOKEN_SQUOTE: return "SQUOTE";
        case TOKEN_DQUOTE: return "DQUOTE";
        case TOKEN_EOF: return "EOF";
        default: return "UNKNOWN";
    }
}

// Fonction pour afficher une liste de tokens
void print_tokens(t_token *head)
{
    t_token *current = head;
    int i = 0;

    printf("=== Tokens ===\n");
    while (current)
    {
        printf("Token %d: type=%s, value='%s'\n",
            i++, token_type_to_str(current->type),
            current->value ? current->value : "NULL");
        current = current->next;
    }
    printf("============\n\n");
}

// Fonction pour tester un cas
void test_case(const char *input, const char *test_name)
{
    int error_code;
    printf("Test: %s\nInput: '%s'\n", test_name, input);

    t_token *tokens = lexer((char *)input, &error_code);

    if (error_code != LEXER_SUCCESS)
        printf("Error code: %d\n", error_code);
    else
        print_tokens(tokens);

    free_token_list(tokens);
}

int main(void)
{
    // Test 1: Quotes simples
    test_case("echo 'Hello World'", "Simple quotes");

    // Test 2: Quotes doubles
    test_case("echo \"Hello World\"", "Double quotes");

    // Test 3: Variables d'environnement
    test_case("echo $HOME", "Environment variable");

    // Test 4: Variables dans quotes simples
    test_case("echo '$HOME'", "Env var in simple quotes");

    // Test 5: Variables dans quotes doubles
    test_case("echo \"$HOME\"", "Env var in double quotes");

    // Test 6: Redirections
    test_case("echo hello > file.txt", "Output redirection");

    // Test 7: Pipes
    test_case("ls | grep test", "Pipe");

    // Test 8: Quotes non fermées (test d'erreur)
    test_case("echo \"Hello", "Unclosed quote");

    // Test 9: Mélange de quotes
    test_case("echo 'Hello \"World\"'", "Mixed quotes");

    // Test 10: Caractères échappés
    test_case("echo Hello\\ World", "Escaped space");

    return (0);
}
