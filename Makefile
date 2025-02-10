# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root <root@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 16:47:50 by root              #+#    #+#              #
#    Updated: 2025/02/10 13:18:43 by root             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
LDFLAGS = -lreadline

# Source files by directory
ENV_SRCS = env/copy.c \
			env/env_srch_rm_modif.c \
			env/env_utils.c \

EXEC_SRCS = exec/exec_commands.c \
			exec/handle_process.c \
			exec/path_finder.c \
			exec/redir.c \
			exec/main_test.c

SIGNALS_SRCS = signals/config_signals.c \
			signals/handle_sig_heredocs.c \
			signals/sig_handlers.c

UTILS_SRCS = utils/utils.c \
			utils/utils2.c \
			utils/utils3.c

BUILTINS_SRCS = builtins/cd.c \
			builtins/echo.c \
			builtins/env.c \
			builtins/error.c \
			builtins/exit.c \
			builtins/export.c \
			builtins/pwd.c \
			builtins/unset.c

SRCS = $(ENV_SRCS) $(EXEC_SRCS) $(SIGNALS_SRCS) $(UTILS_SRCS) $(BUILTINS_SRCS)

# Object files
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re