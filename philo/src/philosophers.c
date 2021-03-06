/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:18:23 by swautele          #+#    #+#             */
/*   Updated: 2022/04/26 17:11:10 by swautele         ###   ########.fr       */
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
	if (param->meal != 0)
	{
		param->flagdeath = malloc(sizeof(int));
		if (param->flagdeath != NULL)
		{
			param->flagdeath[0] = 0;
			create_thread(param);
			free(param->flagdeath);
		}
	}
	free (param);
}
