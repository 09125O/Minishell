# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#              #
#    Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                              COLOR SETTING                                   #
# **************************************************************************** #

COLOR_RESET = \033[0m
PINKB = \033[1;95m
REDB = \033[1;91m
ROSEB = \033[1;38;5;225m
BLUEB = \033[1;34m
GREENB = \033[1;38;5;85m
PURPLEB = \033[1;38;5;55m

# **************************************************************************** #
#                                 MAIN                                         #
# **************************************************************************** #

NAME = libft.a

# **************************************************************************** #
#                               DIRECTORIES                                    #
# **************************************************************************** #

HEADER = -I includes/
SRCS_DIR = srcs/
OBJS_DIR = objs/

# **************************************************************************** #
#                         SRCS, OBJS, DEPENTDENCIES                            #
# **************************************************************************** #

ARRAY_DIR  = $(SRCS_DIR)ft_array/ft_split.c\
             $(SRCS_DIR)ft_array/ft_strchr.c\
             $(SRCS_DIR)ft_array//ft_strdup.c\
             $(SRCS_DIR)ft_array//ft_striteri.c\
             $(SRCS_DIR)ft_array/ft_strjoin.c\
             $(SRCS_DIR)ft_array/ft_strlcat.c\
             $(SRCS_DIR)ft_array/ft_strlcpy.c\
             $(SRCS_DIR)ft_array/ft_strlen.c\
             $(SRCS_DIR)ft_array/ft_strmapi.c\
             $(SRCS_DIR)ft_array/ft_strncmp.c\
             $(SRCS_DIR)ft_array/ft_strlcpy.c\
             $(SRCS_DIR)ft_array//ft_strnstr.c\
             $(SRCS_DIR)ft_array/ft_strrchr.c\
             $(SRCS_DIR)ft_array/ft_strtrim.c\
             $(SRCS_DIR)ft_array/ft_substr.c\
			 $(SRCS_DIR)ft_array/ft_strcmp.c\
			 $(SRCS_DIR)ft_array/ft_strndup.c

ARRAYS_DIR  = $(SRCS_DIR)ft_arrays/arrs_free.c\
			  $(SRCS_DIR)ft_arrays/ft_arrsdup.c\
			  $(SRCS_DIR)ft_arrays/ft_arrslen.c

IS_DIR     = $(SRCS_DIR)ft_is/ft_isalnum.c\
             $(SRCS_DIR)ft_is/ft_isalpha.c\
             $(SRCS_DIR)ft_is/ft_isascii.c\
             $(SRCS_DIR)ft_is/ft_isdigit.c\
             $(SRCS_DIR)ft_is/ft_isprint.c 

LST_DIR    = $(SRCS_DIR)ft_lst/ft_lstadd_back.c\
             $(SRCS_DIR)ft_lst/ft_lstadd_front.c\
             $(SRCS_DIR)ft_lst/ft_lstclear.c\
             $(SRCS_DIR)ft_lst/ft_lstdelone.c\
             $(SRCS_DIR)ft_lst/ft_lstiter.c\
             $(SRCS_DIR)ft_lst/ft_lstlast.c\
             $(SRCS_DIR)ft_lst/ft_lstmap.c\
             $(SRCS_DIR)ft_lst/ft_lstnew.c\
             $(SRCS_DIR)ft_lst/ft_lstsize.c 
             
MEM_DIR    = $(SRCS_DIR)ft_mem/ft_bzero.c\
             $(SRCS_DIR)ft_mem/ft_calloc.c\
             $(SRCS_DIR)ft_mem/ft_memchr.c\
             $(SRCS_DIR)ft_mem/ft_memcmp.c\
             $(SRCS_DIR)ft_mem/ft_memmove.c\
             $(SRCS_DIR)ft_mem/ft_memset.c 

PUTFD_DIR  = $(SRCS_DIR)ft_putfd/ft_putchar_fd.c\
             $(SRCS_DIR)ft_putfd/ft_putendl_fd.c\
             $(SRCS_DIR)ft_putfd/ft_putnbr_fd.c\
             $(SRCS_DIR)ft_putfd/ft_putstr_fd.c 

TO_DIR     = $(SRCS_DIR)ft_to/ft_atoi.c\
             $(SRCS_DIR)ft_to/ft_itoa.c\
             $(SRCS_DIR)ft_to/ft_tolower.c\
             $(SRCS_DIR)ft_to/ft_toupper.c\
			 $(SRCS_DIR)ft_to/ft_atol.c

PRINTF_DIR = $(SRCS_DIR)ft_printf/ft_printf.c\
             $(SRCS_DIR)ft_printf/ft_put_char.c\
             $(SRCS_DIR)ft_printf/ft_put_hex.c\
             $(SRCS_DIR)ft_printf/ft_put_int.c\
             $(SRCS_DIR)ft_printf/ft_put_ptr.c\
             $(SRCS_DIR)ft_printf/ft_put_str.c\
             $(SRCS_DIR)ft_printf/ft_put_unsign.c

GNL_DIR    = $(SRCS_DIR)get_next_line/get_next_line.c

SRCS       = $(ARRAY_DIR) $(ARRAYS_DIR) $(IS_DIR) $(LST_DIR) $(MEM_DIR) $(PUTFD_DIR) $(TO_DIR) $(PRINTF_DIR) $(GNL_DIR)
OBJS       = $(patsubst $(SRCS_DIR)%.c,$(OBJS_DIR)%.o,$(SRCS))

# **************************************************************************** #
#                            COMPILER & FLAGS                                  #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
AR = ar rcs
RM = rm -rf

# **************************************************************************** #
#                             BUILD COMMANDS                                   #
# **************************************************************************** #

all: $(NAME)
	@echo "$(PURPLEB)✨COMPILATION DONE!$(NAME) CREATED✨$(COLOR_RESET)"

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)
	@echo "$(BLUEB)---COMPILING--- $(NAME)$(COLOR_RESET)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

# **************************************************************************** #
#                             CLEAN COMMANDS                                   #
# **************************************************************************** #

clean:
	@$(RM) $(OBJS_DIR)
	@echo "$(BLUEB)🫧CLEAN DONE! [$(OBJS)] DELETED🫧$(COLOR_RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(BLUEB)🫧🫧FCLEAN DONE! [$(NAME)] REMOVED🫧🫧$(COLOR_RESET)"

re: fclean all
	@echo "$(REDB)RE DONE$(COLOR_RESET)"

.PHONY: all clean fclean re
