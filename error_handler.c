/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:08:41 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/23 14:08:30 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void set_error(t_error_info *error, LexerError code, char *message, int position)
{
    if (error)
    {
        error->code = code;
        error->message = message;
        error->position = position;
    }
}

int validate_env_var(char *input, int i, t_error_info *error)
{
    if (!input[i] || input[i] != '$')
        return (1);

    i++; // Skip $
    // Vérifie si le premier caractère est valide (lettre ou underscore)
    if (!input[i] || !(((input[i] >= 'A' && input[i] <= 'Z') ||
        (input[i] >= 'a' && input[i] <= 'z')) || input[i] == '_'))
    {
        set_error(error, LEXER_ERROR_INVALID_ENV_VAR,
            "Variable d'environnement invalide: doit commencer par une lettre ou '_'", i);
        return (0);
    }

    // Vérifie le reste des caractères
    while (input[i] && is_env_char(input[i]))
        i++;

    return (1);
}

int validate_operator(char *input, int i, t_error_info *error)
{
    char current = input[i];
    char next = input[i + 1];
    if (current == '|')
    {
        if (next == '|')
        {
            set_error(error, LEXER_ERROR_INVALID_OPERATOR,
                "Opérateur '||' non supporté", i);
            return (0);
        }
        return (1);
    }
    if (current == '<' || current == '>')
    {
        if (next == current) // << ou >>
        {
            if (input[i + 2] == current) // >>> ou <<<
            {
                set_error(error, LEXER_ERROR_INVALID_OPERATOR,
                    "Opérateur de redirection invalide", i);
                return (0);
            }
            return (1);
        }
        return (1);
    }
    return (1);
}
