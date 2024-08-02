/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:51:42 by adherrer          #+#    #+#             */
/*   Updated: 2024/08/02 19:16:14 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	catch_exp(int argc)
{
	int	status;
	int	error;

	error = 0;
	while (argc-- - 1 > 0)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) != 0)
			error = (WEXITSTATUS(status));
	}
	return (error);
}
