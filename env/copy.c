#include "env.h"

char	**copy_env(char	**shell_env)
{

}

void	init_env(char **environment)
{
	g_env.var = copy_env(environment);
	if (!g_env.var)
	{
		perror("Failed to initialize environment!");
		exit(EXIT_FAILURE);
	}
}
