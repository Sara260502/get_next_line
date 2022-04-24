#include "get_next_line.h"

/* Looks for a newline character in the given linked list. */
int	found_newline(t_list *stash)
{
	int		i;
	t_list	*current;

	if (stash == NULL)
		return (0); 
	current = ft_lst_get_last(stash);//here i now that if i read 1 buff 50 times tgere isn't a /n, so i go directly on the last one
	i = 0;
	while (current->content[i])// as long as there is something in my string
	{
		if (current->content[i] == '\n')
			return (1); // found it
		i++;
	}
	return (0);
}

/* Returns a pointer to the last node in the stash */

t_list	*ft_lst_get_last(t_list *stash)
{
	t_list	*current;
	
	current = stash;
	while (current && current->next)
		current = current->next;
	return (current);
}

/* Calculates the number of chars in the current line, including the trailing
 * \n if there is one, and allocates memory accordingly. */

void	generate_line(char **line, t_list *stash)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

/* Frees the entire stash. */
void	free_stash(t_list *stash)
{
	t_list	*current;
	t_list	*next;

	current = stash;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}
