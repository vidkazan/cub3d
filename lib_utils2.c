/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcody <fcody@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:34:07 by fcody             #+#    #+#             */
/*   Updated: 2021/12/04 14:34:07 by fcody            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
