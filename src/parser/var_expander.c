/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:50:19 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/18 00:37:28 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"

static int	get_var_name_len(const char *str)
{
   int	i;

   i = 0;
   if (str[i] == '?')
   	return (1);
   while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
   	i++;
   return (i);
}

char	*get_var_value(char *var_name, char **env)
{
   int		len;
   char	*value;

   if (!var_name || !env)
   	return (NULL);
   if (var_name[0] == '?')
   	return (ft_itoa(g_signal_status));
   len = ft_strlen(var_name);
   while (*env)
   {
   	if (!ft_strncmp(*env, var_name, len) && (*env)[len] == '=')
   	{
   		value = ft_strdup(*env + len + 1);
   		return (value);
   	}
   	env++;
   }
   return (ft_strdup(""));
}

static char	*join_parts(char *s1, char *s2)
{
   char	*result;

   result = ft_strjoin(s1, s2);
   free(s1);
   free(s2);
   return (result);
}

static char	*handle_dollar(char *str, int *i, char **env)
{
   char	*var_name;
   char	*value;
   int		len;

   (*i)++;
   len = get_var_name_len(str + *i);
   if (len == 0)
   	return (ft_strdup("$"));
   var_name = ft_substr(str, *i, len);
   if (!var_name)
   	return (NULL);
   value = get_var_value(var_name, env);
   free(var_name);
   *i += len;
   return (value);
}

char	*expand_variables(char *str, char **env)
{
   char	*result;
   char	*temp;
   int		i;

   if (!str)
   	return (NULL);
   result = ft_strdup("");
   i = 0;
   while (str[i])
   {
   	if (str[i] == '$')
   		temp = handle_dollar(str, &i, env);
   	else
   	{
   		temp = ft_substr(str, i, 1);
   		i++;
   	}
   	if (!temp)
   	{
   		free(result);
   		return (NULL);
   	}
   	result = join_parts(result, temp);
   }
   return (result);
}
