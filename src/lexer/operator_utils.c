/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:10:21 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/25 18:06:20 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_lexer.h"
#include "minishell.h"
#include "libft.h"

static t_token_type	get_operator_type(char *input, int pos)
{
	if (input[pos] == '|')
		return (TOKEN_PIPE);
	if (input[pos] == '<')
	{
		if (input[pos + 1] == '<')
			return (TOKEN_REDIR_HEREDOC);
		return (TOKEN_REDIR_IN);
	}
	if (input[pos] == '>')
	{
		if (input[pos + 1] == '>')
			return (TOKEN_REDIR_APPEND);
		return (TOKEN_REDIR_OUT);
	}
	return (TOKEN_EOF);
}

int	process_operator(t_token **head, t_lexer_ctx *ctx)
{
	t_token	*token;
	char	*value;
	int		len;

	len = 1;
	if ((ctx->input[ctx->position] == '<' || ctx->input[ctx->position] == '>')
		&& ctx->input[ctx->position + 1] == ctx->input[ctx->position])
		len = 2;
	value = ft_substr(ctx->input, ctx->position, len);
	if (!value)
		return (-1);
	token = create_token(get_operator_type(ctx->input, ctx->position), value);
	if (!token)
	{
		free(value);
		return (-1);
	}
	add_token(head, token);
	ctx->position += len;
	return (1);
}
