/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 21:45:34 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/28 02:08:09 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	finaly_openfile(char **av, int argc)
{
	int		fd_out;

	if (ft_strcmp(av[1], "here_doc"))
		fd_out = open_file(av[argc - 1], STDOUT_FILENO);
	else
		fd_out = open_file(av[argc - 1], 2);
	return (fd_out);
}
