/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:53:47 by root              #+#    #+#             */
/*   Updated: 2025/02/10 12:51:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include "../env/env.h"
# include "../utils/utils.h"

int		ft_pwd(void);
int		ft_cd(char **args, t_env *env);
int		ft_env(t_env *env);
int		ft_unset(char **args, t_env *env);
int		ft_export(char **args, t_env *env);
int		ft_echo(char **args);
void	ft_exit(int status);

void	ft_error(char *cmd, char *arg, char *msg);

#endif