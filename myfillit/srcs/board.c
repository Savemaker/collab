//header

#include "../includes/fillit.h"

char	**createboard(int s)
{
	int i;
	int j;
	char **board;

	if (!(board = (char **)malloc(sizeof(char *) * s)))
		return (NULL);
	while (i < s)
	{
		board[i] = (char *)malloc(sizeof(char) * s + 1);
		i++;
	}
	i = 0;
	while (i < s)
	{
		j = 0;
		while (j < s)
		{
			board[i][j] = '.';
			j++;
		}
		board[i][j + 1] = '\0';
		i++;
	}
	return (board);
}

void freeboard(char **board, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(board[i]);
		i++;
	}
	free(board);
}
