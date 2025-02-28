#include "shell_ctx.h"
#include "libft.h"
#include <unistd.h>

t_shell_ctx	*init_shell_ctx(char **envp)
{
	t_shell_ctx	*ctx;

	ctx = malloc(sizeof(t_shell_ctx));
	if (!ctx)
		return (NULL);
	ctx->env = env_init(envp);
	if (!ctx->env)
	{
		free(ctx);
		return (NULL);
	}
	ctx->cwd = NULL;
	ctx->old_pwd = NULL;
	ctx->last_status = 0;
	ctx->shell_pid = getpid();
	ctx->is_interactive = isatty(STDIN_FILENO);
	ctx->last_error.code = 0;
	ctx->last_error.message = NULL;
	return (ctx);
}

void	update_shell_ctx(t_shell_ctx *ctx)
{
	char	*pwd;

	if (!ctx)
		return ;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		if (ctx->old_pwd)
			free(ctx->old_pwd);
		ctx->old_pwd = ctx->cwd;
		ctx->cwd = pwd;
	}
}

void	set_shell_error(t_shell_ctx *ctx, int code, const char *message)
{
	if (!ctx)
		return ;
	ctx->last_error.code = code;
	ctx->last_error.message = (char *)message;
}

void	clear_shell_error(t_shell_ctx *ctx)
{
	if (!ctx)
		return ;
	ctx->last_error.code = 0;
	ctx->last_error.message = NULL;
}

void	set_last_status(t_shell_ctx *ctx, int status)
{
	if (!ctx)
		return ;
	ctx->last_status = status;
}

int	get_last_status(t_shell_ctx *ctx)
{
	if (!ctx)
		return (1);
	return (ctx->last_status);
}

void	free_shell_ctx(t_shell_ctx *ctx)
{
	if (!ctx)
		return ;
	if (ctx->env)
		env_free(ctx->env);
	if (ctx->cwd)
		free(ctx->cwd);
	if (ctx->old_pwd)
		free(ctx->old_pwd);
	free(ctx);
}
