/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 12:46:39 by obouhour          #+#    #+#             */
/*   Updated: 2025/02/04 17:08:28 by root             ###   ########.fr       */
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
#include "../env/env.h"
#include "../signals/signals.h"
#include "../utils/utils.h"

typedef struct s_exec
{
	int				pipe_count;		// Le nombre de pipe
	int				**pipes;		// Un double tableau qui gerera les pipes
	int				last_exit_code; // Le derniers code d'erreurs a ressortir, il sera recup grace a WIFEXITED
} t_exec;

//A voir avec le parsing pour cette struct
typedef struct s_redirection
{
	char			*input_file;	// <
	char			*output_file;	// >
	char			*append_file;	// >>
	char			*heredoc_delim;	// <<
} t_redirection;

/// A voir aussi avec le parsing pour cette struct
typedef	struct s_command
{
	char			**args; //arguments par ex "["ls", "-l", NULL]"
	t_redirection	*redir;
} t_command;

//exec
void	execute_commands(t_command **commands, int cmd_count, char **env);
void exec_command(char **args, char **env);

//find path
char	*path_finder(char *cmd, char **env);

//redirections
void	handle_redirection(t_redirection *redir);

//handle process
void	spawn_processes(t_exec *exec, t_command **commands, int cmd_count, char **env);
void	setup_pipes(t_exec *exec, int cmd_index, int cmd_count);
void	close_pipes(t_exec *exec);

#endif