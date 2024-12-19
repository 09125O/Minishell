/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:47:17 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/19 18:06:44 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------------------------------------------------------------- */
/*                         GESTION DES CHEMINS READLINE                        */
/* --------------------------------------------------------------------------- */
#if defined(__APPLE__) && defined(__MACH__)
    #include <readline/readline.h>
    #include <readline/history.h>
    #define CLEAR_HISTORY clear_history
#else
    #include <readline/readline.h>
    #include <readline/history.h>
    #define CLEAR_HISTORY rl_clear_history
#endif
/* --------------------------------------------------------------------------- */

/* Définition unique de la variable globale */
int	g_signal_status = 0;

static int	custom_complete(int count, int key)
{
   char	*input;

   input = rl_line_buffer;
   if (!input || !*input || (*input && is_whitespace(*input)))
   	return (rl_insert(count, key));
   return (rl_complete(count, key));
}

static void	process_input(t_shell *shell)
{
	t_token	*tokens;
	t_ast	*ast;

	if (!shell->input || !*shell->input)
		return ;
	tokens = lexer(shell->input);
	if (!tokens)
		return ;
	ast = parser(tokens);
	free_token_list(tokens);
	if (!ast)
		return ;
	shell->exit_status = execute_ast(shell, ast);
	free_ast(ast);
}

static void	cleanup_shell(t_shell *shell)
{
	if (shell->input)
		free(shell->input);
	if (shell->pwd)
		free(shell->pwd);
	if (shell->oldpwd)
		free(shell->oldpwd);
	if (shell->env_array)
		free_str_array(shell->env_array);
	if (shell->env)
		free_env_list(shell->env);
	/*rl_clear_history();*/
	/* Nettoyage de l'historique Readline */
	CLEAR_HISTORY();
}

int	main(int argc, char **argv, char **envp)
{
   t_shell	shell;

   (void)argv;
   if (argc != 1)
   {
		ft_putendl_fd("minishell: too many arguments", 2);
   		return (EXIT_FAILURE);
   }
   init_shell(&shell, envp);
   rl_outstream = stderr;
   rl_bind_key('\t', custom_complete);
   while (1)
   {
   	shell.input = readline("minishell> ");
   	if (!shell.input)
   		break ;
   	if (shell.input[0])
   	{
   		add_history(shell.input);
   		process_input(&shell);
   	}
   	free(shell.input);
   	shell.input = NULL;
   }
   cleanup_shell(&shell);
   return (shell.exit_status);
}
