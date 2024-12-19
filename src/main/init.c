/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:47:14 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/19 17:39:13 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_env_list(t_shell *shell, char **envp)
{
   t_env	*env_list;
   char	*key;
   char	*value;
   int		i;

   env_list = NULL;
   i = 0;
   while (envp[i])
   {
   	key = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
   	value = ft_strdup(ft_strchr(envp[i], '=') + 1);
   	if (key && value)
   		set_env_var(&env_list, key, value);
   	free(key);
   	free(value);
   	i++;
   }
   shell->env = env_list;
}

static char	**create_env_array(t_env *env)
{
   t_env	*current;
   char	**array;
   char	*tmp;
   int		i;
   int		size;

   size = 0;
   current = env;
   while (current && ++size)
   	current = current->next;
   array = ft_calloc(size + 1, sizeof(char *));
   if (!array)
   	return (NULL);
   current = env;
   i = 0;
   while (current)
   {
   	tmp = str_join_with_sep(current->key, current->value, "=");
   	if (!tmp)
   		return (free_str_array(array), NULL);
   	array[i++] = tmp;
   	current = current->next;
   }
   array[i] = NULL;
   return (array);
}

static void	init_shell_vars(t_shell *shell)
{
   char	*pwd;

   pwd = getcwd(NULL, 0);
   if (pwd)
   {
   	shell->pwd = pwd;
   	set_env_var(&shell->env, "PWD", pwd);
   }
   shell->oldpwd = NULL;
   shell->exit_status = 0;
   shell->in_heredoc = 0;
   shell->input = NULL;
}

void	init_shell(t_shell *shell, char **envp)
{
	ft_memset(shell, 0, sizeof(t_shell));
	init_env_list(shell, envp);
	init_shell_vars(shell);
	shell->env_array = create_env_array(shell->env);
	/*
	// Debug: afficher l'env_array
	printf("DEBUG: env_array content:\n");
	if (shell->env_array)
	{
		int i = 0;
		while (shell->env_array[i])
		{
			printf("%s\n", shell->env_array[i]);
			i++;
		}
	}
	*/
	setup_signal_handlers();
}
