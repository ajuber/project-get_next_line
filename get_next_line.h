/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 13:35:51 by ajubert           #+#    #+#             */
/*   Updated: 2015/12/23 13:11:39 by ajubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include<sys/types.h>
# include<sys/uio.h>
# include<unistd.h>
# include<stdlib.h>
# include<string.h>
# include <fcntl.h>
# include"libft.h"

#define BUFF_SIZE 10

int		get_next_line(int const fd, char **line);

#endif
