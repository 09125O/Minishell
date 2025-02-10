/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:50:19 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/10 22:27:19 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int get_var_name_len(const char *str)
{
    int i = 0;
    if (str[i] == '?')
		return (1);
    while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
        i++;
    return (i);
}

char *get_var_value(char *var_name, char **env)
{
    if (!var_name || !env)
		return (NULL);
    if (var_name[0] == '?')
		return (ft_itoa(g_signal_status));
    int len = ft_strlen(var_name);
    while (*env)
	{
        if (!ft_strncmp(*env, var_name, len) && (*env)[len] == '=')
            return (ft_strdup(*env + len + 1));
        env++;
    }
    return (ft_strdup(""));
}

static char *join_parts(char *s1, char *s2)
{
    char *result = ft_strjoin(s1, s2);
    free(s1);
    free(s2);
    return (result);
}

static char *handle_dollar(char *str, int *i, char **env)
{
    (*i)++;
    int len = get_var_name_len(str + *i);
    if (len == 0)
		return (ft_strdup("$"));
    char *var_name = ft_substr(str, *i, len);
    if (!var_name)
		return (NULL);
    char *value = get_var_value(var_name, env);
    free(var_name);
    *i += len;
    return (value);
}

char *expand_variables(char *str, char **env)
{
  if (!str)
    return (NULL);
  char *result = ft_strdup("");
  int i = 0;
  while (str[i])
  {
      char *temp;
      if (str[i] == '$')
          temp = handle_dollar(str, &i, env);
      else
          temp = ft_substr(str, i++, 1);
      if (!temp)
      {
          free(result);
          return (NULL);
      }
      result = join_parts(result, temp);
  }
  return (result);
}
