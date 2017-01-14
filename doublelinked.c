#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

typedef struct v_list
{
	char *data;
	char piece;
	struct v_list *prev;
	struct v_list *next;
}x_list;

typedef struct head
{
	struct v_list *first_element;
	int lenght;
}head;

x_list *new_node(char *data)
{
	x_list *elem;

	elem = NULL;
	elem = (x_list*)malloc(sizeof(x_list));
	elem->data = data;
	elem->next = NULL;
	elem->prev = NULL;

	return (elem);
}

x_list *add_node(x_list *elem, char *data, head *master)
{
	x_list *new;

	if (elem)
	{
		new = new_node(data);
		new->next = elem;
		elem->prev = new;
		master->lenght += 1;
	}
	else
	{
		new = new_node(data);
		master->first_element = new;
		master->lenght += 1;
	}
	return (new);
}

void print_list(x_list *elem, head sentinel)
{
	while (elem)
	{
		ft_putstr(elem->data);
		ft_putstr("\n\n");
		elem = elem->prev;
	}
}

char *cut_piece(char *buf)
{
	int i;
	int j;
	unsigned int start;
	size_t len;

	i = 0;
	j = 0;
	start = 0;
	while (buf[start] != '#')
		start++;
	i = start;
	while (buf[i] && j < 4)
	{
		if (buf[i] == '#')
			j++;
		i++;
	}
	len = ((size_t)i - (size_t)start);
	return (ft_strsub(buf, start, len));
}

x_list *read_and_copy(char *argv, head *sentinel, x_list *elem)
{
	int fd;
	int ret;
	char buf[21];

	if((fd = open(argv, O_RDONLY)) != -1)
	{
		while ((ret = read(fd, buf, 21)))
		{
			if (ft_checksquare(buf) == 1 && ft_checkpiece(buf) == 1)
			{
				elem = add_node(elem, cut_piece(buf), sentinel);
				elem->piece = (sentinel->lenght + 64);
			}
			else
			{
				ft_putstr("error");
				return (NULL);
			}
		}
	}
	close(fd);
	return (sentinel->first_element);
}

void hashtag_to_alpha(x_list *elem)
{
	int i = 0;
	while (elem)
	{
		while(elem->data[i])
		{
			if (elem->data[i] == '#')
			{
				elem->data[i] = elem->piece;
				//ft_putchar(elem->piece);
				//ft_putchar('\n');
			}
			i++;
		}
		i = 0;
		elem = elem->prev;
	}
}



int main(int argc, char **argv)
{
	x_list *elem;
	head sentinel;
	elem = NULL;

	elem = read_and_copy(argv[1], &sentinel, elem);
	hashtag_to_alpha(elem);
	print_list(elem, sentinel);
}
