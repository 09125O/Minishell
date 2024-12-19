/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:18:11 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/19 11:16:31 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include "parser.h"

typedef struct s_pipe
{
	int		read_fd;
	int		write_fd;
}	t_pipe;

typedef struct s_process
{
	pid_t	pid;
	int		status;
	int		pipe_in;
	int		pipe_out;
}	t_process;

/* executor.c */
int		execute_ast(t_shell *shell, t_ast *ast);

/* exec_cmd.c */
int		is_builtin(char *cmd);
int		execute_command(t_shell *shell, t_command *cmd);
int		execute_builtin(t_shell *shell, t_command *cmd);
int		execute_external(t_shell *shell, t_command *cmd);

/* exec_pipeline.c */
int		execute_pipeline(t_shell *shell, t_ast *pipeline);

/* exec_pipeline_utils.c*/
void	init_pipes(t_pipe *pipes, int count);
int		create_pipes(t_pipe *pipes, int count);
int		setup_pipeline(t_process *proc, t_pipe *pipes, int cmd_count);

/* process.c */
int		create_process(t_shell *shell, t_command *cmd, t_pipe *in, t_pipe *out);
void	child_process(t_shell *shell, t_command *cmd, t_pipe *in, t_pipe *out);

/* wait.c */
int		wait_processes(t_process *processes, int count);
int		get_exit_status(int status);

/* path_resolver.c */
char	*find_command_path(char *cmd, char **env_path);
char	**get_path_dirs(char **env);

/* redirect_in.c */
int		setup_input_redirect(t_command *cmd);
int		apply_input_redirect(char *file);

/* redirect_out.c */
int		setup_output_redirect(t_command *cmd);
int		apply_output_redirect(char *file, int append);

/* heredoc.c */
int		handle_heredoc(char *delim);
void	cleanup_heredoc(void);

/* exec_utils.c */
void	save_io(int *saved);
void	restore_io(int *saved);
void	close_pipe(t_pipe *pipe);

#endif
