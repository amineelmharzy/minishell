/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 09:13:15 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/12 09:23:45 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

int main()
{
	char **a1 = ft_split("/usr/bin/awk {print$1} README.md", ' ');
	int	pid = fork();
	if (pid == 0)
	{
		execve(a1[0], a1, NULL);
	}
}
