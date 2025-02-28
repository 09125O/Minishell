/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: d9125 <d9125@me.com>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:00:00 by d9125             #+#    #+#           */
/*   Updated: 2024/03/19 11:30:00 by d9125            ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "types.h"
# include "minishell.h"
# include "env.h"

# define PIPE_READ 0
# define PIPE_WRITE 1

/* Fonctions d'exécution des commandes */
int		execute_commands(t_command **commands, int cmd_count, t_shell_ctx *ctx);
int		exec_single_command(t_command *cmd, t_shell_ctx *ctx);
int		exec_builtin(t_command *cmd, t_shell_ctx *ctx);
char	*find_command_path(char *cmd, t_shell_ctx *ctx);
char	*path_finder(char *cmd, t_env *env);

/* Fonctions de gestion des processus */
int		spawn_processes(t_exec *exec, int cmd_count);
void	close_pipes(t_exec *exec);
void	cleanup_pipes(t_exec *exec);
int		**create_pipes(t_exec *exec, int cmd_count);

/* Fonctions de redirection */
int		setup_redirections(t_command *cmd, t_shell_ctx *ctx);
int		restore_redirections(void);

/* Fonctions de gestion des descripteurs de fichiers */
t_fd_backup	*save_fds(void);
void	restore_fds(t_fd_backup *backup);

#endif
