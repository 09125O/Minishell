# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 22:15:37 by douzgane          #+#    #+#              #
#    Updated: 2024/12/19 11:19:38 by douzgane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC		= cc
CFLAGS		= -Wall -Wextra -Werror
RM		= rm -f

# --------------------------------------------------------------------------- #
#                        GESTION DES CHEMINS DE READLINE                       #
# --------------------------------------------------------------------------- #

# Détection des chemins via pkg-config (si disponible)
READLINE_CFLAGS := $(shell pkg-config --cflags readline 2>/dev/null)
READLINE_LDFLAGS := $(shell pkg-config --libs readline 2>/dev/null)

ifeq ($(READLINE_CFLAGS),)
    ifeq ($(shell uname), Darwin)
        # Fallback pour macOS avec Homebrew (Intel ou ARM)
        CFLAGS += -I/usr/local/opt/readline/include -I/opt/homebrew/opt/readline/include
        LDFLAGS += -L/usr/local/opt/readline/lib -L/opt/homebrew/opt/readline/lib
    else
        # Fallback pour Linux
        CFLAGS += -I/usr/include/readline
        LDFLAGS += -L/usr/lib
    endif
else
    # Utilisation automatique de pkg-config
    CFLAGS += $(READLINE_CFLAGS)
    LDFLAGS += $(READLINE_LDFLAGS)
endif

LDFLAGS += -lreadline

# --------------------------------------------------------------------------- #


# Directories
SRCS_DIR	= src
OBJS_DIR	= obj
LIBFT_DIR	= libft
INC_DIR		= includes

# Sources by directory
MAIN_SRCS	= main.c \
		  init.c

EXEC_SRCS	= executor.c \
		  exec_cmd.c \
		  exec_pipeline.c \
		  exec_pipeline_utils.c \
		  exec_utils.c

EXEC_PROC_SRCS	= process.c \
		  wait.c

EXEC_PATH_SRCS	= path_resolver.c

EXEC_REDIR_SRCS	= redirect_in.c \
		  redirect_out.c \
		  heredoc.c

LEXER_SRCS	= lexer.c \
		  lexer_utils.c \
		  token_creator.c \
		  token_type.c \
		  token_list.c

PARSER_SRCS	= parser.c \
		  parser_utils.c \
		  ast_creator.c \
		  ast_utils.c \
		  var_expander.c \
		  quote_handler.c \
		  word_splitter.c

BUILT_SRCS	= echo.c \
		  cd.c \
		  pwd.c \
		  export.c \
		  export_utils.c \
		  unset.c \
		  env.c \
		  exit.c

SIGNAL_SRCS	= signals.c \
		  signal_handlers.c

ENV_UTILS	= env_getter.c \
		  env_setter.c \
		  env_delete.c

STR_UTILS	= str_array.c \
		  str_split.c \
		  str_join.c

ERROR_UTILS	= error_print.c \
		  error_handler.c

# Combine all sources with their proper paths
SRCS		= $(addprefix $(SRCS_DIR)/main/, $(MAIN_SRCS)) \
		  $(addprefix $(SRCS_DIR)/executor/, $(EXEC_SRCS)) \
		  $(addprefix $(SRCS_DIR)/executor/process/, $(EXEC_PROC_SRCS)) \
		  $(addprefix $(SRCS_DIR)/executor/path/, $(EXEC_PATH_SRCS)) \
		  $(addprefix $(SRCS_DIR)/executor/redirect/, $(EXEC_REDIR_SRCS)) \
		  $(addprefix $(SRCS_DIR)/lexer/, $(LEXER_SRCS)) \
		  $(addprefix $(SRCS_DIR)/parser/, $(PARSER_SRCS)) \
		  $(addprefix $(SRCS_DIR)/builtins/, $(BUILT_SRCS)) \
		  $(addprefix $(SRCS_DIR)/signals/, $(SIGNAL_SRCS)) \
		  $(addprefix $(SRCS_DIR)/utils/env_utils/, $(ENV_UTILS)) \
		  $(addprefix $(SRCS_DIR)/utils/str_utils/, $(STR_UTILS)) \
		  $(addprefix $(SRCS_DIR)/utils/error/, $(ERROR_UTILS))

# Objects
OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Dependencies
LIBFT		= $(LIBFT_DIR)/libft.a
DEPS		= $(OBJS:.o=.d)
INC		= -I$(INC_DIR) -I$(LIBFT_DIR)/inc
LIBS		= -L$(LIBFT_DIR) -lft -lreadline

# Rules
all:		$(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME):	$(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

clean:
	@make -C $(LIBFT_DIR) clean
	$(RM) -r $(OBJS_DIR)

fclean:		clean
	@make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re:		fclean all

-include $(DEPS)

.PHONY:		all clean fclean re
