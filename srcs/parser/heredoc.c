/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"

/** PRS_HANDLE_REDIR
 * - Ensures that a valid filename follows each redirection operator
 * - Handle an error if the redirection is improperly formed 
 * (e.g.missing filename after redirection operator or misplaced PIPE)
 * (1) Check if the first token is PIPE -> ERROR
 * (2) Loop List, Check if token valid (INFILE, OUTFILE, HEREDOC, APPEND)
*/
int	prs_handle_redir(t_token *token)
{
	if (token && token->type == PIPE)
		return (FAILURE);
	while (token)
	{
		if (token->type == INFILE || token->type == OUTFILE
			|| token->type == HEREDOC || token->type == APPEND)
		{
			if (token->next == NULL || token->next->type != STR)
				return (FAILURE);
			token->next->type = FILENAME;
		}
		else if (token->type == PIPE && token->next == NULL)
			return (FAILURE);
		token = token->next;
	}
	return (SUCCESS);
}

/** GENERATE_RANDOM_FILENAME
 * 1. Function takes a string pointer
 * 2. Generates a filename in format "/tmp/hd_xxxxxxxx"
 * where x are random lowercase letters a-z
 *
 * @note
 * - Uses Linear Congruential Generator formula:
 *   rand = rand * 1103515245 + 12345
 * 	(Linear congruential generator)
 * - Starting seed is the input string pointer value cast to unsigned long
 * *Security note: Not cryptographically secure cuzof predictable randomness
 */
static char	*generate_random_filename(char *str)
{
	char			*new;
	int				i;
	unsigned long	rand;

	if (!str)
		return (NULL);
	new = malloc(sizeof(char) * 17);
	if (!new)
		return (NULL);
	i = 0;
	while (i < 8)
	{
		new[i] = "/tmp/hd_"[i];
		i++;
	}
	rand = (unsigned long)str;
	i = 8;
	while (i < 16)
	{
		rand = rand * 1103515245 + 12345;
		new[i] = 'a' + (rand % 26);
		i++;
	}
	new[16] = '\0';
	return (new);
}

/** PRS_HANDLE_HEREDOC
 * @param char *filename; Variable to store the name of the generated file
 * @param int fd; File descriptor for the temporary file
 * @param int end; Flag to indicate an error (if set to 1)
 * (1) Initialize the error flag to 0 (no error)
 * (2) Loop token list -> check if it's HEREDOC
 * -1  Generate a unique filename based on the heredoc content
 * -2  open() //6: 4+2(Owner can read + write); 4: Group can read
 * -3  Initialize the heredoc file with input content (if error -> end = 1)
 * -4  close(fd); + free() (Free the original value of next token and replace
 * 		it with the generated filename)
 * -5  Mark this token as NON_TERM_HEREDOC to indicate it has been processed
 * (3) Return end, which is 0 if successful or 1 if an error occurred
*/
int	prs_handle_heredoc(t_token *token)
{
	char	*filename;
	int		fd;
	int		end;

	end = 0;
	while (token != NULL && end == 0)
	{
		if (token->type == HEREDOC)
		{
			filename = generate_random_filename(token->next->value);
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (FAILURE);
			if (prs_init_heredoc(fd, token->next->value) != 0)
				end = 1;
			close(fd);
			free(token->next->value);
			token->next->value = filename;
			token->type = NON_HEREDOC;
		}
		token = token->next;
	}
	return (end);
}

/** INIT_HEREDOC
 * (1) Set up a signal handler for SIGINT,
	which will execute `sig_heredoc` when Ctrl+C is pressed.
 * (2) Start infinite loop
 * -1 Display a "heredoc>" prompt and wait for the user to enter a line of text.
 * -2 If the user enters Ctrl+D (end-of-file), `line` will be NULL.
 * -3 Check if (input match end-of-file marker) OR (signal end_heredoc triggered)
 * -4 Write the line to the file descriptor `fd` (where heredoc output is saved)
 * -5 Add a newline after each line in the output file
 * -6 Free line buffer for the next iteration
 * (3) Check if the `end_heredoc` flag in `g_signals` is set to 1,
 * -> Indicate heredoc process was interrupted (e.g., by a signal like Ctrl+C)
 * -> Reset `end_heredoc` flag to 0 so it’s ready for future heredoc operations
 * @note
 * while ((line = readline("heredoc>"))) : Check if line is non-NULL
 */
static int	init_heredoc_signal(void)
{
	if (g_signal.end_heredoc == 1)
	{
		g_signal.end_heredoc = 0;
		return (FAILURE);
	}
	return (SUCCESS);
}

int	prs_init_heredoc(int fd, char *eof_delimiter)
{
	char	*line;

	signal(SIGINT, signals_heredoc);
	while (1)
	{
		line = readline("heredoc>");
		if (!line)
		{
			ft_putstr_fd("here_doc: called end-of-line (ctrl-d)\n", 2);
			break ;
		}
		if (ft_strcmp(line, eof_delimiter) == 0 || g_signal.end_heredoc == 1)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (init_heredoc_signal());
}
