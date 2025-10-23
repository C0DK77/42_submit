#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	char	*line;
	char	buf;
	int		i;
	int		bytes_read;

	line = malloc(10000);
	if (!line)
		return (NULL);
	i = 0;
	while ((bytes_read = read(fd, &buf, 1)) > 0)
	{
		line[i++] = buf;
		if (buf == '\n')
			break ;
	}
	if (bytes_read <= 0 && i == 0)
	{
		free(line);
		return (NULL);
	}
	line[i] = '\0';
	return (line);
}
