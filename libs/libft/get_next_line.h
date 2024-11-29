/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:34:18 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/29 16:48:01 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

void	*gnl_memset(void *b, int c, size_t len);
char	*ft_find_leftover(char *leftover);
int		gnl_strlen(const char *str);
void	*ft_memset(void *b, int c, size_t len);
char	*gnl_strjoin(char const *s1, char const *s2);
char	*ft_read_from_file(int fd, char *leftover);
char	*ft_find_line(char *next_line);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strdup(const char *s1);
char	*get_next_line(int fd);

#endif