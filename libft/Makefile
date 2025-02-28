# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 16:10:21 by douzgane          #+#    #+#              #
#    Updated: 2025/02/26 20:40:17 by douzgane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I inc

# Dossiers
SRC_DIR = src/
OBJ_DIR = obj/

AR = ar rcs
RM = rm -rf

# Sources
LIBFT_DIR = libft/
LIBFT = \
	isalpha \
	isdigit \
	isdigit_str \
	isalnum \
	isascii \
	isprint \
	strlen \
	memset \
	bzero \
	memcpy \
	memmove \
	strcmp \
	strlcpy \
	strlcat \
	toupper \
	tolower \
	strchr \
	strrchr \
	strncmp \
	memchr \
	memcmp \
	strnstr \
	atoi \
	calloc \
	strdup \
	substr \
	strjoin \
	strtrim \
	split \
	itoa \
	strmapi \
	striteri \
	putchar_fd \
	putstr_fd \
	putendl_fd \
	putnbr_fd \
	lstnew \
	lstadd_front \
	lstsize \
	lstlast \
	lstadd_back \
	lstdelone \
	lstclear \
	lstiter \
	lstmap

PRINTF_DIR = printf/
PRINTF = \
	ft_printf \
	ft_printf_utils

GNL_DIR = gnl/
GNL = \
	get_next_line \
	get_next_line_utils

FILES = \
	$(addprefix $(LIBFT_DIR)ft_, $(LIBFT)) \
	$(addprefix $(PRINTF_DIR), $(PRINTF)) \
	$(addprefix $(GNL_DIR), $(GNL))

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

# Règles
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(AR) $(NAME) $(OBJS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)$(LIBFT_DIR) \
		$(OBJ_DIR)$(PRINTF_DIR) \
		$(OBJ_DIR)$(GNL_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
