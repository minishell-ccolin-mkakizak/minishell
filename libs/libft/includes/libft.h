/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:36:52 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/28 14:23:13 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct c_list
{
	int				content;
	struct c_list	*next;
	struct c_list	*prev;
}					t_c_list;

# define TRUE 1
# define FALSE 0

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
size_t				ft_strlen(const char *str);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strdup(const char *s);

char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

// ft_printf_funciton
int					ft_putchar(char c);
void				ft_putstr(char *str);
int					ft_putnbr(int n);
int					ft_putnbr_long(long long n);
int					ft_putnbr_base(unsigned long num, char *base);

int					ft_put_address(unsigned long ptr);
int					ft_printf(const char *format, ...);
int					ft_print_str(char *str);
int					ft_print_unsigned_dec(unsigned int n);
int					ft_print_lower_hex(unsigned int nbr);
int					ft_print_upper_hex(unsigned int nbr);

// push_swap_utils
t_c_list			*ft_c_lstnew(int content);
void				ft_c_push(t_c_list **src, t_c_list **dest, char stack);
void				ft_c_lstadd(t_c_list **head, t_c_list *new);
t_c_list			*ft_lstpop(t_c_list **head);
int					ft_c_lstsize(t_c_list *lst);
void				ft_rotate(t_c_list **head, char stack);
void				ft_r_rotate(t_c_list **head, char stack);
void				rotate_stack(t_c_list **src, int stack, int index);
void				ft_lstswap(t_c_list **head, char stack);
void				ft_c_lstclear(t_c_list **head);
void				ft_c_print_lst(t_c_list *head, char stack);

// args_validation
int					*args_validation(int argc, char *argv[]);
int					print_arr(int *arr, int len);
void				error(void);

// compress
int					*compress(int *arr, int len);
int					is_smaller(int a, int b);
int					is_bigger(int a, int b);
int					find_min_index(int *arr, int len);

// sort_utils
int					check_sort(t_c_list *head);
int					check_r_sort(t_c_list *head);
int					find_nbr(t_c_list *head, int nbr);
int					find_r_nbr(t_c_list *head, int nbr);
int					check_any_sort(t_c_list *head);
int					check_any_r_sort(t_c_list *head);
int					find_min(t_c_list *head);
int					find_max(t_c_list *head);
int					recon_smaller(t_c_list *head, int deli);
int					recon_larger(t_c_list *head, int deli);
void				push_all(t_c_list **src_lst, t_c_list **dest_lst,
						char dest_stack);
void				split_lsts_tw_thr(t_c_list **stack_a, t_c_list **stack_b);
int					check_either_sort(t_c_list *head, char stack);
char				get_other_stack(char c);
void				splt_lst_hlf(t_c_list **src, t_c_list **dest, char stk,
						int dlmt);

// ft_atoi_long
long				ft_atoi_long(const char *str);

// short_sort
int					sort_short(t_c_list **stack_a, t_c_list **stack_b, int len);

// sort
void				sort(t_c_list **head, int len);
int					find_sortest_path(t_c_list **src, int target_nbr);

// get_next_line
char				*get_next_line(int fd);
size_t				gnl_strlen(const char *str);
int					check_for_new_line(char *str);
char				*gnl_strjoin(char *s1, char *s2);
int					init(char *sttc_str, char **buffer, char **result);
int					clean_up(char **sttc_str, char **buffer, char **result,
						int *bytes);
char				*get_new_string(int fd, char *sttc_str);
char				*get_one_line(char *str);
char				*gnl_strdup(const char *str);

void				ft_free_all(char **str);

#endif
