/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:51:42 by adherrer          #+#    #+#             */
/*   Updated: 2024/08/05 17:04:05 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	catch_exp(int argc, pid_t *pids)
{
	int	status;
	int	error;
	int	i;

	error = 0;
	i = 0;
	while (argc - 2 > i)
	{
		waitpid(pids[i++], &status, 0);
	}
	waitpid(pids[i], &status, 0);
	error = (WEXITSTATUS(status));
	free(pids);
	return (error);
}
