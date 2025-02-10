/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:50:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/10 22:25:54 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int count_args(char **args)
{
    int count = 0;
    while (args && args[count])
        count++;
    return (count);
}

static char **resize_args_array(char **old_args, int new_size)
{
    char **new_args = malloc(sizeof(char *) * (new_size + 1));
    if (!new_args)
		return (NULL);
    int i = 0;
    while (old_args[i] && i < new_size - 1)
	{
        new_args[i] = old_args[i];
        i++;
    }
    new_args[new_size - 1] = NULL;
    free(old_args);
    return (new_args);
}

void free_redirect(t_redirect *redirect)
{
    t_redirect *next;
    while (redirect)
	{
        next = redirect->next;
        if (redirect->file)
            free(redirect->file);
        free(redirect);
        redirect = next;
    }
}

void free_ast(t_ast *ast)
{
    if (!ast)
		  return;
    if (ast->left)
		  free_ast(ast->left);
    if (ast->right)
		  free_ast(ast->right);
    if (ast->cmd)
		  free_command(ast->cmd);
    free(ast);
}
