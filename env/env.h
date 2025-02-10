/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:31:16 by obouhour          #+#    #+#             */
/*   Updated: 2025/02/10 13:17:06 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
#define ENV_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <term.h>
#include <curses.h>

#define ERROR_ENV_MESS "Failed to initialize environment!"

typedef struct s_env
{
	char	**vars;//tableau qui contiendras les variable d'environnement
	int		size_vars;//nombre de variables (ou de string) que contient l'environnement
} t_env;

#include "../exec/executor.h"
#include "../signals/signals.h"
#include "../utils/utils.h"
#include "../builtins/builtins.h"

//Recherche/modif/suppr d'une variable d'environnement
t_env	*init_env(char **shell_env);
char	*search_env_variable(t_env *env, char *key);
int		remove_env_var(t_env *env, char *key);
int		update_env_variable(t_env *env, char *key, char *new_value);

//utils
void	free_env(t_env *env);
void	errors_env(void);

#endif

//
// Malloc:
// - env (struct)
// - env.vars (double tableau)
// - env.vars[i] (chaque chaine dans le tableau est malloc avec strdup)
//