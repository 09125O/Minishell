/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:49:46 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/18 00:34:55 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include "libft.h"

t_ast	*create_ast_node(t_command *cmd)
{
   t_ast	*node;

   node = malloc(sizeof(t_ast));
   if (!node)
   	return (NULL);
   node->cmd = cmd;
   node->left = NULL;
   node->right = NULL;
   return (node);
}

static int	is_pipeline_token(t_token *token)
{
   return (token && token->type == TOKEN_PIPE);
}

static t_command	*extract_command(t_token **tokens)
{
   t_command	*cmd;
   t_redirect	*redir;

   cmd = create_command();
   if (!cmd)
   	return (NULL);
   while (*tokens && !is_pipeline_token(*tokens))
   {
   	if (is_redirection((*tokens)->type))
   	{
   		redir = create_redirect((*tokens)->next->value, (*tokens)->type);
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

static t_ast	*build_ast_recursive(t_token **tokens)
{
   t_command	*cmd;
   t_ast		*node;

   if (!*tokens)
   	return (NULL);
   cmd = extract_command(tokens);
   if (!cmd)
   	return (NULL);
   node = create_ast_node(cmd);
   if (!node)
   	return (free_command(cmd), NULL);
   if (*tokens && is_pipeline_token(*tokens))
   {
   	*tokens = (*tokens)->next;
   	node->right = build_ast_recursive(tokens);
   	if (!node->right)
   		return (free_ast(node), NULL);
   }
   return (node);
}

t_ast	*build_pipeline(t_token *tokens)
{
   t_token	*current;
   t_ast	*root;

   if (!tokens)
   	return (NULL);
   current = tokens;
   root = build_ast_recursive(&current);
   return (root);
}
