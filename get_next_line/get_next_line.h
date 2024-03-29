/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szicchie <szicchie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:59:58 by szicchie          #+#    #+#             */
/*   Updated: 2022/05/12 00:01:27 by szicchie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

typedef struct	t_list
{
	char			*content;
	struct t_list	*next;
}				t_list;

char	*get_next_line(int fd);
int 	found_new_line(t_list *stash);
t_list	*ft_lst_get_last(t_list *stash);
void	read_and_stash(int fd, t_list **stash);
void	add_to_stash(t_list **stash, char *buf, int readed);
void	extract_line(t_list *stash, char **line);
void	generate_line(char **line, t_list *stash);
void	clean_stash(t_list **stash);
int 	ft_strlen(const char *str);
void	free_stash(t_list *stash);
#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif