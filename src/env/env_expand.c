/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:00:00 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/27 00:01:22 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

/**
 * Expands environment variables in a string
 *
 * @param env The environment list
 * @param str The string containing variables to expand
 * @param ctx The shell context
 * @return A new string with expanded variables
 */
char	*env_expand_var(t_env *env, const char *str, t_shell_ctx *ctx)
{
	char		*result;
	static int	expansion_count = 0;

	ft_putstr_fd("DEBUG [env_expand_var]: Entrée avec str='", 2);
	if (str)
		ft_putstr_fd((char *)str, 2);
	else
		ft_putstr_fd("NULL", 2);
	ft_putstr_fd("'\n", 2);

	// Réinitialiser le compteur si c'est un nouvel appel (pas de récursion)
	if (expansion_count == 0)
		expansion_count = 0;

	// Vérifier le nombre d'expansions pour éviter les boucles infinies
	expansion_count++;
	if (expansion_count > 10)
	{
		ft_putstr_fd("DEBUG [env_expand_var]: ATTENTION - Trop d'expansions imbriquées\n", 2);
		expansion_count = 0; // Réinitialiser le compteur avant de sortir
		return (ft_strdup(str ? str : ""));
	}

	if (!str)
	{
		ft_putstr_fd("DEBUG [env_expand_var]: str est NULL, retour chaîne vide\n", 2);
		expansion_count = 0; // Réinitialiser le compteur avant de sortir
		return (ft_strdup(""));
	}

	result = expand_next_var(env, str, ctx);

	ft_putstr_fd("DEBUG [env_expand_var]: Résultat='", 2);
	if (result)
		ft_putstr_fd(result, 2);
	else
		ft_putstr_fd("NULL", 2);
	ft_putstr_fd("'\n", 2);

	expansion_count = 0; // Réinitialiser le compteur avant de sortir
	return (result);
}

/**
 * Expands environment variables in a quoted string
 *
 * @param env The environment list
 * @param str The string containing variables to expand
 * @param quote The quote type (' or ")
 * @param ctx The shell context
 * @return A new string with expanded variables (only if quote is ")
 */
char	*env_expand_quoted(t_env *env, const char *str, char quote, t_shell_ctx *ctx)
{
	char		*result;
	static int	expansion_count = 0;

	ft_putstr_fd("DEBUG [env_expand_quoted]: Entrée avec str='", 2);
	if (str)
		ft_putstr_fd((char *)str, 2);
	else
		ft_putstr_fd("NULL", 2);
	ft_putstr_fd("', quote='", 2);
	ft_putchar_fd(quote, 2);
	ft_putstr_fd("'\n", 2);

	// Réinitialiser le compteur si c'est un nouvel appel (pas de récursion)
	if (expansion_count == 0)
		expansion_count = 0;

	// Vérifier le nombre d'expansions pour éviter les boucles infinies
	expansion_count++;
	if (expansion_count > 10)
	{
		ft_putstr_fd("DEBUG [env_expand_quoted]: ATTENTION - Trop d'expansions imbriquées\n", 2);
		expansion_count = 0; // Réinitialiser le compteur avant de sortir
		return (ft_strdup(str ? str : ""));
	}

	// Single quotes prevent expansion
	if (quote == '\'')
	{
		ft_putstr_fd("DEBUG [env_expand_quoted]: Guillemet simple, pas d'expansion\n", 2);
		result = ft_strdup(str);
	}
	// Double quotes allow expansion
	else if (quote == '\"')
	{
		ft_putstr_fd("DEBUG [env_expand_quoted]: Guillemet double, expansion\n", 2);
		result = env_expand_var(env, str, ctx);
	}
	// Default case (no quotes)
	else
	{
		ft_putstr_fd("DEBUG [env_expand_quoted]: Pas de guillemet\n", 2);
		result = ft_strdup(str);
	}

	ft_putstr_fd("DEBUG [env_expand_quoted]: Résultat='", 2);
	if (result)
		ft_putstr_fd(result, 2);
	else
		ft_putstr_fd("NULL", 2);
	ft_putstr_fd("'\n", 2);

	expansion_count = 0; // Réinitialiser le compteur avant de sortir
	return (result);
}
