/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:49:19 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/10 22:54:14 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast *parser(t_token *tokens, int *error_code)
{
    if (!tokens)
    {
        *error_code = PARSER_ERROR_INVALID_SYNTAX;
        return (NULL);
    }
    *error_code = PARSER_SUCCESS;
    return (parse_pipeline(tokens, error_code));
}

static t_ast *parse_pipeline(t_token *tokens, int *error_code)
{
    t_command *cmd = create_command();
    if (!cmd)
    {
        *error_code = PARSER_ERROR_INVALID_SYNTAX;
        return (NULL);
    }
    t_token *current = tokens;
    if (parse_command(cmd, &current, error_code))
    {
        free_command(cmd);
        return (NULL);
    }
    t_ast *node = create_pipeline_node(cmd, &current, error_code);
    if (!node)
    {
        return (NULL);
    }
    if (current) {
        node->right = parse_pipeline(current, error_code);
    }
    return (node);
}

static int parse_command(t_command *cmd, t_token **token, int *error_code)
{
    while (*token && (*token)->type != TOKEN_PIPE)
    {
        if (is_redirection((*token)->type))
        {
            if (handle_redirect(cmd, token, error_code))
            {
                return (1);
            }
        }
        else if ((*token)->type == TOKEN_WORD)
        {
            add_arg_to_command(cmd, ft_strdup((*token)->value));
            *token = (*token)->next;
        }
        else
        {
            *error_code = PARSER_ERROR_INVALID_SYNTAX;
            return (1);
        }
    }
    return (0);
}

static int handle_redirect(t_command *cmd, t_token **token, int *error_code)
{
    t_redirect *redir = create_redirect((*token)->next->value, (*token)->type);
    if (!redir)
    {
        *error_code = PARSER_ERROR_INVALID_SYNTAX;
        return (1);
    }
    add_redirect_to_command(cmd, redir);
    *token = (*token)->next->next;
    return (0);
}

static t_ast *create_pipeline_node(t_command *cmd, t_token **token)
{
    t_ast *node = create_ast_node(cmd);
    if (!node)
		return (NULL);
    if (*token && (*token)->type == TOKEN_PIPE)
	{
        *token = (*token)->next;
        node->right = parse_pipeline(*token);
    }
    return (node);
}
