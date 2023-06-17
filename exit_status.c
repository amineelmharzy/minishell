/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:42:16 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/06/16 16:47:53 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_wexitstatus(int status)
{
	return (((status) & 0xff00) >> 8);
}

int	_wtermsig(int status)
{
	return ((status) & 0x7f);
}

int	_wifexited(int status)
{
	return (_wtermsig(status) == 0);
}

int	_wifsignaled(int status)
{
	return (((signed char)(((status) & 0x7f) + 1) >> 1) > 0);
}
