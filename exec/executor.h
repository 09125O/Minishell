/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhour <obouhour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 12:46:39 by obouhour          #+#    #+#             */
/*   Updated: 2024/12/21 15:20:45 by obouhour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

typedef struct s_exec
{

} t_exec;

typedef struct s_redirection
{

} t_redirection;

typedef	struct s_command
{
	/* data */
} t_command;

//exec
void	exec_command(char *cmd, char **env);

//find path
char	*path_finder(char *cmd, char **env);

//utils
char	**ft_split(const char *s, char c);
void	free_dbl_tab(char **tab);

#endif