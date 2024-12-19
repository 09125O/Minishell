/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:18:45 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/17 16:59:53 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "utils.h"
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>

/* echo.c */
int		ft_echo(char **args);

/* cd.c */
int		ft_cd(t_shell *shell, char **args);

/* pwd.c */
int		ft_pwd(t_shell *shell);

/* export.c */
int		ft_export(t_shell *shell, char **args);

/* export_utils.c */
void	sort_env_vars(char **vars);
void	print_sorted_env(t_shell *shell);
int		is_valid_identifier(char *str);

/* unset.c */
int		ft_unset(t_shell *shell, char **args);

/* env.c */
int		ft_env(t_shell *shell);

/* exit.c */
int		ft_exit(t_shell *shell, char **args);

#endif
