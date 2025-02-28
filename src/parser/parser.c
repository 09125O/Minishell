/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:58:21 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/25 00:09:55 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_parser.h"
#include <stdlib.h>

static void	init_parser_context(t_parser_context *ctx, t_token *tokens)
{
	ctx->current = tokens;
	ctx->error = PARSER_SUCCESS;
	ctx->error_msg = NULL;
	ctx->error_pos = 0;
}

static t_token	*next_token(t_parser_context *ctx)
{
	if (ctx->current)
		ctx->current = ctx->current->next;
	return (ctx->current);
}

static t_token	*peek_token(t_parser_context *ctx)
{
	if (!ctx->current)
		return (NULL);
	return (ctx->current->next);
}

static int	validate_tokens(t_parser_context *ctx)
{
	if (!ctx->current)
		return (1);
	if (ctx->current->type == TOKEN_PIPE)
	{
		set_parser_error(ctx, PARSER_ERROR_SYNTAX,
			"Pipe inattendu en début de commande");
		return (0);
	}
	return (1);
}

t_command	*parse_tokens(t_token *tokens, t_parser_error *error)
{
	t_parser_context	ctx;
	t_command		*cmd;

	init_parser_context(&ctx, tokens);
	if (!tokens)
	{
		*error = PARSER_SUCCESS;
		return (NULL);
	}
	if (!validate_tokens(&ctx))
	{
		*error = ctx.error;
		return (NULL);
	}
	cmd = parse_pipeline(&ctx);
	*error = ctx.error;
	return (cmd);
}

static void	free_simple_command(t_command *cmd)
{
	t_redirection	*redir;
	t_redirection	*next_redir;
	int				i;

	i = 0;
	while (i < cmd->cmd.simple.argc)
		free(cmd->cmd.simple.args[i++]);
	free(cmd->cmd.simple.args);
	redir = cmd->cmd.simple.redirections;
	while (redir)
	{
		next_redir = redir->next;
		free(redir->file);
		free(redir);
		redir = next_redir;
	}
}

static void	free_pipeline(t_command *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->cmd.pipeline.cmd_count)
		free_command(cmd->cmd.pipeline.commands[i++]);
	free(cmd->cmd.pipeline.commands);
}

void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == CMD_SIMPLE)
		free_simple_command(cmd);
	else if (cmd->type == CMD_PIPE)
		free_pipeline(cmd);
	free(cmd);
}
