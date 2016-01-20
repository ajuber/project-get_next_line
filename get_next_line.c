/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 15:06:11 by ajubert           #+#    #+#             */
/*   Updated: 2016/01/20 16:58:47 by ajubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		extractbuffer(char **str1, int fd)
{
	char	str[BUFF_SIZE + 1];
	int		strsize;
	int		i;
	char	*tmp;

	i = 0;
	strsize = read(fd, str, BUFF_SIZE);
	if (strsize < 0)
		return (-1);
	if (strsize == 0)
		return (0);
	str[strsize] = '\0';
	tmp = &str1[0][0];
	str1[0] = ft_strjoin(tmp, str);
	ft_strdel(&tmp);
//	str1[0] = ft_strjoin(str1[0], str);
	strsize = ft_strlen(str1[0]);
	return (strsize);
}

int		get_previous_str(char **str, char **line)
{
	int i;
	int size[2]; //size[1] = strsize

	i = 0;
	while (str[0][i] && str[0][i] != '\n')
		i++;
	if (str[0][i] == '\n')
	{
		i++;
		size[0] = ft_strlen(&str[0][i]);
		ft_memmove(str[0], &str[0][i], size[0]);
		size[1] = ft_strlen(str[0]);
		ft_bzero(&str[0][size[0]], size[1] - size[0]);
	}
	else
		str[0] = ft_strdup("\0");
	if (str[0][0] == '\n')
	{
		line[0] = ft_strdup("\0");
		return (1);
	}
	return (0);
}

int		next_calc(int size, char **line, char **str, int *test)
{
	int i;

	if (size == 0)
		size = ft_strlen(str[0]);
	line[0] = ft_strdup(str[0]);
	i = 0;
	while (line[0][i] && line[0][i] != '\n')
		i++;
	while (line[0][i])
	{
		line[0][i] = '\0';
		i++;
		*test = 1;
	}
	return (i);
}

int		calc_get_next_line(char **str, int fd, char **line, int *fd1)
{
	int test;
	int strsize;
	int i;
	int size;

	while (1)
	{
		test = 0;
		strsize = extractbuffer(str, fd);
		if (strsize == -1)
			return (-1);
		if (str[0][0] == 0)
		{
			line[0] = ft_strdup("\0");
			return (0);
		}
		size = strsize;
		i = next_calc(size, line, str, &test);
		*fd1 = fd;
		if ((line[0][i] == '\0' && i < BUFF_SIZE) || test == 1 || strsize == 0)
			return (1);
	}
}

int		get_next_line(int const fd, char **line)
{
	static char		**str = 0;
	static int		fd1 = -1;
	int				test;

	if (fd < 0 || line == NULL || BUFF_SIZE <= 0)
		return (-1);
	if (fd1 != fd)
	{
		if (!(str = (char **)malloc(sizeof(char *) * 1)))
			return (-1);
		str[0] = ft_strdup("\0");
	}
	else if (get_previous_str(str, line))
		return (1);
	test = calc_get_next_line(str, fd, line, &fd1);
	if (test == 1)
		return (1);
	if (test == 0)
		return (0);
	return (-1);
}
