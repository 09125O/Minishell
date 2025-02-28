/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:53:47 by root              #+#    #+#             */
/*   Updated: 2025/02/26 20:40:17 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include "env.h"
# include "utils.h"
# include "shell_ctx.h"
# include "minishell.h"

int		ft_cd(char **args, t_shell_ctx *ctx);
int		ft_echo(char **args);
int		ft_env(t_env *env);
int		ft_exit(char **args);
int		ft_export(char **args, t_env *env);
int		ft_pwd(void);
int		ft_unset(char **args, t_env *env);
int		exec_builtin(t_command *cmd, t_shell_ctx *ctx);

//utils
void	ft_error(const char *cmd, const char *arg, const char *msg);

/* Fonctions utilitaires */
int	is_builtin(const char *cmd);
int	get_builtin_index(const char *cmd);

#endif
