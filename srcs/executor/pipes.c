/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_toolbox1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"

// fd : pointer to fd, if NULL it means no fd to close
//*fd : if -1, invalid or uninitialized fd
void	exe_close(int *fd)
{
	if (fd && *fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

// only for child process
void	ft_close(t_shell *ctx)
{
	if (ctx)
	{
		exe_close(&(ctx->default_in));
		exe_close(&(ctx->default_out));
	}
}

// only for child process
// we close useless fds OR
// we close last fds when finished
void	close_fds(int pipes_nb, int (*fd)[2], int current_cmd,
		bool is_final_close)
{
	int	j;

	j = 0;
	while (j < pipes_nb)
	{
		if (!is_final_close)
		{
			if (j != current_cmd - 1)
			{
				exe_close(&fd[j][0]);
			}
			if (j != current_cmd)
			{
				exe_close(&fd[j][1]);
			}
		}
		else
		{
			exe_close(&fd[j][0]);
			exe_close(&fd[j][1]);
		}
		j++;
	}
}

int	ft_env_lstsize(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}
