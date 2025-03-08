/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_build.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_BUILD_H
# define PARSE_BUILD_H

# include "../includes/mini.OD.shell.h"

typedef struct s_shell		t_shell;
typedef struct s_env		t_env;
typedef enum e_token_type	t_token_type;
typedef struct s_token		t_token;
typedef struct s_arg		t_arg;
typedef struct s_filename	t_filename;

typedef enum e_token_type
{
	INFILE,
	OUTFILE,
	HEREDOC,
	NON_HEREDOC,
	APPEND,
	PIPE,
	STR,
	SGL_QUOTE,
	DBL_QUOTE,
	COMMAND,
	FILENAME,
	ARG,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_shell			*content;
	t_token_type	type;
	t_token			*next;
}	t_token;

typedef struct s_arg
{
	char	*value;
	t_arg	*next;
}	t_arg;

typedef struct s_filename
{
	char			*path;
	t_token_type	type;
	t_filename		*next;
}	t_filename;

typedef struct s_exec
{
	char				*cmd;
	t_arg				*args;
	t_filename			*redirs;
	struct s_exec		*next;
	int					fd_in;
	int					fd_out;
}						t_exec;

/*********************************/
/************ PARSING ************/
/*********************************/
/*parsing*/
int			parsing(t_token **token);
int			prs_check_allnodes_null(t_token *token);
int			prs_remove_node_null(t_token **head);
int			prs_handle_cmd(t_token *token);
void		prs_unlink_error(t_token *token);

/*parsing helper*/
t_env		*get_env(char *pathname, t_env *env);
char		*prs_tokens_combine(t_token *token);
char		*check_null_strjoin(char *s1, char *s2);

/*********************************/
/*********** EXPANSION ***********/
/*********************************/
/*expansion*/
int			prs_count_dollar_sign(char *input_str);
char		*prs_exapnd_1envvar(char *str, char *envvar_found,
				t_shell *content);
int			prs_handle_envvar_expansion(t_token *token);

/*expansion env*/
int			ft_envvar_len(char *env_var);
char		*get_envvar_name(char *env_var);
char		*get_str_before_envvar(char *full_str, char *env_var);
char		*get_str_after_envvar(char *env_var);
char		*get_envvar_value(char *env_var, t_shell *content);

/*expansion helper*/
char		*handle_qmark_exit_status(t_shell *content);
char		*handle_dollar_pid(void);
int			prs_expand_env(t_token *token);

/************ HEREDOC ************/
int			prs_handle_redir(t_token *token);
int			prs_handle_heredoc(t_token *token);
int			prs_init_heredoc(int fd, char *eof_delimiter);

/************ QUOTES ************/
/*quotes*/
int			prs_check_quotes_valid(t_token *token);
t_token		*prs_quotes_to_tokens(char *input_str, t_shell *content);
int			prs_handle_quotes_n_expand_env(t_token *token);

/*quotes helper*/
t_token		*prs_get_quoted_str(char *input_str, char c, t_shell *content);
int			ft_quotes_len(char *str, char sd_quote);
int			ft_rogue_len(char *str);

/*********************************/
/********* BUILD TO EXEC *********/
/*********************************/
/*build to exec*/
t_exec		*build_to_exec(t_token *token);
t_exec		*init_build(void);
int			bd_handle_pipe(t_exec *exec, t_token *token);
int			bd_handle_cmd(t_exec *exec, t_token *token);

/*build helper*/
int			ft_build_lstsize(t_exec *exec);
void		build_free_all(t_exec *exec);

/*build args*/
int			bd_handle_args(t_exec *exec, t_token *token);
t_arg		*bd_args_create(char *arg_value);
int			arg_add_back(t_arg **head, t_arg *new);
void		arg_free(t_arg *args);

/*build filenames*/
int			bd_handle_redirs(t_exec *exec, t_token *token);
t_filename	*bd_filenames_create(char *pathname, t_token_type type);
int			filename_add_back(t_filename **head, t_filename *new);
void		filename_free(t_filename *filename);

#endif
