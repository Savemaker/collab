#include "libft.h"

t_list	*get_true_list_with_fd(int fd, t_list **file)
{
  t_list	*tmp;

  tmp = *file;
  while (tmp)
    {
      if ((int)tmp->content_size == fd)
        return (tmp);
      tmp = tmp->next;
    }
  tmp = ft_lstnew("", fd);
  ft_lstadd(file, tmp);
  return (tmp);
}

char	*find_line(void **data)
{
  int	i;
  char	*str;
  char	*tmp;
  char ***content;

  content = (char ***)&data;
  i = 0;

  while (*(**content + i) && *(**content + i) != '\n')
    i++;
  if ( *(**content + i) == '\n')
  {
    *(**content + i) = '\0';
    i++;
  }
  str = ft_strdup(**content);
  tmp = ft_strdup(**content + i);
  free(**content);
  **content = tmp;

  return (str);
}

int		read_file(const int fd, char **content)
{
  int	nbyte;
  char	*tmp;
  char	buf[BUFF_SIZE + 1];

  while ( (nbyte = read(fd, buf, BUFF_SIZE)))
  {
    buf[nbyte] = '\0';
    tmp = *content;
    if (!(*content = ft_strjoin(*content, buf)))
      return (-1);
    free(tmp);

    if (ft_strchr(buf, '\n') != NULL)
      break;
  }
  return (nbyte);
}

int		get_next_line(const int fd, char **line)
{
	static	t_list *file;
	t_list	*actual;
    char	buf[BUFF_SIZE + 1];
    char	*tmp;
    int		nb;

    if (fd < 0 || line == NULL || (read(fd, buf, 0) < 0))
      return (-1);

    actual = get_true_list_with_fd(fd, &file);
    tmp = actual->content;
    nb = read_file(fd, &tmp);
    actual->content = tmp;

	if (nb == 0 && *((char *)actual->content) == '\0')
		return (0);
    *line = find_line(&(actual->content));
    return (1);
  }
