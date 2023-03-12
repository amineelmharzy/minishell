#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	int i;

	i = -1;
	char *variable = av[1];
	char	**path = ft_split(getenv("PATH"), ':');
	while(path[++i])
	{
		path[i] = ft_strjoin(path[i],"/");
		path[i] = ft_strjoin(path[i], variable);
		if (!access(path[i],X_OK | F_OK))
		{
			printf("yeeeh we found it\n");
		}
	}


}
