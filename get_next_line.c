/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 15:06:11 by ajubert           #+#    #+#             */
/*   Updated: 2016/01/22 16:30:21 by ajubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		extractbuffer(char **str1, int fd)
{
	char	str[BUFF_SIZE + 1];
	int		strsize;
	char	*tmp;

	strsize = read(fd, str, BUFF_SIZE);
	if (strsize < 0)
		return (-1);
	if (strsize == 0)
		return (0);
	str[strsize] = '\0';
	tmp = &str1[0][0];
	str1[0] = ft_strjoin(tmp, str);
	free(tmp);
	strsize = ft_strlen(str1[0]);
	return (strsize);
}

void	get_previous_str(char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(str[0]);
	ft_bzero(str[0], ft_strlen(str[0]));
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (tmp[++i - 1] == '\n')
		ft_strcpy(str[0], &tmp[i]);
	free(tmp);
}

int		next_calc(char **line, char **str, int *test)
{
	int		i;
	char	*tmp;

	tmp = line[0];
	line[0] = ft_strdup(str[0]);
	free(tmp);
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

	while (1)
	{
		test = 0;
		strsize = extractbuffer(str, fd);
		if (strsize == -1)
			return (-1);
		if (str[0][0] == 0)
			return (0);
		i = next_calc(line, str, &test);
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
	line[0] = ft_strdup("\0");
	if (fd1 != fd)
	{
		if (!(str = (char **)malloc(sizeof(char *) * 1)))
			return (-1);
		str[0] = ft_strdup("\0");
	}
	test = calc_get_next_line(str, fd, line, &fd1);
	get_previous_str(str);
	if (test == 1)
		return (1);
	if (test == 0)
		return (0);
	return (-1);
}
