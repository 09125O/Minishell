/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../includes/mini.OD.shell.h"
# include <stdbool.h>

typedef struct s_shell		t_shell;
typedef struct s_env		t_env;
typedef struct s_exec		t_exec;
typedef struct s_arg		t_arg;
typedef struct s_filename	t_filename;

# define MAX_FDS 1024

void						exe_close(int *fd);
void						ft_close(t_shell *ctx);
int							open_pipes(int pipes_nb, int (*fd)[2]);
void						close_fds(int pipes_nb, int (*fd)[2],
								int current_cmd, bool is_final_close);
int							ft_args_lstsize(t_arg *args);
void						exec_args_create(t_exec *temp, int args_nb,
								char *args[args_nb]);
int							ft_char_count(char *str, char c);
char						*find_path(char *cmd, t_env *env);
int							ft_env_lstsize(t_env *env);
char						**env_format(t_env *env);
void						err_execve(char *path, int err_no);
int							ft_execution(t_shell *ctx, t_exec *temp);
void						child_process(t_shell *ctx, int (*fd)[2], int i,
								t_exec *temp);
void						exe_err_coredump(int pid);
void						wait_children(int pid_count, t_shell *ctx);
int							exec(t_shell *ctx);
int							exec_parent(t_shell *ctx);
void						set_std(t_shell *ctx, int mode);
void						unlink_all(t_shell *ctx);
int							err_redirs(t_exec *exec, t_shell *ctx);
int							exec_redirs(t_exec *exec);
int							redirs_type(t_filename *file);
int							err_pipe(int err_no, t_shell *ctx);
int							err_fork(int err_no, t_shell *ctx, int fd[][2]);
void						close_all(int pipe_nb, int (*fd)[2]);
void						err_open(int err_no, char *file);
void						ft_free_all(char **arr);
int							check_is_alr_path(char *cmd);

#endif
