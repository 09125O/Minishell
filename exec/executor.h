/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhour <obouhour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 12:46:39 by obouhour          #+#    #+#             */
/*   Updated: 2024/12/21 16:42:48 by obouhour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

typedef struct s_exec
{

} t_exec;
//A voir avec le parsing pour cette struct
typedef struct s_redirection
{
	char	*input_file;	// <
	char	*output_file;	// >
	char	*append_file;	// >>
	char	*heredoc_delim;	// <<
} t_redirection;
/// A voir aussi avec le parsing pour cette struct
typedef	struct s_command
{

} t_command;

//exec
void	exec_command(char *cmd, char **env);

//find path
char	*path_finder(char *cmd, char **env);

//redirections
void	handle_redirection(t_redirection *redir);

//utils
char	**ft_split(const char *s, char c);
void	free_dbl_tab(char **tab);

#endif