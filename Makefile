# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 16:10:21 by douzgane          #+#    #+#              #
#    Updated: 2025/02/25 19:51:42 by douzgane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I includes -I libft/inc -I/opt/homebrew/opt/readline/include
LIBS = -L libft -lft -L/opt/homebrew/opt/readline/lib -lreadline

# Dossiers
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = libft

# Headers
HEADERS = $(INC_DIR)/minishell.h \
	$(INC_DIR)/builtins.h \
	$(INC_DIR)/env.h \
	$(INC_DIR)/s_lexer.h \
	$(INC_DIR)/s_parser.h \
	$(INC_DIR)/executor.h \
	$(INC_DIR)/signals.h \
	$(INC_DIR)/utils.h

# Sources
MAIN_SRC = main.c

BUILTINS_SRC = builtins/cd.c \
	builtins/echo.c \
	builtins/env.c \
	builtins/exit.c \
	builtins/export.c \
	builtins/pwd.c \
	builtins/unset.c \
	builtins/utils.c

ENV_SRC = env/env_core.c \
	env/env_expand.c \
	env/env_expand_utils.c \
	env/env_parser.c \
	env/env_utils.c \
	env/env_ops.c \
	env/env_special.c \
	env/env_sync.c

LEXER_SRC = lexer/lexer.c \
	lexer/char_utils.c \
	lexer/env_utils.c \
	lexer/error_utils.c \
	lexer/operator_utils.c \
	lexer/quote_utils.c \
	lexer/token_utils.c \
	lexer/word_utils.c

PARSER_SRC = parser/parser_core.c \
	parser/parser_cmd.c \
	parser/parser_memory.c \
	parser/parser_utils.c \
	parser/parser_args.c \
	parser/parser_cmd_utils.c

EXECUTOR_SRC = executor/exec_commands.c \
	executor/handle_process.c \
	executor/path_finder.c \
	executor/redir.c

SIGNALS_SRC = signals/signals.c \
	signals/signals_core.c \
	signals/signals_handlers.c \
	signals/signals_utils.c

SHELL_SRC = shell/shell_ctx.c

UTILS_SRC = utils/utils.c

# Regroupement de toutes les sources
SRCS = $(MAIN_SRC) $(BUILTINS_SRC) $(ENV_SRC) $(LEXER_SRC) \
	$(PARSER_SRC) $(EXECUTOR_SRC) $(SIGNALS_SRC) $(SHELL_SRC) $(UTILS_SRC)

# Objets
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# Règles
all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT_DIR)/libft.a $(OBJS)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo "\033[32mCompilation terminée avec succès !\033[0m"

# Création des dossiers objets
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/builtins
	@mkdir -p $(OBJ_DIR)/env
	@mkdir -p $(OBJ_DIR)/lexer
	@mkdir -p $(OBJ_DIR)/parser
	@mkdir -p $(OBJ_DIR)/executor
	@mkdir -p $(OBJ_DIR)/signals
	@mkdir -p $(OBJ_DIR)/shell
	@mkdir -p $(OBJ_DIR)/utils

# Compilation de la libft
$(LIBFT_DIR)/libft.a:
	@$(MAKE) -C $(LIBFT_DIR)

# Règle de compilation générique avec dépendances des headers
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@echo "\033[34mCompilation de $<...\033[0m"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "\033[33mNettoyage des fichiers objets effectué\033[0m"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "\033[33mNettoyage complet effectué\033[0m"

re: fclean all

.PHONY: all clean fclean re
