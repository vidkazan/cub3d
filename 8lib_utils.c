#include "cub3d.h"

int	ft_strlen_line2(char **str)
{
	int line = 0;
	while (str[line])
		line++;
	return (line);
}

int	ft_error(int code)
{
	write(2, "Error\n",6);
	exit (1);
}

int	game_close(void)
{
	exit(0);
}

float	ft_abs(float a)
{
	if(a < 0)
		return (-a);
	return (a);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*buf;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		buf = *lst;
		while (buf->next != NULL)
			buf = buf->next;
		buf->next = new;
	}
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->content = content;
	new->next = NULL;
	return (new);
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	char			*buf;
	unsigned long	i;

	i = 0;
	buf = malloc(count * size);
	if (!buf)
		return (NULL);
	else
	{
		while (i < size * count)
		{
			buf[i] = 0;
			i++;
		}
	}
	return (buf);
}

int	ft_strlen_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr || !arr[0])
		return (0);
	while (arr[i])
		i++;
	return (i);
}

char	**ft_arrdup(char **arr)
{
	char	**arr_dup;
	int		i;
	int		arr_len;

	if (!arr || !arr[0])
		return (NULL);
	i = -1;
	arr_len = ft_strlen_arr(arr);
	arr_dup = (char **)malloc(sizeof(char *) * (arr_len + 1));
	while (++i < arr_len)
		arr_dup[i] = ft_strdup(arr[i]);
	arr_dup[arr_len] = NULL;
	return (arr_dup);
}

void	free_arr(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	str = NULL;
}
