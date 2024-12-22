/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhour <obouhour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 12:46:39 by obouhour          #+#    #+#             */
/*   Updated: 2024/12/22 12:33:45 by obouhour         ###   ########.fr       */
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
	int				pipe_count;	// Le nombre de pipe
	int				**pipes;	//	un double tableau qui gerera les pipes
	int				last_exit_code;
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

//utils
char	**ft_split(const char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	free_dbl_tab(char **tab);
int		ft_strcmp(char *s1, char *s2);
size_t	ft_strlen(const char *str);

#endif