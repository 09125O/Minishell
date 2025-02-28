/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:10:21 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/26 21:36:11 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_lexer.h"
#include "minishell.h"
#include "shell_ctx.h"

static int	get_quoted_length(char *input, int i, char quote_type)
{
	int	len;

	len = 0;
	i++;
	while (input[i + len] && input[i + len] != quote_type)
		len++;
	return (len);
}

static char	*append_char(char *str, char c)
{
	char	*new;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new = malloc(len + 2);
	if (!new)
	{
		free(str);
		return (NULL);
	}
	ft_strlcpy(new, str, len + 1);
	new[len] = c;
	new[len + 1] = '\0';
	free(str);
	return (new);
}

static char	*expand_quoted_content(char *content, t_env *env, char quote_type, t_shell_ctx *shell_ctx)
{
	char	*result;
	char	*expanded;
	char	*temp;
	int		i;
	int		start;

	if (quote_type == '\'')
		return (ft_strdup(content));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (content[i])
	{
		if (content[i] == '$' && !is_escaped(content, i))
		{
			start = i;
			while (content[i] && is_env_char(content[i]))
				i++;
			temp = ft_substr(content, start, i - start);
			expanded = env_expand_var(env, temp, shell_ctx);
			free(temp);
			temp = result;
			result = ft_strjoin(result, expanded);
			free(temp);
			free(expanded);
		}
		else
			result = append_char(result, content[i++]);
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*extract_quoted_word(char *input, int *i, char quote_type,
	t_lexer_error_info *error)
{
	int		len;
	char	*word;
	int		j;

	len = get_quoted_length(input, *i, quote_type);
	if (!input[*i + len + 1])
	{
		set_error(error, LEXER_ERROR_UNCLOSED_QUOTE,
			"Quote non fermée", *i);
		return (NULL);
	}
	word = malloc(len + 1);
	if (!word)
	{
		set_error(error, LEXER_ERROR_MEMORY,
			"Erreur d'allocation mémoire", *i);
		return (NULL);
	}
	(*i)++;
	j = 0;
	while (j < len)
		word[j++] = input[(*i)++];
	word[j] = '\0';
	(*i)++;
	return (word);
}

int	process_quotes(t_token **head, char *input, int *i,
	t_lexer_ctx *ctx)
{
	char	quote_type;
	char	*content;
	char	*expanded;
	t_token	*token;

	quote_type = input[*i];
	content = extract_quoted_word(input, i, quote_type, &ctx->error);
	if (!content)
		return (-1);
	expanded = expand_quoted_content(content, ctx->env, quote_type, ctx->shell_ctx);
	free(content);
	if (!expanded)
	{
		set_error(&ctx->error, LEXER_ERROR_MEMORY,
			"Erreur d'allocation mémoire", *i);
		return (-1);
	}
	token = create_token(TOKEN_WORD, expanded);
	if (!token)
	{
		free(expanded);
		set_error(&ctx->error, LEXER_ERROR_MEMORY,
			"Erreur d'allocation mémoire", *i);
		return (-1);
	}
	add_token(head, token);
	return (1);
}
