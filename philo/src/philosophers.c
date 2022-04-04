/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonwautelet <simonwautelet@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:18:23 by swautele          #+#    #+#             */
/*   Updated: 2022/04/04 12:17:20 by simonwautel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

int	main(int argc, char **argv)
{
	t_param	*param;

	if (argc < 5 || argc > 6)
	{
		printf("Error\nNumber of parameter invalid\n");
		return (1);
	}
	param = init_param(argc, argv);
	if (param == NULL)
	{
		printf("Error\nParameter invalid\n");
		return (2);
	}
	// gettimeofday(&param->start, NULL);
	// param->lastmeal = param->start;
	param->flagdeath = malloc(sizeof(char));
	param->flagdeath[0] = 0;
	create_thread(param);
	free(param->flagdeath);
	free (param);
}
