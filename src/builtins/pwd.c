/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:26:37 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/17 17:04:17 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	ft_pwd(t_shell *shell)
{
	char	*pwd;

	if (shell->pwd)
	{
		ft_putendl_fd(shell->pwd, 1);
		return (EXIT_SUCCESS);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		print_error("pwd", NULL, strerror(errno));
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (EXIT_SUCCESS);
}
