/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:58:21 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/26 00:21:59 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_parser.h"
#include <stdlib.h>
#include <stdio.h>

void	add_redirection(t_redirection **head, t_redirection *new)
{
	t_redirection	*current;

	if (!*head)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new;
}

int	is_redirection_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC);
}

int	count_args(t_token *token)
{
	int		count;
	t_token	*current;

	count = 0;
	current = token;
	while (current && current->type != TOKEN_PIPE)
	{
		if (current->type == TOKEN_WORD)
			count++;
		current = current->next;
	}
	return (count);
}

char	**create_args_array(t_token *token, int count)
{
	char	**args;

	args = malloc(sizeof(char *) * (count + 1));  // +1 pour le NULL final
	if (!args)
		return (NULL);
	if (!fill_args_array(args, token, count))
		return (NULL);
	return (args);
}

t_redir_type	get_redirection_type(t_token_type token_type)
{
	if (token_type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	else if (token_type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	else if (token_type == TOKEN_REDIR_APPEND)
		return (REDIR_APPEND);
	else if (token_type == TOKEN_REDIR_HEREDOC)
		return (REDIR_HEREDOC);
	return (REDIR_IN); // Valeur par défaut en cas d'erreur
}
