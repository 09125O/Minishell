/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_srch_rm_modif.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:53:41 by obouhour          #+#    #+#             */
/*   Updated: 2024/12/17 22:03:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*search_env_variable(t_env *env, char *key)
{
	int i;
	int	key_len;

	i = 0;
	if (!key || !env)
		return (NULL);
	key_len = ft_strlen(key);
	while (env->vars[i])
	{
		if (!ft_strncmp(env->vars[i], key, key_len) 
				&& env->vars[i][key_len] == '=')
			return (env->vars[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

int	remove_env_var(t_env *env, char *key)
{
	int	i;
	int	j;
	int	key_len;

	if (!env || !key)
		return (-1);
	i = 0;
	key_len = ft_strlen(key);
	while (env->vars[i])
	{
		if (!ft_strncmp(env->vars[i], key, key_len)
				&& env->vars[i][key_len] == '=')
		{
			free(env->vars[i]);
			j = i;
			while (env->vars[j])
			{
				env->vars[j] = env->vars[j + 1];
				j++;
			}
			env->size_vars--;
			return (0);
		}
		i++;
	}
	return (-1);
}

int	update_env_variable(t_env *env, char *key, char *new_value)
{
	int		i;
	int		key_len;
	char	*new_entry;
	char	**new_vars;

	if (!env || !key || !new_value)
		return (-1);
	key_len = ft_strlen(key);
	new_entry = malloc(sizeof(char) * (key_len + ft_strlen(new_value) + 2)); // "key=value\0"
	if (!new_entry)
		return (-1);
	ft_strcpy(new_entry, (char *)key);
	ft_strcat(new_entry, "=");
	ft_strcat(new_entry, (char *)new_value);
	i = 0;
	while ( env->vars[i])//on cherche si la variable existe 
	{
		if (!ft_strncmp(env->vars[i], key, key_len) && env->vars[i][key_len] == '=')
		{
			free(env->vars[i]);
			env->vars[i] = new_entry;	// On remplace par la nouvelle
			return (0);
		}
		i++;
	}
	new_vars = malloc(sizeof(char *) * (env->size_vars + 2));// Si la variable n'existe pas(sinon on aurait quitter au return au dessus), ajouter une nouvelle entrée
	if (!new_vars)
	{
		free(new_entry);
		return (-1);
	}
	i = -1;
	while (i++ < env->size_vars)
		new_vars[i] = env->vars[i];
	new_vars[env->size_vars] = new_entry;	// On ajoute la nouvelle variable
	new_vars[env->size_vars + 1] = NULL;	// On termine notre nouveau tableau par NULL
	free(env->vars);		//
	env->vars = new_vars;	//Ici on remplace notre tableau par un nouveau
	env->size_vars++;		//
	return (0);
}




// int	update_env_var(t_env *env, char *key, char *new_value)
// {
// 	int		i;
// 	char	*new_entry;

// 	if (!env || !key || !new_value)
// 		return (-1);
// 	if (var_does_exist(env, key) == 0)
// 	{
// 		i = 0;
// 		new_entry = malloc(sizeof(char) * (ft_strlen(key) + ft_strlen(new_value) + 2));
// 		if (!new_entry)
// 			return (-1);
// 		new_entry = ft_strcpy(new_entry, key);
// 		new_entry = ft_strcat(new_entry, "=");
// 		new_entry = ft_strcat(new_entry, new_value);
// 		while(env->vars[i])
// 		{
// 			if (!ft_strncmp(env->vars[i], key, ft_strlen(key)) 
// 					&& env->vars[i][ft_strlen(key)] == '=')
// 			{
// 				free(env->vars[i]);
// 				env->vars[i] = new_entry;
// 				return (0);
// 			}
// 		}
// 	}
// 	else
// 	{
// 		if (var_does_not_exist(env, key, new_value) == -1)
// 			return (-1);
// 	}
// 	return (0);
// }
