/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samrazaf <samrazaf@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 15:17:46 by samrazaf          #+#    #+#             */
/*   Updated: 2026/03/13 10:26:56 by samrazaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
# include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int	fd;
	char *line;

	fd = open("text.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);

	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	//printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));
	close(fd);
	return (0);
}
