/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:10:21 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/25 18:05:57 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_lexer.h"

void	set_error(t_lexer_error_info *error, t_lexer_error code,
	char *message, int position)
{
	if (error)
	{
		error->code = code;
		error->message = message;
		error->position = position;
	}
}

int	validate_env_var(char *input, int i, t_lexer_error_info *error)
{
	if (!input[i] || input[i] != '$')
		return (1);
	i++;
	if (!input[i])
		return (1);
	if (input[i] == '_')
		return (0);
	if (!is_env_first_char(input[i]))
	{
		set_error(error, LEXER_ERROR_INVALID_ENV_VAR,
			"Variable d'environnement invalide", i);
		return (0);
	}
	i++;
	while (input[i])
	{
		if (!is_env_char(input[i]) && input[i] != '_')
		{
			set_error(error, LEXER_ERROR_INVALID_ENV_VAR,
				"Variable d'environnement invalide", i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	validate_operator(char *input, int i, t_lexer_error_info *error)
{
	char	current;
	char	next;

	current = input[i];
	next = input[i + 1];
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
		if ((next == current && input[i + 2] == current) ||
			(next && next != current && (next == '<' || next == '>')))
		{
			set_error(error, LEXER_ERROR_INVALID_OPERATOR,
				"Opérateur de redirection invalide", i);
			return (0);
		}
		if (next == ' ' && input[i + 2] == current)
		{
			set_error(error, LEXER_ERROR_INVALID_OPERATOR,
				"Opérateur de redirection invalide", i);
			return (0);
		}
		return (1);
	}
	return (1);
}
