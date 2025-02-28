/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:58:21 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/25 13:07:15 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_parser.h"
#include <stdlib.h>
#include <stdio.h>

static int	process_redirections(t_command *cmd, t_parser_ctx *ctx)
{
	t_redirection	*redir;
	t_token			*peek;
	t_token			*save;
	t_token			*next_pipe;

	if (!cmd || !ctx)
		return (0);

	save = ctx->current;
	peek = ctx->current;
	next_pipe = peek;
	while (next_pipe && next_pipe->type != TOKEN_PIPE)
		next_pipe = next_pipe->next;

	while (peek && peek != next_pipe)
	{
		if (is_redirection_token(peek->type))
		{
			ctx->current = peek;
			redir = parse_redirection(ctx);
			if (!redir)
			{
				ctx->current = save;
				return (0);
			}
			add_redirection(&cmd->redirections, redir);
			peek = ctx->current;
		}
		else
			peek = peek->next;
	}
	ctx->current = save;
	return (1);
}

t_command	*parse_simple_command(t_parser_ctx *ctx)
{
	t_command		*cmd;
	int				arg_count;
	t_token			*start;

	if (!ctx || !ctx->current)
		return (NULL);

	start = ctx->current;
	if (!prepare_args(start, &arg_count))
		return (NULL);

	cmd = create_command(CMD_SIMPLE);
	if (!cmd)
		return (NULL);

	cmd->args = create_args_array(start, arg_count);
	if (!cmd->args)
	{
		free_command(cmd);
		return (NULL);
	}

	while (arg_count > 0)
	{
		next_token(ctx);
		arg_count--;
	}

	if (!process_redirections(cmd, ctx))
	{
		free_command(cmd);
		return (NULL);
	}

	while (ctx->current && ctx->current->type != TOKEN_PIPE)
		next_token(ctx);

	return (cmd);
}

t_redirection	*parse_redirection(t_parser_ctx *ctx)
{
	t_redirection	*redir;
	t_token_type	type;

	if (!ctx || !ctx->current)
		return (NULL);

	type = ctx->current->type;
	next_token(ctx);
	if (!ctx->current || ctx->current->type != TOKEN_WORD)
	{
		set_parser_error(ctx, E_SYNTAX, "Missing redirection argument");
		return (NULL);
	}

	redir = create_redirection(get_redirection_type(type), ctx->current->value);
	next_token(ctx);
	return (redir);
}

t_command	*parse_pipeline(t_parser_ctx *ctx)
{
	t_command	*pipeline;
	t_command	*cmd;
	t_command	*last;
	t_token		*peek;
	int			has_pipe;

	if (!ctx || !ctx->current)
		return (NULL);

	peek = ctx->current;
	has_pipe = 0;
	while (peek)
	{
		if (peek->type == TOKEN_PIPE)
		{
			has_pipe = 1;
			break ;
		}
		peek = peek->next;
	}

	if (!has_pipe)
		return (parse_simple_command(ctx));

	pipeline = create_command(CMD_PIPELINE);
	if (!pipeline)
		return (NULL);

	cmd = parse_simple_command(ctx);
	if (!cmd)
	{
		free_command(pipeline);
		return (NULL);
	}
	pipeline->commands = cmd;
	last = cmd;

	while (ctx->current && ctx->current->type == TOKEN_PIPE)
	{
		next_token(ctx);
		if (!ctx->current)
		{
			free_command(pipeline);
			return (NULL);
		}
		cmd = parse_simple_command(ctx);
		if (!cmd)
		{
			free_command(pipeline);
			return (NULL);
		}
		last->next = cmd;
		last = cmd;
	}

	return (pipeline);
}
