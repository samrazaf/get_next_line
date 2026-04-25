/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samrazaf <samrazaf@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 15:15:51 by samrazaf          #+#    #+#             */
/*   Updated: 2026/04/02 15:58:58 by samrazaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, int search, char *buffer, char *new_str)
{
	ssize_t	read_buf;
	char	*temp;

	while (!new_str || !ft_strchr(new_str, search))
	{
		read_buf = read(fd, buffer, BUFFER_SIZE);
		if (read_buf == -1)
		{
			free(new_str);
			return (NULL);
		}
		else if (read_buf == 0)
			break ;
		buffer[read_buf] = '\0';
		if (!new_str)
			new_str = ft_strdup(buffer);
		else
		{
			temp = new_str;
			new_str = ft_strjoin(new_str, buffer);
			free(temp);
		}
	}
	return (new_str);
}

static char	*extract_new_line(char *new_str, int search)
{
	int	i;

	i = 0;
	while (new_str[i] && new_str[i] != search)
		i ++;
	new_str = ft_substr(new_str, 0, i + 1);
	return (new_str);
}

static char	*update_last_line(char *last_str, int search)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = ft_strlen(last_str);
	while (last_str[i] && last_str[i] != search)
		i ++;
	if (last_str[i] == '\0' || last_str[i + 1] == '\0')
	{
		free(last_str);
		return (NULL);
	}
	new_str = ft_substr(last_str, (i + 1), (j - i + 1));
	free(last_str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	char		search;
	char		*buffer;
	char		*str_return;
	static char	*new_str;

	search = '\n';
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if ((fd < 0 && BUFFER_SIZE <= 0) || !buffer)
		return (NULL);
	new_str = read_line(fd, search, buffer, new_str);
	free(buffer);
	if (new_str && ft_strchr(new_str, search))
	{
		str_return = extract_new_line(new_str, search);
		new_str = update_last_line(new_str, search);
		return (str_return);
	}
	else if (new_str && *new_str)
	{
		str_return = ft_strdup(new_str);
		free(new_str);
		new_str = NULL;
		return (str_return);
	}
	return (0);
}
