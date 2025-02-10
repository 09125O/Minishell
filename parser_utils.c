/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:49:31 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/10 22:25:23 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_command *create_command(void)
{
    t_command *cmd = malloc(sizeof(t_command));
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
    return (cmd);
}

t_redirect *create_redirect(char *file, t_token_type type)
{
    t_redirect *redirect = malloc(sizeof(t_redirect));
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

void add_arg_to_command(t_command *cmd, char *arg)
{
    if (!cmd || !arg)
		return;
    int arg_count = count_args(cmd->args);
    char **new_args = resize_args_array(cmd->args, arg_count + 2);
    if (!new_args)
	{
        free(arg);
        return;
    }
    new_args[arg_count] = arg;
    cmd->args = new_args;
}

void add_redirect_to_command(t_command *cmd, t_redirect *redir)
{
    if (!cmd || !redir)
		return;
    if (!cmd->redirects)
	{
        cmd->redirects = redir;
        return;
    }
    t_redirect *current = cmd->redirects;
    while (current->next)
        current = current->next;
    current->next = redir;
}

void free_command(t_command *cmd)
{
    if (!cmd)
        return;
    if (cmd->args)
    {
        int i = 0;
        while (cmd->args[i])
        {
            free(cmd->args[i]);
            i++;
        }
        free(cmd->args);
    }
    free_redirect(cmd->redirects);
    free(cmd);
}
