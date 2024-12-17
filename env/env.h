/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhour <obouhour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:31:16 by obouhour          #+#    #+#             */
/*   Updated: 2024/12/17 12:35:39 by obouhour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
#define ENV_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <term.h>
#include <curses.h>

#define ERROR_ENV_MESS "Failed to initialize environment!"

typedef struct s_env
{
	char	**vars;//tableau qui contiendras les variable d'environnement
	int		size_vars;//nombre de variables (ou de string) que contient l'environnement
} t_env;

//utils
void	errors_env(void);
int		ft_strlen(char *str);
char	*ft_strdup(char *src);
void free_env(t_env *env);

#endif

/*
Malloc:
- env (struct)
- env.vars (double tableau)
- env.vars[i] (chaque chaine dans le tableau est malloc avec strdup)
*/