/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:08:02 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/17 16:19:22 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	handle_signal_status(int status)
{
   if (WIFSIGNALED(status))
   {
   	if (WTERMSIG(status) == SIGQUIT)
   		ft_putstr_fd("Quit (core dumped)\n", 2);
   	return (128 + WTERMSIG(status));
   }
   return (WEXITSTATUS(status));
}

int	get_exit_status(int status)
{
   if (WIFEXITED(status))
   	return (WEXITSTATUS(status));
   return (handle_signal_status(status));
}

static void	store_process_status(t_process *proc, int status)
{
   if (WIFEXITED(status))
   	proc->status = WEXITSTATUS(status);
   else if (WIFSIGNALED(status))
   	proc->status = 128 + WTERMSIG(status);
   else
   	proc->status = 1;
}

static int	get_last_status(t_process *processes, int count)
{
   if (count > 0)
   	return (processes[count - 1].status);
   return (1);
}

int	wait_processes(t_process *processes, int count)
{
   int	i;
   int	status;

   i = 0;
   while (i < count)
   {
   	if (processes[i].pid > 0)
   	{
   		waitpid(processes[i].pid, &status, 0);
   		store_process_status(&processes[i], status);
   	}
   	i++;
   }
   return (get_last_status(processes, count));
}
