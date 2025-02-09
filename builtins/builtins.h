/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:53:47 by root              #+#    #+#             */
/*   Updated: 2025/02/09 17:12:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>


int		ft_pwd(void);
int		ft_cd(char **args, char **env);
int		ft_env(char **env);
int		ft_unset(char **args, char **env);
int		ft_export(char **args, char **env);
int	ft_echo(char **args);
void	ft_exit(int status);

#endif