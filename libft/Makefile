#######################################################
## ARGUMENTS

NAME		=	libft.a
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
HEADER		=	-Iinc

SRC_DIR		=	src/
OBJ_DIR		=	obj/

AR			=	ar rcs
RM			=	rm -rf

#######################################################
## SRCS & OBJS

LIBFT_DIR	=	libft/
LIBFT		= \
			isalpha \
			isdigit \
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
			lstmap \

PRINTF_DIR	=	printf/
PRINTF		= \
			ft_printf \
			ft_printf_utils \

GNL_DIR		=	gnl/
GNL			= \
			get_next_line \
			get_next_line_utils \

FILES		= \
			$(addprefix $(LIBFT_DIR)ft_, $(LIBFT)) \
			$(addprefix $(PRINTF_DIR), $(PRINTF)) \
			$(addprefix $(GNL_DIR), $(GNL)) \

SRCS	=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

#######################################################
## RULES

all : $(NAME)

$(NAME) : $(OBJS) Makefile
		$(AR) $(NAME) $(OBJS)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
		$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR) \
		$(OBJ_DIR)$(LIBFT_DIR) \
		$(OBJ_DIR)$(GNL_DIR) \
		$(OBJ_DIR)$(PRINTF_DIR) \

clean :
		$(RM) $(OBJ_DIR)

fclean : clean
		$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
