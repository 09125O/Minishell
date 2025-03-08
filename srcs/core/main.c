/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/09 00:22:35 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"

/** READ N LOOP */
//readline returns NULL if receieves EOF(Ctrl+D), standard behavior
int	read_n_loop(t_shell *content)
{
	char	*line;

	(void)content;
	line = NULL;
	while (1)
	{
		init_signals();
		line = readline(PROMPT);
		if (!line)
			break ;
		else if (check_line_empty(line) == 0)
		{
			add_history(line);
			if (process_input(content, line) != 0)
			{
				ft_putstr_fd("Syntax Error\n", 2);
				content->exit_code = 2;
			}
			line = NULL;
		}
		if (line)
			free(line);
	}
	return (0);
}

int	main(int ac, char *av[], char *env[])
{
	t_shell	*content;

	content = NULL;
	(void)ac;
	(void)av;
	content = init_shell(env);
	if (!content)
		return (EXIT_FAILURE);
	read_n_loop(content);
	free_all_shell(content);
	rl_clear_history();
	ft_putstr_fd("exit\n", 2);
	return (EXIT_SUCCESS);
}
