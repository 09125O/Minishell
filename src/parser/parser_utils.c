/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:49:31 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/18 00:34:33 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include "libft.h"

void	free_redirect(t_redirect *redirect)
{
   t_redirect	*next;

   while (redirect)
   {
   	next = redirect->next;
   	if (redirect->file)
   		free(redirect->file);
   	free(redirect);
   	redirect = next;
   }
}

void	free_command(t_command *cmd)
{
   int	i;

   if (!cmd)
   	return ;
   if (cmd->args)
   {
   	i = 0;
   	while (cmd->args[i])
   		free(cmd->args[i++]);
   	free(cmd->args);
   }
   free_redirect(cmd->redirects);
   free(cmd);
}

t_command	*create_command(void)
{
   t_command	*cmd;

   cmd = malloc(sizeof(t_command));
   if (!cmd)
   	return (NULL);
   cmd->args = malloc(sizeof(char *));
   if (!cmd->args)
   {
   	free(cmd);
   	return (NULL);
   }
   cmd->args[0] = NULL;
   cmd->redirects = NULL;
   cmd->next = NULL;
   return (cmd);
}

t_redirect	*create_redirect(char *file, t_token_type type)
{
   t_redirect	*redirect;

   redirect = malloc(sizeof(t_redirect));
   if (!redirect)
   	return (NULL);
   redirect->file = ft_strdup(file);
   if (!redirect->file)
   {
   	free(redirect);
   	return (NULL);
   }
   redirect->type = type;
   redirect->next = NULL;
   return (redirect);
}

void	free_ast(t_ast *ast)
{
   if (!ast)
   	return ;
   if (ast->left)
   	free_ast(ast->left);
   if (ast->right)
   	free_ast(ast->right);
   if (ast->cmd)
   	free_command(ast->cmd);
   free(ast);
}
