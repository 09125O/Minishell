/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"

/** PRS_CHECK_QUOTES_VALID
 * validation step -> prevent errors caused by unclosed or invalid
	quotes before running the more complex functions.
 * @note *EXTRA CONDITION after ft_quotes_len(),
 * 			if (str[i] == '\0')
 * 				return (FAILURE);
 *  -> to detect unmatched or missing closing quotes.
 *
 * If the function encounters the end of the string ('\0')
		after processing a quote, but without finding a matching
		closing quote, it means that the quotes are improperly terminated.
 * This can happen if:
    An opening quote exists (' or "), but there is no corresponding
		closing quote at the end of the string.
	The string is incomplete or malformed.
*/
int	prs_check_quotes_valid(t_token *token)
{
	int		i;
	char	*str;

	while (token != NULL)
	{
		if (token->type == STR)
		{
			i = 0;
			str = token->value;
			while (str[i])
			{
				if (str[i] == '\'' || str[i] == '\"')
					i += ft_quotes_len(&(str[i]), str[i]);
				if (str[i] == '\0')
					return (FAILURE);
				i++;
			}
		}
		token = token->next;
	}
	return (SUCCESS);
}

/** PRS_QUOTES_TOKENS
 * Parse a string into tokens by:
 * - Identifying quoted and unquoted parts of the input string.
 * - Creating tokens for each segment (quoted or unquoted).
 * - Returning a linked list of tokens representing the parsed segments.
 * (1) Loop input_str
 * [IF] the current character is a single or double quote
 * -> Extracts the content inside the quotes + creates a token for it
 * -> Skipclosing quote by moving `i` forward by len of processed str
 * [ELSE] not quotes
 * -> Create a raw token for the unquoted part
 * -> Move `i` forward by the length of the raw segment minus 1
 * (since the `i++` at the end of the loop increments it further)
 * (2) If token creation failed -> return NULL
 * (3) Add the newly created token to the list of tokens
 * @note new_token = token_create("", 0, STR, content);
 * - Handle empty quotes
 * - Skip the quote
 * @return result (newly created token)
 */
/**
 * @note int *i
 * - use a pointer to modify it across different functions
 * - Able to modify the og counter value across both functions
 * *i += ft_strlen(new_token->value) + 1; (This updates the original i)
 * handle_quoted_token(..., &i); (i is updated after function return)
*/
// Helper function to process a single token
static t_token	*process_single_token(char *str, t_shell *content, int *i)
{
	t_token	*new_token;

	if (str[0] == '\'' || str[0] == '\"')
	{
		new_token = prs_get_quoted_str(str, str[0], content);
		if (!new_token)
		{
			new_token = token_create("", 0, STR, content);
			*i += 1;
		}
		else
			*i += ft_strlen(new_token->value) + 1;
	}
	else
	{
		new_token = token_create(str, ft_rogue_len(str), STR, content);
		*i += ft_strlen(new_token->value) - 1;
	}
	return (new_token);
}

t_token	*prs_quotes_to_tokens(char *input_str, t_shell *content)
{
	int		i;
	t_token	*token;
	t_token	*new_token;

	i = 0;
	token = NULL;
	while (input_str[i])
	{
		new_token = process_single_token(&(input_str[i]), content, &i);
		if (!new_token)
			return (NULL);
		token_add_back(&token, new_token);
		i++;
	}
	return (token);
}

/*
t_token	*prs_quotes_to_tokens(char *input_str, t_shell *content)
{
	int		i;
	t_token	*token;
	t_token	*new_token;

	i = 0;
	token = NULL;
	new_token = NULL;
	while (input_str[i])
	{
		if (input_str[i] == '\'' || input_str[i] == '\"')
		{
			new_token = prs_get_quoted_str(&(input_str[i]),
							input_str[i], content);
			if (!new_token)
			{
				new_token = token_create("", 0, STR, content);
				i += 1;
			}
			else
				i += ft_strlen(new_token->value) + 1;
		}
		else
		{
			new_token = token_create(&(input_str[i]), ft_rogue_len(&(input_str[i])),
							STR, content);
			i += ft_strlen(new_token->value) - 1;
		}
		if (!new_token)
			return (NULL);
		token_add_back(&token, new_token);
		i++;
	}
	return (token);
}*/

/**handle quotes n expand env
 * Processes tokens in a linked list of tokens (t_token) by handling:
 * (1) Iterate through all tokens in the linked list (= input string)
 * (2) Process tokens of type STRING:
 * 	-1 Parse quotes within the token's value and return a list of tokens
 * 	-2 Expand environment variables within the parsed tokens
 */
int	prs_handle_quotes_n_expand_env(t_token *token)
{
	t_token	*input_str;

	while (token != NULL)
	{
		if (token->type == STR)
		{
			input_str = prs_quotes_to_tokens(token->value, token->content);
			prs_expand_env(input_str);
			if (token->value)
				free(token->value);
			token->value = prs_tokens_combine(input_str);
			token_free(input_str);
		}
		token = token->next;
	}
	return (SUCCESS);
}

/* OG prs_quotes_to_tokens (correct)
t_token	*prs_quotes_to_tokens(char *input_str, t_shell *content)
{
	int		i;
	t_token	*token;
	t_token	*new_token;

	i = 0;
	token = NULL;
	new_token = NULL;
	while (input_str[i])
	{
		if (input_str[i] == '\'' || input_str[i] == '\"')
		{
			new_token = prs_get_quoted_str(&(input_str[i]),
							input_str[i], content);
			if (!new_token)
			{
				new_token = token_create("", 0, STR, content);
				i += 1;
			}
			else
				i += ft_strlen(new_token->value) + 1;
		}
		else
		{
			new_token = token_create(&(input_str[i]), ft_rogue_len(&(input_str[i])),
							STR, content);
			i += ft_strlen(new_token->value) - 1;
		}
		if (!new_token)
			return (NULL);
		token_add_back(&token, new_token);
		i++;
	}
	return (token);
}

////////////////////////////////////////
Modified vr. (incorrect)
static t_token	*handle_quoted_token(char *str, char quote,
					t_shell *content, int *i)
{
	t_token	*new_token;

	new_token = prs_get_quoted_str(str, quote, content);
	if (!new_token)
	{
		new_token = token_create("", 0, STR, content);
		(*i)++; 
	}
	else
		*i += ft_strlen(new_token->value) + 1;
	return (new_token);
}

t_token	*prs_quotes_to_tokens(char *input_str, t_shell *content)
{
	int		i;
	t_token	*token;
	t_token	*new_token;

	i = 0;
	token = NULL;
	while (input_str[i])
	{
		if (input_str[i] == '\'' || input_str[i] == '\"')
			new_token = handle_quoted_token(&input_str[i],
					input_str[i], content, &i);
		else
		{
			new_token = token_create(&input_str[i], ft_rogue_len(&input_str[i]),
					STR, content);
			i += ft_strlen(new_token->value);
		}
		if (!new_token || !token_add_back(&token, new_token))
			return (NULL);
		i++;
	}
	return (token);
}*/