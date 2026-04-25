/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samrazaf <samrazaf@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:13:23 by samrazaf          #+#    #+#             */
/*   Updated: 2026/04/02 16:20:24 by samrazaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i ++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s1) + ft_strlen(s2);
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	ptr = malloc(sizeof(char) * (j + 1));
	j = 0;
	if (ptr == NULL)
		return (NULL);
	while (s1 && s1[i])
	{
		ptr[i] = s1[i];
		i ++;
	}
	while (s2 && s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	j = 0;
	while (j <= i)
	{
		if ((unsigned char)s[j] == (unsigned char)c)
			return ((char *)&s[j]);
		j ++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[j]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	i;
	size_t	n;

	n = 0;
	i = ft_strlen(s);
	ptr = malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (NULL);
	while (n < i)
	{
		ptr[n] = s[n];
		n ++;
	}
	ptr[n] = '\0';
	return (ptr);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	a;
	char	*ptr;

	a = ft_strlen(s);
	if (!s)
		return (NULL);
	if (a <= (size_t)start)
	{
		ptr = malloc(1);
		if (!ptr)
			return (NULL);
		ptr[0] = '\0';
		return (ptr);
	}
	if (len > a - start)
		len = a - start;
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
		ptr[i++] = s[start++];
	ptr[i] = '\0';
	return (ptr);
}
