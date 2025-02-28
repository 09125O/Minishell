#ifndef SHELL_CTX_H
# define SHELL_CTX_H

# include <stdbool.h>
# include "types.h"
# include "env.h"
# include "s_lexer.h"
# include "s_parser.h"
# include "executor.h"

/* Fonctions de gestion du contexte */
t_shell_ctx	*init_shell_ctx(char **envp);
void		update_shell_ctx(t_shell_ctx *ctx);
void		free_shell_ctx(t_shell_ctx *ctx);
void		set_shell_error(t_shell_ctx *ctx, int code, const char *message);
void		clear_shell_error(t_shell_ctx *ctx);
void		set_last_status(t_shell_ctx *ctx, int status);
int			get_last_status(t_shell_ctx *ctx);

#endif
