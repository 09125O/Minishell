/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:58:21 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/25 18:14:03 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_parser.h"
#include "../libft/inc/libft.h"
#include <stdlib.h>

int	fill_args_array(char **args, t_token *token, int count)
{
	int	i;

	i = 0;
	while (token && i < count)
	{
		if (token->type == TOKEN_WORD)
		{
			args[i] = ft_strdup(token->value);
			if (!args[i])
				return (0);
			i++;
		}
		token = token->next;
	}
	args[i] = NULL;
	return (1);
}

int	validate_args(t_token *token, int count)
{
	int	i;

	i = 0;
	while (token && i < count)
	{
		if (token->type != TOKEN_WORD)
			return (0);
		token = token->next;
		i++;
	}
	return (1);
}

int	check_args_limit(int count)
{
	return (count <= 4);  // 4 = commande + 3 arguments
}

int	prepare_args(t_token *token, int *count)
{
	*count = 0;
	while (token && token->type != TOKEN_PIPE
		&& !is_redirection_token(token->type))
	{
		if (token->type == TOKEN_WORD)
			(*count)++;
		token = token->next;
	}
	if (*count == 0)
		return (0);
	if (*count > 4)  // 4 = commande + 3 arguments
		return (0);
	return (1);
}

char	**process_args(t_token *token, int count)
{
	char	**args;

	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	if (!fill_args_array(args, token, count))
		return (NULL);
	args[count] = NULL;
	return (args);
}
