/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:10:21 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/26 22:54:39 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_lexer.h"
#include "minishell.h"
#include "shell_ctx.h"
#include <stdlib.h>
#include <string.h>

t_token	*create_env_var_token(char *input, int *i, t_env *env)
{
	char		*var_name;
	char		*value;
	t_token		*token;
	int			len;
	int			start;

	// Ignorer le caractère $
	(*i)++;

	// Cas spécial pour $?
	if (input[*i] == '?')
	{
		(*i)++;
		ft_putstr_fd("DEBUG: Variable spéciale $? détectée dans le lexer\n", 2);
		value = get_special_var("?", g_global.ctx);
		ft_putstr_fd("DEBUG: Valeur de $? dans le lexer: ", 2);
		if (value)
			ft_putstr_fd(value, 2);
		else
			ft_putstr_fd("NULL", 2);
		ft_putstr_fd("\n", 2);
		token = create_token(TOKEN_WORD, value ? value : ft_strdup("0"));
		return (token);
	}

	// Si fin de chaîne ou caractère non valide pour un nom de variable
	if (!input[*i] || !is_env_first_char(input[*i]))
		return (create_token(TOKEN_WORD, ft_strdup("$")));

	// Trouver la longueur du nom de variable
	start = *i;
	while (input[*i] && is_env_char(input[*i]))
		(*i)++;

	len = *i - start;
	if (len <= 0)
		return (create_token(TOKEN_WORD, ft_strdup("$")));

	// Extraire le nom de variable
	var_name = ft_substr(input, start, len);
	if (!var_name)
		return (NULL);

	// Obtenir la valeur de la variable
	if (is_special_var(var_name))
		value = get_special_var(var_name, g_global.ctx);
	else
		value = env_get(env, var_name);

	free(var_name);

	// Créer le token avec la valeur ou une chaîne vide
	if (value)
		token = create_token(TOKEN_WORD, ft_strdup(value));
	else
		token = create_token(TOKEN_WORD, ft_strdup(""));

	if (!token)
		return (NULL);

	return (token);
}
