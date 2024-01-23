/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:52:10 by mjeannin          #+#    #+#             */
/*   Updated: 2024/01/23 15:37:48 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
	{
		free_stash(stash);
		stash = NULL;
		return (NULL);
	}
	line = NULL;
	read_and_stash(fd, &stash);
	if (stash == NULL)
		return (NULL);
	extract_line(stash, &line);
	clean_stash(&stash);
	if (line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

/* Uses read() to add characters to the stash */

void	read_and_stash(int fd, t_list **stash)
{
	char	*buf;
	int		readed;

	readed = 1;
	while (!found_newline(*stash) && readed != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
		{
			free_stash(*stash);
			*stash = NULL;
			return ;
		}
		readed = (int)read(fd, buf, BUFFER_SIZE);
		if ((*stash == NULL && readed == 0) || readed == -1)
		{
			free(buf);
			free_stash(*stash);
			*stash = NULL;
			return ;
		}
		buf[readed] = '\0';
		add_to_stash(stash, buf, readed);
		free(buf);
	}
}

/* Adds the cont of our buffer to the end of our stash */

void	add_to_stash(t_list **stash, char *buf, int readed)
{
	int		i;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->cont = malloc(sizeof(char) * (readed + 1));
	if (!new_node->cont)
	{
		free(new_node);
		return ;
	}
	i = -1;
	while (++i < readed && buf[i])
		new_node->cont[i] = buf[i];
	new_node->cont[i] = '\0';
	new_node->next = NULL;
	if (*stash)
		ft_lst_get_last(*stash)->next = new_node;
	else
		*stash = new_node;
}

/* Extracts all characters from our stash and stores them in out line.
 * stopping after the first \n it encounters */

void	extract_line(t_list *stash, char **line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	generate_line(line, stash);
	if (*line == NULL)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->cont[i])
		{
			if (stash->cont[i] == '\n')
			{
				(*line)[j++] = stash->cont[i];
				break ;
			}
			(*line)[j++] = stash->cont[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

void	clean_stash(t_list **stash)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list));
	if (stash == NULL || clean_node == NULL)
		return ;
	clean_node->next = NULL;
	last = ft_lst_get_last(*stash);
	i = 0;
	while (last->cont[i] && last->cont[i] != '\n')
		i++;
	if (last->cont && last->cont[i] == '\n')
		i++;
	clean_node->cont = malloc(sizeof(char) * ((ft_strlen(last->cont) - i) + 1));
	if (clean_node->cont == NULL)
		return ;
	j = 0;
	while (last->cont[i])
		clean_node->cont[j++] = last->cont[i++];
	clean_node->cont[j] = '\0';
	free_stash(*stash);
	*stash = clean_node;
}
