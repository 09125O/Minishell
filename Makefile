# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#              #
#    Updated: 2025/03/09 00:15:09 by douzgane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                 NAME / MAIN                                  #
# **************************************************************************** #

NAME = minishell

# **************************************************************************** #
#                                 DIRECTORIES                                  #
# **************************************************************************** #

INCL_DIR = includes
SRCS_DIR = srcs
OBJS_DIR = objs
LIBFT_DIR = libft

CORE_DIR = core
LEXER_DIR = lexer
PARSER_DIR = parser
EXECUTOR_DIR = executor
BUILTINS_DIR = builtins
BUILDER_DIR = builder
SIGNALS_DIR = signals

CORE_FL = $(addprefix $(CORE_DIR)/, main.c init.c cleanup.c env.c)
LEXER_FL = $(addprefix $(LEXER_DIR)/, lexer.c lexer_utils.c token.c)
PARSER_FL = $(addprefix $(PARSER_DIR)/, parser.c parser_utils.c heredoc.c quotes.c quotes_utils.c expander.c env_expander.c expander_utils.c)
EXECUTOR_FL = $(addprefix $(EXECUTOR_DIR)/, executor.c process.c redirections.c pipes.c wait.c execution.c errors.c utils.c)
BUILTINS_FL = $(addprefix $(BUILTINS_DIR)/, builtins.c cd.c echo.c env.c exit.c exit_utils.c export.c export_utils.c pwd.c unset.c env_utils.c)
BUILDER_FL = $(addprefix $(BUILDER_DIR)/, builder.c args.c filename.c utils.c)
SIGNALS_FL = $(addprefix $(SIGNALS_DIR)/, handler.c)

# **************************************************************************** #
#                              SRC & OBJ FILES                                 #
# **************************************************************************** #

SRCS = $(addprefix $(SRCS_DIR)/, $(CORE_FL) $(LEXER_FL) $(PARSER_FL) $(EXECUTOR_FL) $(BUILTINS_FL) $(BUILDER_FL) $(SIGNALS_FL))
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# **************************************************************************** #
#                                 LIBRARY FILES                                #
# **************************************************************************** #

LIBFT_A = $(LIBFT_DIR)/libft.a

# **************************************************************************** #
#                            COMPILER & FLAGS                                  #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I$(INCL_DIR) -I$(LIBFT_DIR)/includes
LFLAGS = -L$(LIBFT_DIR) -lft
LDFLAGS = -lreadline
RM = rm -rf

# **************************************************************************** #
#                               BUILD COMMANDS                                 #
# **************************************************************************** #

### Build Targets ###
all: $(NAME)
	$(print_flag)

### NAME Create the executable ###
$(NAME): $(OBJS) $(LIBFT_A)
	@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME) $(LDFLAGS)
	@echo "$(GREENB)$(NAME) SUCCESSFULLY COMPILED!$(COLOR_RESET)"

### Compile object files ###
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUEB)COMPILING $< TO $@$(COLOR_RESET)"

### Create object directory ###
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)/$(CORE_DIR)
	@mkdir -p $(OBJS_DIR)/$(LEXER_DIR)
	@mkdir -p $(OBJS_DIR)/$(PARSER_DIR)
	@mkdir -p $(OBJS_DIR)/$(EXECUTOR_DIR)
	@mkdir -p $(OBJS_DIR)/$(BUILTINS_DIR)
	@mkdir -p $(OBJS_DIR)/$(BUILDER_DIR)
	@mkdir -p $(OBJS_DIR)/$(SIGNALS_DIR)

### Build the libft library ###
$(LIBFT_A):
	@make -C $(LIBFT_DIR)
	@echo "$(YELLOW_BG) $(LIBFT_DIR) CREATED$(COLOR_RESET)"

### Archive Libraries ###
archives: libft
	@mkdir -p archives
	@if [ -f $(LIBFT_A) ]; then cp $(LIBFT_A) archives/; fi
#--silent: add at the back if don't want it displayed!

### Clean up object files and directories ###
clean:
	@$(RM) $(OBJS_DIR)
	@make clean -C $(LIBFT_DIR)
	@echo "$(CYANB)CLEAN DONE! OBJS of [$(NAME)] REMOVED$(COLOR_RESET)"

### Remove all built files ###
fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo "$(CYANB)FCLEAN DONE! [$(LIBFT_A)] REMOVED$(COLOR_RESET)"

### Rebuild the project ###
re: fclean all
	@echo "$(REDB)RE DONE$(COLOR_RESET)"

# **************************************************************************** #
#                              PHONY TARGETS                                   #
# **************************************************************************** #

.PHONY: all clean fclean re libft archives

# **************************************************************************** #
#                              COLOR SETTING                                   #
# **************************************************************************** #

COLOR_RESET = \033[0m
BOLD = \033[1m
BLUE = \033[34m
BLUEB = \033[1;34m
GREEN = \033[32m
GREENB = \033[1;32m
YELLOW = \033[33m
YELLOWB = \033[1;33m
RED = \033[31m
REDB = \033[1;31m
CYAN = \033[36m
CYANB = \033[1;36m
WHITE = \033[37m
WHITEB = \033[1;37m
GRAY = \033[90m
GRAYB = \033[1;90m

GREEN_BG = \033[42m
BLUE_BG = \033[44m
YELLOW_BG = \033[43m
CYAN_BG = \033[46m

# **************************************************************************** #
#                               PRINT FLAG                                     #
# **************************************************************************** #

define print_flag
	@echo "$(BLUE)=================================================================$(COLOR_RESET)"
	@echo "$(GREENB)                      mini.OD.shell READY                      $(COLOR_RESET)"
	@echo "$(BLUE)=================================================================$(COLOR_RESET)"
endef
