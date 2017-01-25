/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemarch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 12:05:16 by elemarch          #+#    #+#             */
/*   Updated: 2014/12/11 14:45:27 by elemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"
#include "libft.h"

char			*gnl_find_bn(char *str, char **save)
{
	char		*bn;

	if ((bn = ft_strchr(str, '\n')))
	{
		if (*save)
			free(*save);
		*save = ft_strdup(bn + 1);
		*bn = '\0';
	}
	return (bn);
}

int				gnl_loop(int fd, char **bn, char **save, char **line)
{
	int			ret;
	char		buff[BUFF_SIZE + 1];

	while (ft_bzero(buff, BUFF_SIZE + 1), 1)
	{
		ret = read(fd, buff, BUFF_SIZE);
		if (ret < 0)
			return (-1);
		if (ret == 0)
			return (0);
		*bn = gnl_find_bn(buff, save);
		*line = ft_strfjoin(*line, buff);
		if (*bn)
			return (1);
	}
}

int				get_next_line(int const fd, char **line)
{
	int			ret;
	char		*bn;
	static char	*save;
	char		*temp;

	if (fd < 0 || !line)
		return (-1);
	*line = NULL;
	if (save)
	{
		temp = ft_strdup(save);
		if (!(bn = gnl_find_bn(temp, &save)))
			save = NULL;
		*line = ft_strdup(temp);
	}
	if (!save)
	{
		bn = NULL;
		ret = gnl_loop(fd, &bn, &save, line);
		if (ret)
			return (ret);
	}
	if (save)
		return (1);
	return (0);
}
