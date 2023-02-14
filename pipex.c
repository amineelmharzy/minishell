/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:17:56 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/14 22:13:51 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int     ft_strlen(char *str)
{
        int     len;

        if (!str)
                return (0);
        len = 0;
        while (*str != '\0')
        {
                len++;
                str++;
        }
        return (len);
}

char    *ft_strjoin(char *s1, char *s2)
{
        int             i;
        char    *newstr;
        int             length;

        i = 0;
        if (!s2)
                return (NULL);
        length = ft_strlen((char *)s1) + ft_strlen((char *)s2);
        newstr = (char *)malloc(sizeof(char) * (length + 1));
        if (!newstr)
                return (NULL);
        while (s1[i])
        {
                newstr[i] = s1[i];
                i++;
        }
        while (*s2)
                newstr[i++] = *s2++;
        newstr[i] = '\0';
        //free(s1);
        return (newstr);
}

static int      check_sep(char c, char sep)
{
        int     i;

        i = 0;
        if (c == sep)
                return (1);
        return (0);
}

static int      count_strings(char *str, char set)
{
        int     count;
        int     i;

        i = 0;
        count = 0;
        while (str[i] != '\0')
        {
                while (str[i] != '\0' && (check_sep(str[i], set) == 1))
                {
                        i++;
                }
                if (str[i] != '\0')
                {
                        count++;
                }
                while (str[i] != '\0' && (check_sep(str[i], set) == 0))
                {
                        i++;
                }
        }
        return (count);
}

static int      ft_seplen(char *str, char charset)
{
        int     count;
        int     i;
        int     start;

        count = 0;
        i = 0;
        start = 0;
        while (str[i] && (check_sep(str[i], charset)))
        {
                i++;
        }
        start = i;
        while (str[i] && (!check_sep(str[i], charset)))
        {
                i++;
        }
        return (i - start);
}

static char     *ft_fill(char *str, char charset)
{
        char    *word;
        int             i;
        int             wl;

        wl = ft_seplen(str, charset);
        i = 0;
        word = malloc(wl + 1);
        if (!word)
                return (NULL);
        while (i < wl)
        {
                word[i] = str[i];
                i++;
        }
        word[i] = '\0';
        return (word);
}

char    **ft_split(char *str, char set)
{
        char    **array;
        int             i;

        if (!str)
                return (NULL);
        i = 0;
        array = malloc(sizeof(char *) * (count_strings(str, set) + 1));
        if (!array)
                return (NULL);
        while (*str != '\0')
        {
                while (*str != '\0' && check_sep(*str, set))
                {
                        str++;
                }
                if (*str != '\0')
                {
                        array[i] = ft_fill(str, set);
                        i++;
                }
                while (*str != '\0' && !check_sep(*str, set))
                        str++;
        }
        array[i] = 0;
		return (array);
}

char	*get_lfile(int ac, char **argv)
{
	int	i;

	i = 3;
	while (argv[i] != 0)
	{
		if (argv[i + 1] == 0)
			break ;
		i++;
	}
	return (argv[i]);
}

char	**get_path(char *cmd)
{
	char	**paths = ft_split(getenv("PATH"), ':');
	char	**parsed_args;
	char	*command;
	int	i;
	i = 0;
	while (paths[i] != 0)
	{
		command = ft_strjoin(paths[i], "/");
		command = ft_strjoin(command, cmd);
		parsed_args = ft_split(command, ' ');
		command = parsed_args[0];
		if (access(command, F_OK | X_OK) != -1)
		{
			return (parsed_args);
		}
		i++;
	}
	return (NULL);
}

/*
void	pipex(char *cmd1, int fdin, int fdout)
{
	int	fd[2];
	int	pid;
	char	**parsed_arg;

	if (pipe(fd) < 0)
		return ;
	parsed_arg = get_path(cmd1);
	if (!parsed_arg)
		return ;
	pid = fork();
	if (pid == 0)
	{
		execve(parsed_arg[0], parsed_arg, NULL);
	}
	waitpid(-1, NULL, 0);
}
*/

void	pipex(char *av, int fdin, int fdout)
{
	int	i;
	int	pid;
	int	pfd[2];
	char	**parsed_command;

	parsed_command = get_path(av);
	if (!parsed_command)
		return ;
	if (pipe(pfd) < 0)
		perror("Pipe Error\n");
	pid = fork();
	if (pid == 0)
	{
		dup2(pfd[1], 1);
		close(pfd[0]);
		execve(parsed_command[0], parsed_command, NULL);
	}
	else
	{
		dup2(pfd[0], 0);
		close(pfd[1]);
		waitpid(-1, NULL, 0);
	}
}

void	execlast(char *av)
{
	char **parsed_cmd  = get_path(av);
	int	pid;
	if(!parsed_cmd)
		return ;
	pid = fork();
	if (pid == 0)
	{
		execve(parsed_cmd[0], parsed_cmd, NULL);
	}
	else
		waitpid(-1, NULL, 0);
}

/*
void	pipex(int ac, char **av, int fdin, int fdout)
{
	int	count;

	count = ac - 3;
	int	pfd[count][2];
	int	i;
	int	j;
	char	**parsed_command;
	int	pid;
	i = 0;
	while (i < count)
	{
		if (pipe(pfd[i]) == -1 )
			perror("Pipe Error\n");
		i++;
	}
	i = 2;
	j = 0;
	while (i < ac - 2)
	{
		parsed_command = get_path(av[i]);
		if (!parsed_command)
			return ;
		pid = fork();
		if (!pid)
		{
			dup2(pfd[j][0], 0);
			dup2(pfd[j + 1][1], 1);
			close(pfd[j][1]);
			close(pfd[j + 1][0]);
			execve(parsed_command[0], parsed_command, NULL);
		}
		j++;
		i++;
	}
	waitpid(-1, NULL, 0);
	char *m = malloc(10);
	read(pfd[2][0], m, 9);
	m[9] = 0;
	printf("%s\n", m);
	pid = fork();
	parsed_command = get_path(av[i]);
	if (!pid)
	{
		dup2(pfd[j][0], 0);
		close(pfd[j][1]);
		dup2(fdout, 1);
		execve(parsed_command[0], parsed_command, NULL);
	}
}
*/

int	main(int argc, char **argv)
{
	char	*ffile;
	char	*lfile;
	int		i;
	int		ffd;
	int		lfd;

	i = 1;
	while (i < argc - 1)
	{
		pipex(argv[i], ffd, lfd);
		i++;
	}
	execlast(argv[i]);
}
