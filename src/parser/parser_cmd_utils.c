/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:58:21 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/25 18:14:19 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_parser.h"
#include "libft.h"
#include <stdlib.h>

static int	validate_command_args(t_token *token, int count)
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

static int	fill_command_args(char **args, t_token *token, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		args[i] = ft_strdup(token->value);
		if (!args[i])
		{
			while (--i >= 0)
				free(args[i]);
			free(args);
			return (0);
		}
		token = token->next;
		i++;
	}
	args[i] = NULL;
	return (1);
}

char	**process_command_args(t_token *token, int count)
{
	char	**args;

	if (!validate_command_args(token, count))
		return (NULL);

	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);

	if (!fill_command_args(args, token, count))
		return (NULL);

	return (args);
}
