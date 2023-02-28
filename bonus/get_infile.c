/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 08:16:33 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/25 08:15:38 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_infile(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->infiles[i] != 0)
		i++;
	return (shell->infiles[i - 1]);
}
