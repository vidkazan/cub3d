#include "get_next_line.h"

char	*ft_for_ost(char **ost, char **line)
{
	char	*srch;
	char	*tmp;

	srch = NULL;
	if (*ost)
	{
		srch = ft_strchr(*ost, '\n');
		if (srch)
		{
			srch[0] = '\0';
			tmp = ft_strdup(*ost);
			srch++;
			ft_strcpy(*ost, srch);
		}
		else
		{
			tmp = ft_strdup(*ost);
			free(*ost);
			*ost = NULL;
		}
		free(*line);
		*line = tmp;
	}
	return (srch);
}

void	ft_for_buf(char *buf, char **line, char **srch, char **ost)
{
	char	*tmp;

	*srch = ft_strchr(buf, '\n');
	if (*srch)
	{
		(*srch)[0] = '\0';
		tmp = ft_strjoin(*line, buf);
		(*srch)++;
		*ost = ft_strdup(*srch);
	}
	else
		tmp = ft_strjoin(*line, buf);
	free(*line);
	*line = tmp;
}

int	get_next_line(int fd, char **line)
{
	char		buf[10000];
	int			byte;
	static char	*ost;
	char		*srch;

	if (!line || fd < 0 || read(fd, 0, 0))
		return (-1);
	*line = ft_strdup("");
	byte = 1;
	srch = ft_for_ost(&ost, line);
	if (srch)
		return (1);
	while (byte != 0 && !srch)
	{
		byte = read(fd, &buf, 1);
		buf[byte] = '\0';
		ft_for_buf(buf, line, &srch, &ost);
	}
	if (srch)
		return (1);
	return (0);
}
