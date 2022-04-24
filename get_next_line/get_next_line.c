#include  "get_next_line.h"

//this function takes also BUFFER_SIZE as a parameter, that will be set at compile time. 

char	*get_next_line(int fd)
{
	static t_list	*stash;
	char			*line;

	/*static t_list	*stash = 0;*/
//what values these parameters can have but don't want to deal with 
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
	return (NULL);
	line = 0;
	//1. read from fd and add to linked list 
	read_and_stash(fd, &stash); //want to retrive the numb of characters read 
	if (stash == 0)
		return (NULL);
	//2. extract from stash to line
	extract_line(stash, &line);
	//3. clean the stash
	clean_stash(&stash);
	if (line[0] == '\0') //finish reading the whole file 
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}
	
	/*use read() to add characters to the stash*/
	void read_and_stash(int fd, t_list **stash)
	{
		char *buff;
		int readed;

		readed = 1;
		while(!found_new_line(*stash) && readed != 0)
		{
			buff = malloc(sizeof(char) * (BUFFER_SIZE +1));
			if (!buff)
				return;
			readed = (int)read(fd, buff, BUFFER_SIZE); //casting to int cause read returns a size_t
			if ((*stash == NULL && readed == 0) || readed == -1)
			{
			free(buff);
			return ;
			}
			buff[readed] = '\0'; //here i want to close this string that has read, because read() copies a number of characters but it doesn't care if there is a \0 at the end or not
			add_to_stash(stash, buff, readed);
			free(buff);
		}
	}	

/* Adds the content of the buffer to the end of the stash */

void	add_to_stash(t_list **stash, char *buff, int readed)
{
	int		i;
	t_list	*last;
	t_list	*new_node;
	
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = 0;
	new_node->content = malloc(sizeof(char) * (readed + 1));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buff[i] && i < readed) //that allows me to read only the characters that have been read 
	{
		new_node->content[i] = buff[i]; //copy into the new node everything in the buffer that has been read
		i++;
	}
	new_node->content[i] = '\0'; //close it 
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last = ft_lst_get_last(*stash);
	last->next = new_node;
}


/* Extracts all characters from the stash and stores them in out line.
 * stopping after the first \n it encounters */

void	extract_line(t_list *stash, char **line)
{
	int	i;
	int	j;

	if (stash == 0)
		return ;
	generate_line(line, stash); //allocate memory large enought to get this line
	if (*line == 0)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

/* After extracting the line that was read, we don't need those characters
 * anymore. This function clears the stash so only the characters that have
 * not been returned at the end of get_next_line remain in our static stash. */

void	clean_stash(t_list **stash)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list)); //malloc a space for the struct 
	if (stash == NULL || clean_node == NULL)
		return ;
	clean_node->next = 0;
	last = ft_lst_get_last(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n') //while the content of the last element exist and is not a \n
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(sizeof(char) * ((ft_strlen(last->content) - i) + 1)); //allocate memory for my content. ft_strlen: i want the lenght of all characters that are stored in the last element of my string(stash). -i: - number of characters that we just counted there which are the one that i've alredy returned. +1 for the /0
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++]; //copy in my clean_node everything that is in the content of the last node of my stash and that has not been returned and that is what i want to keep
	clean_node->content[j] = '\0';
	free_stash(*stash);
	*stash = clean_node; //once it's free, the initial pointer of my stash will be free, so i can make it point to my clean_node and then my stash will point to this new cleaned item where'll be only items not returned yet.
}