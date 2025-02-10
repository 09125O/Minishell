/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:49:46 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/10 22:01:50 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast *create_ast_node(t_command *cmd)
{
    t_ast *node = malloc(sizeof(t_ast));
    if (!node)
		return (NULL);
    node->cmd = cmd;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

static t_ast *build_ast_recursive(t_token **tokens)
{
    t_command *cmd = extract_command(tokens);
    if (!cmd)
		return (NULL);
    t_ast *node = create_ast_node(cmd);
    if (!node)
		return (free_command(cmd), NULL);
    if (*tokens && is_pipeline_token(*tokens))
	{
        *tokens = (*tokens)->next;
        node->right = build_ast_recursive(tokens);
    }
    return (node);
}

static t_command *extract_command(t_token **tokens)
{
    t_command *cmd = create_command();
    if (!cmd)
		return (NULL);
    while (*tokens && !is_pipeline_token(*tokens))
	{
        if (is_redirection((*tokens)->type))
		{
            t_redirect *redir = create_redirect((*tokens)->next->value, (*tokens)->type);
            if (!redir)
				return (free_command(cmd), NULL);
            add_redirect_to_command(cmd, redir);
            *tokens = (*tokens)->next->next;
        }
		else
		{
            add_arg_to_command(cmd, ft_strdup((*tokens)->value));
            *tokens = (*tokens)->next;
        }
    }
    return (cmd);
}

static int is_pipeline_token(t_token *token)
{
    return (token && token->type == TOKEN_PIPE);
}

int validate_ast(t_ast *ast)
{
    if (!ast)
		return (0);
    if (!ast->cmd || !ast->cmd->args || !ast->cmd->args[0])
		return (0);
    if (ast->right && !validate_ast(ast->right))
		return (0);
    return (1);
}
