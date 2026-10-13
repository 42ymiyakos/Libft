NAME	= run_test
LIBFT	= ../libft.a
SRCS	= main.c utils.c test_strlen.c test_is.c test_to.c test_strchr.c \
		  test_strrchr.c test_strncmp.c test_strlcpy.c test_strlcat.c \
		  test_strnstr.c test_atoi.c test_calloc.c test_strdup.c \
		  test_memset.c test_bzero.c test_memcpy.c test_memmove.c \
		  test_memchr.c test_memcmp.c
CC		= cc
CFLAGS	= -Wall -Wextra -g -fsanitize=address
INCS	= -I. -I..
LIBS	= -lbsd

.PHONY: all run clean $(LIBFT)
all: $(NAME)

$(NAME): $(SRCS) test.h $(LIBFT)
	$(CC) $(CFLAGS) $(INCS) $(SRCS) $(LIBFT) $(LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C ..

run: all
	./$(NAME)

clean:
	rm -f $(NAME)
