/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:48:09 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/18 00:27:43 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

static t_token_type	get_pipe_type(void)
{
   return (TOKEN_PIPE);
}

static t_token_type	get_redirect_in_type(char *input, int *i)
{
   if (input[*i + 1] == '<')
   {
   	(*i)++;
   	return (TOKEN_HEREDOC);
   }
   return (TOKEN_REDIRECT_IN);
}

static t_token_type	get_redirect_out_type(char *input, int *i)
{
   if (input[*i + 1] == '>')
   {
   	(*i)++;
   	return (TOKEN_APPEND);
   }
   return (TOKEN_REDIRECT_OUT);
}

int	is_redirection(char c)
{
   return (c == '<' || c == '>');
}

t_token_type	get_token_type(char *input, int *i)
{
   if (input[*i] == '|')
   	return (get_pipe_type());
   if (input[*i] == '<')
   	return (get_redirect_in_type(input, i));
   if (input[*i] == '>')
   	return (get_redirect_out_type(input, i));
   return (TOKEN_EOF);
}
