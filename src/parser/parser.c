/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:49:19 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/18 00:33:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include "libft.h" 

static int	handle_redirect(t_command *cmd, t_token **token)
{
	t_redirect	*redir;
	t_token_type	type;

	type = (*token)->type;
	*token = (*token)->next;
	if (!*token || (*token)->type != TOKEN_WORD)
		return (1);
	redir = create_redirect((*token)->value, type);
	if (!redir)
		return (1);
	add_redirect_to_command(cmd, redir);
	*token = (*token)->next;
	return (0);
}

static int	parse_command(t_command *cmd, t_token **token)
{
	while (*token && (*token)->type != TOKEN_PIPE)
	{
		if (is_redirection((*token)->type))
		{
			if (handle_redirect(cmd, token))
				return (1);
		}
		else if ((*token)->type == TOKEN_WORD)
		{
			add_arg_to_command(cmd, ft_strdup((*token)->value));
			*token = (*token)->next;
		}
	}
	return (0);
}

static t_ast	*create_pipeline_node(t_command *cmd, t_token **token)
{
	t_ast	*node;

	node = create_ast_node(cmd);
	if (!node)
		return (NULL);
	if (*token && (*token)->type == TOKEN_PIPE)
	{
		*token = (*token)->next;
		return (node);
	}
	return (node);
}

static t_ast	*parse_pipeline(t_token *tokens)
{
	t_command	*cmd;
	t_ast		*node;
	t_token		*current;

	current = tokens;
	cmd = create_command();
	if (!cmd)
		return (NULL);
	if (parse_command(cmd, &current))
	{
		free_command(cmd);
		return (NULL);
	}
	node = create_pipeline_node(cmd, &current);
	if (!node)
		return (NULL);
	if (current)
		node->right = parse_pipeline(current);
	return (node);
}

t_ast	*parser(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	return (parse_pipeline(tokens));
}
