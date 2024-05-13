/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:09:29 by pitroin           #+#    #+#             */
/*   Updated: 2024/05/13 11:56:14 by pitroin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*last_line(char **current, char **line)
{
	if (*current[0] != '\0')
	{
		*line = ft_strndup(*current, ft_strlen(*current));
		free(*current);
		*current = NULL;
	}
	else
		*line = NULL;
	return (*line);
}

char	*extract_line(char **current)
{
	char	*line_end;
	char	*new_start;
	char	*line;

	line_end = ft_strchr(*current, '\n');
	if (line_end)
	{
		line = ft_strndup(*current, ft_strlen(*current) - ft_strlen(line_end));
		new_start = ft_strndup(line_end, ft_strlen(line_end));
		free(*current);
		if (*new_start == '\0')
		{
			free(new_start);
			*current = NULL;
		}
		else
			*current = new_start;
	}
	else
		return (last_line((current), &line));
	return (line);
}

char	*read_fd(int fd, char **current, char **buff)
{
	char	*tmp;
	int		size;

	while (!ft_strchr(*current, '\n'))
	{
		size = read(fd, *buff, BUFFER_SIZE);
		if (size < 0 || (size == 0 && (!(*current) || *current[0] == '\0')))
		{
			free(*current);
			*current = NULL;
			return (NULL);
		}
		if (size == 0)
			break ;
		(*buff)[size] = '\0';
		tmp = ft_strjoin(*current, *buff);
		free(*current);
		*current = tmp;
	}
	return (extract_line(current));
}

char	*get_next_line(int fd)
{
	static char	*current;
	char		*buff;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	if (!current)
		current = ft_strndup("", 0);
	result = read_fd(fd, &current, &buff);
	free(buff);
	buff = NULL;
	return (result);
}

// int	main(void)
// {
// int		fd;
// char	*line;

// fd = open ("text.txt", O_RDONLY);
// while ((line = get_next_line(fd)) != NULL)
// {
// 	printf("%s", line);
// 	free(line);
// }
// printf("%s", line);
// // free(line);
// close (fd);
// return (0);
// }
