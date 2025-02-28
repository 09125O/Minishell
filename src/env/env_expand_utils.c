#include "minishell.h"

char	*expand_simple_var(t_env *env, const char *var_name, t_shell_ctx *ctx)
{
	char	*value;
	static int	recursion_depth = 0;

	ft_putstr_fd("DEBUG: expand_simple_var appelé avec var_name=", 2);
	if (var_name)
		ft_putstr_fd(var_name, 2);
	else
		ft_putstr_fd("NULL", 2);
	ft_putstr_fd("\n", 2);

	// Réinitialiser le compteur si c'est un nouvel appel (pas de récursion)
	if (recursion_depth == 0)
		recursion_depth = 0;

	// Vérifier la profondeur de récursion pour éviter les boucles infinies
	recursion_depth++;
	if (recursion_depth > 5)
	{
		ft_putstr_fd("DEBUG: expand_simple_var - ATTENTION: Profondeur de récursion maximale atteinte\n", 2);
		recursion_depth = 0; // Réinitialiser avant de sortir
		return (ft_strdup(""));
	}

	if (!var_name || !*var_name)
	{
		recursion_depth = 0; // Réinitialiser avant de sortir
		return (ft_strdup("$"));
	}

	ft_putstr_fd("DEBUG: Vérification si variable spéciale\n", 2);
	if (is_special_var(var_name))
	{
		ft_putstr_fd("DEBUG: Variable spéciale détectée\n", 2);
		value = get_special_var(var_name, ctx);
		ft_putstr_fd("DEBUG: Valeur de la variable spéciale: ", 2);
		if (value)
			ft_putstr_fd(value, 2);
		else
			ft_putstr_fd("NULL", 2);
		ft_putstr_fd("\n", 2);
		recursion_depth = 0; // Réinitialiser avant de sortir
		return (value ? value : ft_strdup(""));
	}

	ft_putstr_fd("DEBUG: Recherche dans l'environnement\n", 2);
	value = env_get(env, var_name);
	ft_putstr_fd("DEBUG: Valeur trouvée: ", 2);
	if (value)
		ft_putstr_fd(value, 2);
	else
		ft_putstr_fd("NULL", 2);
	ft_putstr_fd("\n", 2);

	recursion_depth = 0; // Réinitialiser avant de sortir
	if (!value)
		return (ft_strdup(""));

	// Retourner une copie de la valeur sans expansion récursive
	// pour éviter les boucles infinies
	return (ft_strdup(value));
}

int	get_var_length(const char *str)
{
	int	i;
	int	in_braces;

	i = 1;
	in_braces = (str[i] == '{');
	if (in_braces)
		i++;
	while (str[i])
	{
		if (in_braces && str[i] == '}')
		{
			i++;
			break ;
		}
		else if (!in_braces && !(ft_isalnum(str[i]) || str[i] == '_'
				|| str[i] == '?'))
			break ;
		i++;
	}
	return (i);
}

char	*get_var_name(const char *str)
{
	int		len;
	int		start;
	char	*var_name;
	int		has_braces;

	ft_putstr_fd("DEBUG [get_var_name]: Entrée avec str='", 2);
	if (str)
		ft_putstr_fd((char *)str, 2);
	else
		ft_putstr_fd("NULL", 2);
	ft_putstr_fd("'\n", 2);

	// Cas spécial pour $?
	if (str[1] == '?')
	{
		ft_putstr_fd("DEBUG [get_var_name]: Cas spécial $?\n", 2);
		return (ft_strdup("?"));
	}

	has_braces = (str[1] == '{');
	start = 1 + (has_braces ? 1 : 0);
	len = get_var_length(str) - start - (has_braces ? 1 : 0);

	ft_putstr_fd("DEBUG [get_var_name]: has_braces=", 2);
	ft_putnbr_fd(has_braces, 2);
	ft_putstr_fd(", start=", 2);
	ft_putnbr_fd(start, 2);
	ft_putstr_fd(", len=", 2);
	ft_putnbr_fd(len, 2);
	ft_putstr_fd("\n", 2);

	if (len <= 0)
	{
		ft_putstr_fd("DEBUG [get_var_name]: len <= 0, retour NULL\n", 2);
		return (NULL);
	}

	var_name = ft_substr(str, start, len);

	ft_putstr_fd("DEBUG [get_var_name]: var_name='", 2);
	if (var_name)
		ft_putstr_fd(var_name, 2);
	else
		ft_putstr_fd("NULL", 2);
	ft_putstr_fd("'\n", 2);

	return (var_name);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

char	*expand_next_var(t_env *env, const char *str, t_shell_ctx *ctx)
{
	int		i;
	char	*result;
	char	*temp;
	char	*var_value;
	char	*var_name;
	int		var_len;
	int		max_expansions;

	ft_putstr_fd("DEBUG [expand_next_var]: Entrée avec str='", 2);
	if (str)
		ft_putstr_fd((char *)str, 2);
	else
		ft_putstr_fd("NULL", 2);
	ft_putstr_fd("'\n", 2);

	if (!str || !*str)
	{
		ft_putstr_fd("DEBUG [expand_next_var]: str vide ou NULL, retour chaîne vide\n", 2);
		return (ft_strdup(""));
	}

	result = ft_strdup("");
	if (!result)
	{
		ft_putstr_fd("DEBUG [expand_next_var]: Échec d'allocation mémoire\n", 2);
		return (NULL);
	}

	// Limiter le nombre d'expansions pour éviter les boucles infinies
	max_expansions = 10; // Réduit de 50 à 10 pour éviter les boucles trop longues

	i = 0;
	while (str[i] && max_expansions > 0)
	{
		// Si on trouve un $, on extrait et traite la variable
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			ft_putstr_fd("DEBUG [expand_next_var]: $ trouvé à la position ", 2);
			ft_putnbr_fd(i, 2);
			ft_putstr_fd("\n", 2);

			// Extraire le nom de la variable
			var_name = get_var_name(str + i);
			ft_putstr_fd("DEBUG [expand_next_var]: Nom de variable extrait: ", 2);
			if (var_name)
				ft_putstr_fd(var_name, 2);
			else
				ft_putstr_fd("NULL", 2);
			ft_putstr_fd("\n", 2);

			if (!var_name)
			{
				// Si pas de nom valide, ajouter juste le $ au résultat
				ft_putstr_fd("DEBUG [expand_next_var]: Pas de nom valide, ajout de $ au résultat\n", 2);
				temp = result;
				result = ft_strjoin(result, "$");
				free(temp);
				i++;
				continue;
			}

			// Obtenir la valeur de la variable
			ft_putstr_fd("DEBUG [expand_next_var]: Expansion de la variable\n", 2);
			var_value = expand_simple_var(env, var_name, ctx);
			free(var_name);

			// Ajouter la valeur au résultat
			ft_putstr_fd("DEBUG [expand_next_var]: Ajout de la valeur au résultat\n", 2);
			temp = result;
			result = ft_strjoin(result, var_value);
			free(temp);
			free(var_value);

			// Avancer après la variable
			var_len = get_var_length(str + i);
			ft_putstr_fd("DEBUG [expand_next_var]: Longueur de la variable: ", 2);
			ft_putnbr_fd(var_len, 2);
			ft_putstr_fd("\n", 2);
			i += var_len;

			// Décrémenter le compteur d'expansions
			max_expansions--;
		}
		else
		{
			// Ajouter le caractère courant au résultat
			temp = result;
			result = ft_strjoin_char(result, str[i]);
			if (result == NULL)
			{
				ft_putstr_fd("DEBUG [expand_next_var]: Échec d'allocation mémoire pour ft_strjoin_char\n", 2);
				free(temp);
				return (ft_strdup(""));
			}
			free(temp); // Libérer l'ancienne chaîne
			i++;
		}
	}

	// Vérifier si on a atteint la limite d'expansions
	if (max_expansions <= 0)
	{
		ft_putstr_fd("DEBUG [expand_next_var]: ATTENTION - Limite d'expansions atteinte, possible boucle infinie\n", 2);
	}

	ft_putstr_fd("DEBUG [expand_next_var]: Résultat final='", 2);
	if (result)
		ft_putstr_fd(result, 2);
	else
		ft_putstr_fd("NULL", 2);
	ft_putstr_fd("'\n", 2);

	return (result);
}

// Fonction utilitaire pour joindre un caractère à une chaîne
char	*ft_strjoin_char(char *str, char c)
{
	char	*result;
	int		len;
	int		i;

	if (!str)
		return (NULL);

	len = ft_strlen(str);
	result = (char *)malloc(len + 2);
	if (!result)
		return (NULL);

	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = c;
	result[i + 1] = '\0';

	// Ne pas libérer str ici, car c'est fait dans expand_next_var
	return (result);
}
