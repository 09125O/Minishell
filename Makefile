NAME = minishell
TEST = lexer_test

SRCS = lexer.c \
       lexer_utils.c \
       token_creator.c \
       token_list_utils.c \
       word_extractor.c \
       quote_handler.c \
       error_handler.c \
       token_processor.c

TEST_SRCS = lexer_test.c

OBJS = $(SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

test: $(OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(filter-out lexer_main.o, $(OBJS)) $(TEST_OBJS) -o $(TEST)
	./$(TEST)

clean:
	rm -f $(OBJS) $(TEST_OBJS)

fclean: clean
	rm -f $(NAME) $(TEST)

re: fclean all

.PHONY: all clean fclean re test
