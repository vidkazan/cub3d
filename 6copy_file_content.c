#include "cub3d.h"

char	**make_map(t_list **head, int size)
{
	char	**map;
	int		i;
	t_list	*tmp;

	i = -1;
	map = ft_calloc(size + 1, sizeof(char *));
	if (!map)
		ft_error(67);
	tmp = *head;
	while (tmp)
	{
		map[++i] = tmp->content;
		free(tmp);
		tmp = tmp->next;
	}
	return (map);
}

void	ft_read_map(t_data *m)
{
	char	*line;
	t_list	*head;

	line = NULL;
	head = NULL;
	while (get_next_line(m->fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	m->map = make_map(&head, ft_lstsize(head));
}
