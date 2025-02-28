#ifndef ENV_H
# define ENV_H

# include <stdlib.h>
# include <stdbool.h>
# include "libft.h"
# include "shell_ctx.h"
# include "types.h"

/* Codes de retour pour les opérations sur l'environnement */
typedef enum e_env_status
{
	ENV_SUCCESS = 0,
	ENV_NOT_FOUND = 1,
	ENV_INVALID_KEY = 2,
	ENV_INVALID_VALUE = 3,
	ENV_MALLOC_ERROR = 4,
	ENV_ERROR = 5
}	t_env_status;

/* Fonctions principales */
t_env			*env_init(char **envp);
void			env_free(t_env *env);

/* Fonctions de gestion des variables */
int				env_add(t_env **env, const char *key, const char *value);
char			*env_get(t_env *env, const char *key);
int				env_remove(t_env **env, const char *key);
int				env_is_valid_key(const char *key);

/* Fonctions d'affichage et de conversion */
char			**env_to_array(t_env *env);
void			env_array_free(char **env_array);
void			env_sort_and_print(t_env *env);

/* Fonctions de synchronisation */
void			env_lock(void);
void			env_unlock(void);
int				env_update_from_child(t_env **env, char **child_env);

/* Fonctions de gestion des variables spéciales */
int				env_set_shell_name(t_env **env, const char *name);
int				env_set_shell_pid(t_env **env);
int				env_set_last_bg_pid(t_env **env, int pid);
int				env_set_status(t_env **env, int status);
char			*get_special_var(const char *var_name, t_shell_ctx *ctx);

/* Fonctions d'expansion de variables */
char			*env_expand_quoted(t_env *env, const char *str, char quote, t_shell_ctx *ctx);
char			*env_expand_var(t_env *env, const char *str, t_shell_ctx *ctx);
char			*expand_next_var(t_env *env, const char *str, t_shell_ctx *ctx);
char			*expand_simple_var(t_env *env, const char *var_name, t_shell_ctx *ctx);

/* Fonctions utilitaires */
int				get_var_length(const char *str);
char			*get_env_key(const char *env_str);
char			*get_env_value(const char *env_str);
char			*get_var_name(const char *str);
char			*join_and_free(char *s1, char *s2);
char			*ft_strjoin_char(char *str, char c);
t_env			*create_env_node(const char *key, const char *value);

/* Fonctions de gestion des variables spéciales */
int				is_special_var(const char *var_name);
void			update_special_var(t_shell_ctx *ctx, const char *var_name, int value);

/* Fonctions de gestion du répertoire de travail */
int				env_update_pwd(t_env **env);

#endif
