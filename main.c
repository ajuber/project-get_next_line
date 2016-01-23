/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 13:49:51 by ajubert           #+#    #+#             */
/*   Updated: 2016/01/22 16:31:26 by ajubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int		main(int argc, char **argv)
{
	int		test;
	char	**line;
	int		fd;

	(void)argc;
	line = (char **)malloc(sizeof(char *) * 1);
	line[0] = ft_strdup("\0");
	fd = open(argv[1], O_RDONLY);
	ft_putnbr(fd);
	ft_putchar('\n');
	test = 1;
	while (test == 1)
	{
		test = get_next_line(fd, line);
		ft_putnbr(test);
		ft_putendl(line[0]);
	}
	free(line);
	return (0);
}
