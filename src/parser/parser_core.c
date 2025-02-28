/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:55:21 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/26 00:50:21 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_parser.h"
#include <stdlib.h>
#include <stdio.h>

t_command	*parse_pipeline(t_parser_ctx *ctx);

void	init_parser_context(t_parser_ctx *ctx, t_token *tokens)
{
	ctx->current = tokens;
	ctx->error = E_NONE;
	ctx->error_msg = NULL;
}

t_token	*next_token(t_parser_ctx *ctx)
{
	if (ctx->current)
		ctx->current = ctx->current->next;
	return (ctx->current);
}

t_token	*peek_token(t_parser_ctx *ctx)
{
	if (!ctx->current)
		return (NULL);
	return (ctx->current->next);
}

void	set_parser_error(t_parser_ctx *ctx, t_error error, const char *msg)
{
	if (ctx && msg)
	{
		ctx->error = error;
		ctx->error_msg = (char *)msg;
		printf("Erreur de parsing : %s\n", msg);
	}
}

t_command	**parse_tokens(t_token *tokens)
{
	t_parser_ctx	ctx;
	t_command		*cmd;
	t_command		**commands;
	int				cmd_count;
	int				i;

	if (!tokens)
		return (NULL);
	init_parser_context(&ctx, tokens);
	cmd = parse_pipeline(&ctx);
	if (ctx.error != E_NONE || !cmd)
		return (NULL);

	cmd_count = count_command_list(cmd);

	commands = malloc(sizeof(t_command *) * (cmd_count + 1));
	if (!commands)
	{
		free_command(cmd);
		return (NULL);
	}

	i = 0;
	while (cmd)
	{
		commands[i] = cmd;
		cmd = cmd->next;
		i++;
	}
	commands[i] = NULL;

	return (commands);
}
