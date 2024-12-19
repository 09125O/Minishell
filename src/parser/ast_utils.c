/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:50:01 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/18 00:35:31 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include "libft.h"

static int	count_args(char **args)
{
   int	count;

   count = 0;
   while (args && args[count])
   	count++;
   return (count);
}

static char	**resize_args_array(char **old_args, int new_size)
{
   char	**new_args;
   int		i;

   new_args = malloc(sizeof(char *) * (new_size + 1));
   if (!new_args)
   	return (NULL);
   i = 0;
   while (old_args[i] && i < new_size - 1)
   {
   	new_args[i] = old_args[i];
   	i++;
   }
   new_args[new_size - 1] = NULL;
   new_args[new_size] = NULL;
   free(old_args);
   return (new_args);
}

void	add_arg_to_command(t_command *cmd, char *arg)
{
   int		arg_count;
   char	**new_args;

   if (!cmd || !arg)
   	return ;
   arg_count = count_args(cmd->args);
   new_args = resize_args_array(cmd->args, arg_count + 2);
   if (!new_args)
   {
   	free(arg);
   	return ;
   }
   new_args[arg_count] = arg;
   cmd->args = new_args;
}

void	add_redirect_to_command(t_command *cmd, t_redirect *redir)
{
   t_redirect	*current;

   if (!cmd || !redir)
   	return ;
   if (!cmd->redirects)
   {
   	cmd->redirects = redir;
   	return ;
   }
   current = cmd->redirects;
   while (current->next)
   	current = current->next;
   current->next = redir;
}

int	validate_ast(t_ast *ast)
{
   if (!ast)
   	return (0);
   if (!ast->cmd || !ast->cmd->args || !ast->cmd->args[0])
   	return (0);
   if (ast->right && !validate_ast(ast->right))
   	return (0);
   return (1);
}
