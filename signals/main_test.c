#include "signals.h"

pid_t global_pid = 0;

int main(void)
{
	char *line;
	configure_signals();

	while (1)
	{
		line = readline("FIRST_MINI_SHELL_OMG> ");
		if (!line)
			eof_handler();
		if (*line)
			add_history(line);
		free(line);
	}
	return (0);
}


/*MAIN DONNER PAR CHATGPT JUSTE POUR TESTER AVEC SLEEP 10*/
// #include <sys/wait.h>
// #define MAX_ARGS 100 // Limite arbitraire pour les arguments
// int main(void)
// {
//     char *line;
//     pid_t pid;
//     int status;

//     configure_signals();

//     while (1)
//     {
//         line = readline("FIRST_MINI_SHELL_OMG> ");
//         if (!line)
//             eof_handler();

//         if (*line)
//         {
//             add_history(line);

//             // Parse la commande et les arguments
//             char *args[MAX_ARGS];
//             int i = 0;

//             args[i] = strtok(line, " "); // Découpe la ligne sur les espaces
//             while (args[i] != NULL && i < MAX_ARGS - 1)
//             {
//                 i++;
//                 args[i] = strtok(NULL, " ");
//             }
//             args[i] = NULL; // Le dernier élément doit être NULL pour execvp

//             pid = fork();
//             if (pid == 0)
//             {
//                 // Processus enfant : Exécuter la commande
//                 execvp(args[0], args); // args contient la commande et ses arguments
//                 perror("execvp");
//                 exit(1);
//             }
//             else if (pid > 0)
//             {
//                 // Processus parent : Attendre la fin du processus enfant
//                 waitpid(pid, &status, 0);
//             }
//             else
//             {
//                 perror("fork");
//             }
//         }
//         free(line);
//     }
//     return (0);
// }