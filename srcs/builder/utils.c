/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"

int	ft_build_lstsize(t_exec *exec)
{
	int	len;

	len = 0;
	while (exec)
	{
		exec = exec->next;
		len++;
	}
	return (len);
}

void	build_free_all(t_exec *exec)
{
	t_exec	*current;

	while (exec != NULL)
	{
		current = exec;
		if (exec->cmd)
			free(exec->cmd);
		if (exec->args)
			arg_free(exec->args);
		if (exec->redirs)
			filename_free(exec->redirs);
		exec = exec->next;
		free(current);
	}
}
