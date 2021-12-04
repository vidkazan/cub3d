/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcody <fcody@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:34:08 by fcody             #+#    #+#             */
/*   Updated: 2021/12/04 14:34:08 by fcody            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen_line2(char **str)
{
	int	line;

	line = 0;
	while (str[line])
		line++;
	return (line);
}

int	ft_error(int code)
{
	write(2, "Error\n", 6);
	exit (1);
}

int	game_close(void)
{
	exit(0);
}

float	ft_abs(float a)
{
	if (a < 0)
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
