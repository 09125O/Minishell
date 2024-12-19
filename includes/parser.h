/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:17:55 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/18 00:41:01 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef struct s_redirect
{
	char				*file;
	t_token_type		type;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command
{
	char				**args;
	t_redirect			*redirects;
	struct s_command	*next;
}	t_command;

typedef struct s_ast
{
	t_command			*cmd;
	struct s_ast		*left;
	struct s_ast		*right;
}	t_ast;

/* parser.c */
t_ast		*parser(t_token *tokens);

/* parser_utils.c */
void		free_command(t_command *cmd);
void		free_ast(t_ast *ast);
t_command	*create_command(void);
t_redirect	*create_redirect(char *file, t_token_type type);

/* ast_creator.c */
t_ast		*create_ast_node(t_command *cmd);
t_ast		*build_pipeline(t_token *tokens);

/* ast_utils.c */
void		add_arg_to_command(t_command *cmd, char *arg);
void		add_redirect_to_command(t_command *cmd, t_redirect *redir);

/* var_expander.c */
char		*expand_variables(char *str, char **env);
char		*get_var_value(char *var_name, char **env);

/* quote_handler.c */
char		get_quote_type(char c);
int			find_closing_quote(const char *str, int *i, char quote);
char		*handle_quotes(char *str);
int			is_quoted(char *str);

/* word_splitter.c */
char		**split_words(char *str);
void		free_word_array(char **words);

#endif
