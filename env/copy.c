/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhour <obouhour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:10:09 by obouhour          #+#    #+#             */
/*   Updated: 2024/12/19 10:51:40 by obouhour         ###   ########.fr       */
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

static t_env	*shell_env_null(t_env *env, char **shell_env)
{
	env->size_vars = 0;
	env->vars = malloc(sizeof(char *)); // Allouer un tableau vide
	if (!env->vars)
	{
		free(env);
		errors_env(); // Gère l'échec de malloc
	}
	env->vars[0] = NULL; // Terminer le tableau par NULL
	return (env);
}

t_env	*init_env(char **shell_env)
{
	t_env	*env;
	int		i;

	i = 0;
	env = malloc(sizeof(t_env));
	if (!env)
		errors_env();
	if (!shell_env)
		return (shell_env_null(env, shell_env));
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
} //ligne de trop


/*
Chaque main ici deviendras par la suite une fontion "propre"
qui sera mise en relation avec le programme.
*/

/*MAIN POUR VOIR TOUS L'ENV*/
// int main(int ac, char **av, char **envp)
// {
// 	t_env	*env;
// 	int		i = 0;
// 	char	*value;

// 	env = init_env(NULL);//Tester avec NULL/envp et les sont OK
// 	if (env->vars[0] == NULL)
// 		perror(ERROR_ENV_MESS);
// 	while (env->vars[i])
// 	{
// 		printf("%s\n", env->vars[i]);
// 		i++;
// 	} //Pour faire apparaitre tous l'environnement
// 	free_env(env);
// 	return (0);
// }

/*MAIN POUR VOIR LA VALEUR D'UNE VARIABLE*/
// int main(int ac, char **av, char **envp)
// {
// 	t_env	*env;
// 	int		i = 0;
// 	char	*value;

// 	env = init_env(envp);
// 	if (!env)
// 	{
// 		perror("Failed to initialize environment");
// 		return (EXIT_FAILURE);
// 	}
// 	value = search_env_variable(env, av[1]);
// 	if (!value)
// 		printf("Failed to find variable");
// 	else
// 		printf("%s\n", value);//montre la valeur d'une variable passer en arg
// 	free_env(env);
// 	return (0);
// }

/*MAIN POUR LE REMOVE*/
// int main(int ac, char **av, char **envp)
// {
// 	t_env	*env;
// 	int		i = 0;
// 	char	*value;

// 	env = init_env(envp);
// 	if (!env)
// 	{
// 		perror("Failed to initialize environment");
// 		return (EXIT_FAILURE);
// 	}
// 	while (env->vars[i])
// 	{
// 		printf("%s\n", env->vars[i]);
// 		i++;
// 	} //Pour faire apparaitre tous l'environnement
// 	i = 0;
// 	if (remove_env_var(env, av[1]) == 0)
// 	{
// 		printf("\n\n\nAPRES\n\n\n");
// 		while (env->vars[i])
// 		{
// 			printf("%s\n", env->vars[i]);
// 			i++;
// 		}
// 	}
// 	else
// 		printf("Variable not found");
// 	free_env(env);
// 	return (0);
// }

/*MAIN POUR TESTER LA MODIFICATION OU LE RAJOUT*/
// int main(int argc, char **argv, char **envp)
// {
// 	t_env	*env;
// 	int		i = 0;

// 	if (argc != 3)
// 	{
// 		printf("Usage: <VARIABLE> <VALUE>\n");
// 		return (EXIT_FAILURE);
// 	}
// 	env = init_env(envp);
// 	if (!env)
// 	{
// 		perror("Failed to initialize environment");
// 		return (EXIT_FAILURE);
// 	}
// 	printf("AVANT update:\n");
// 	while ( env->vars[i])
// 	{
// 		printf("%s\n", env->vars[i]);
// 		i++;
// 	}
// 	if (update_env_variable(env, argv[1], argv[2]) == -1)
// 	{
// 		printf("Failed to update variable.\n");
// 		free_env(env);
// 		return (EXIT_FAILURE);
// 	}
// 	printf("\nAPRES update:\n");
// 	i = 0;
// 	while (env->vars[i])
// 	{
// 		printf("%s\n", env->vars[i]);
// 		i++;
// 	}
// 	free_env(env);
// 	return (0);
// }

