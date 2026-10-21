#ifndef TEST_H
# define TEST_H

# include "libft.h"
# include <bsd/string.h>
# include <ctype.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BUF_SIZE 32
# define CALL_LOG_SIZE 64
# define LOG_SIZE 128

// strmapi / striteri用: fの呼ばれ方の記録(i を1文字 + 受け取った文字, の繰り返し)
typedef struct s_call_log
{
	char	v[CALL_LOG_SIZE];
	size_t	len;
}	t_call_log;

// lst系用: f / delが受け取った *(int *)content を順番に並べた記録
typedef struct s_log
{
	int		v[LOG_SIZE];
	size_t	len;
}	t_log;

// utils.c
void	print_pos(const char *s, const char *p);
void	print_buf(const char *buf);
void	print_bytes(const char *s, size_t n);
int		sign(int x);
int		open_capture(int fds[2]);
ssize_t	read_capture(int fds[2], char *buf, size_t size);
void	call_log_reset(t_call_log *log);
void	call_log_record(t_call_log *log, unsigned int i, char c);
int		check_call_log(const char *name, const char *input,
			const t_call_log *log, const char *expected);

// utils_lst.c
void	log_reset(t_log *log);
void	log_push(t_log *log, int v);
void	print_ints(const int *v, size_t n);
t_list	*build_list(int *vals, size_t n);
void	free_nodes(t_list *lst);
int		check_list(const char *name, const char *label, t_list *lst,
			const int *expected, size_t n);
int		check_log(const char *name, const char *label, const t_log *log,
			const int *expected, size_t n);

int		test_ft_strlen(void);
int		test_ft_is(void);
int		test_ft_to(void);
int		test_ft_strchr(void);
int		test_ft_strrchr(void);
int		test_ft_strncmp(void);
int		test_ft_strlcpy(void);
int		test_ft_strlcat(void);
int		test_ft_strnstr(void);
int		test_ft_atoi(void);
int		test_ft_calloc(void);
int		test_ft_strdup(void);
int		test_ft_memset(void);
int		test_ft_bzero(void);
int		test_ft_memcpy(void);
int		test_ft_memmove(void);
int		test_ft_memchr(void);
int		test_ft_memcmp(void);
int		test_ft_put(void);
int		test_ft_strmapi(void);
int		test_ft_striteri(void);
int		test_ft_itoa(void);
int		test_ft_substr(void);
int		test_ft_strjoin(void);
int		test_ft_strtrim(void);
int		test_ft_split(void);
int		test_ft_lstnew(void);
int		test_ft_lstadd_front(void);
int		test_ft_lstsize(void);
int		test_ft_lstlast(void);
int		test_ft_lstadd_back(void);
int		test_ft_lstdelone(void);
int		test_ft_lstclear(void);
int		test_ft_lstiter(void);
int		test_ft_lstmap(void);

#endif
