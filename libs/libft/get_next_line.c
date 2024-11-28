/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:18:52 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/28 14:57:15 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*leftover[OPEN_MAX];
	char		*next_line;
	char		*temp;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	leftover[fd] = ft_read_from_file(fd, leftover[fd]);
	if (!leftover[fd])
	{
		free(leftover[fd]);
		return (NULL);
	}
	next_line = ft_find_line(leftover[fd]);
	temp = leftover[fd];
	leftover[fd] = ft_find_leftover(leftover[fd]);
	if (leftover[fd] == NULL)
		free(leftover[fd]);
	free(temp);
	return (next_line);
}

char	*ft_read_from_file(int fd, char *leftover)
{
	char		*buffer;
	long long	bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	gnl_memset(buffer, 0, BUFFER_SIZE);
	while (!gnl_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(leftover);
			free(buffer);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		else
			buffer[bytes_read] = '\0';
		leftover = gnl_strjoin(leftover, buffer);
	}
	free(buffer);
	return (leftover);
}

char	*ft_find_line(char *leftover)
{
	char	*str;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (leftover[i] != '\n' && leftover[i])
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	while (i > j)
	{
		str[j] = leftover[j];
		j++;
	}
	if (leftover[j] == '\n')
	{
		str[j] = leftover[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_find_leftover(char *leftover)
{
	while (*leftover && *leftover != '\n')
		leftover++;
	if (*leftover == '\n')
		leftover++;
	if (*leftover == '\0')
		return (NULL);
	return (gnl_strdup(leftover));
}
//#include <fcntl.h> // for open
//#include <unistd.h> // for close
//#include <stdio.h> // for printf
//#include <stdlib.h> // for free

//// Declare get_next_line prototype
//char *get_next_line(int fd);

//// 
//int main(void)
//{
//    int fd;
//    char *line;

//    // Open the file in read-only mode
//    //fd = open("test.txt", O_RDONLY);
//    fd = 1;
//    if (fd == -1)
//    {
//        perror("Error opening file");
//        return 1;
//    }

//    // Read lines from the file using get_next_line
//    while ((line = get_next_line(fd)) != NULL)
//    {
//        printf("%s", line);
//        free(line); // Don't forget to free the line after processing it
//    }

//    // Close the file
//    if (close(fd) == -1)
//    {
//        perror("Error closing file");
//        return 1;
//    }

//    return 0;
//}