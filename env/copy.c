/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhour <obouhour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:10:09 by obouhour          #+#    #+#             */
/*   Updated: 2024/12/17 12:47:27 by obouhour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	count_env_vars(char **shell_env)
{
	int	i;

	i = 0;
	while (shell_env[i])
		i++;
	return(i);
}

t_env	*init_env(char **shell_env)
{
	t_env	*env;
	int		i;

	env = malloc(sizeof(t_env));
	i = 0;
	if (!env)
		errors_env();
	env->size_vars = count_env_vars(shell_env);
	env->vars = malloc(sizeof(char *) * (env->size_vars + 1));
	if (!env->vars)
	{
		free(env);
		errors_env(); //a voir si mettre un return
	}
	while (i < env->size_vars)
	{
		env->vars[i] = ft_strdup(shell_env[i]);
		if (!env->vars[i])
		{
			free_env(env);
			errors_env(); //a voir si mettre un return
		}
		i++;
	}
	env->vars[i] = NULL;
	return (env);
} // 1 ligne de trop

int main(int ac, char **av, char **envp)
{
	t_env *env;
	int i = 0;

	// char *shell_env[] = 
	// {
	// 	"ceci=un",
	// 	"est=un",
	// 	"test=de_env",
	// 	NULL
	// };
	env = init_env(envp);
	while (env->vars[i])
	{
		printf("%s\n", env->vars[i]);
		i++;
	}
	free_env(env);
	return (0);
}