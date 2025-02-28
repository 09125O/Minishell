/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:10:21 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/26 20:46:47 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_lexer.h"
#include "minishell.h"

static void	skip_whitespace(char *input, int *i)
{
	while (input[*i] && is_whitespace(input[*i]))
		(*i)++;
}

static int	process_token(t_token **head, t_lexer_ctx *ctx)
{
	skip_whitespace(ctx->input, &ctx->position);
	if (!ctx->input[ctx->position])
		return (1);
	if (ctx->input[ctx->position] == '#')
	{
		while (ctx->input[ctx->position]
			&& ctx->input[ctx->position] != '\n')
			ctx->position++;
		return (1);
	}
	if (is_operator(ctx->input[ctx->position]))
	{
		if (!validate_operator(ctx->input, ctx->position, &ctx->error))
			return (-1);
		return (process_operator(head, ctx));
	}
	else if (is_quote(ctx->input[ctx->position]))
		return (process_quotes(head, ctx->input, &ctx->position, ctx));
	else if (ctx->input[ctx->position] == '$'
		&& !is_escaped(ctx->input, ctx->position))
	{
		t_token *token = create_env_var_token(ctx->input,
			&ctx->position, ctx->env);
		if (!token)
			return (-1);
		add_token(head, token);
		return (1);
	}
	return (process_word(head, ctx->input, &ctx->position));
}

t_token	*lexer(char *input, struct s_env *env)
{
	t_token		*head;
	t_lexer_ctx	ctx;

	head = NULL;
	if (!input)
		return (NULL);
	ctx.input = input;
	ctx.position = 0;
	ctx.env = env;
	ctx.shell_ctx = g_global.ctx;
	ctx.error.code = LEXER_SUCCESS;
	ctx.error.message = NULL;
	ctx.error.position = 0;
	while (input[ctx.position])
	{
		int result = process_token(&head, &ctx);
		if (result < 0)
		{
			free_token_list(head);
			return (NULL);
		}
		if (result == 0)
			ctx.position++;
	}
	return (head);
}
