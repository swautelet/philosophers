/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:18:23 by swautele          #+#    #+#             */
/*   Updated: 2022/03/30 13:20:30 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

int	main(int argc, char **argv)
{
	t_param	param;

	if (argc < 5 || argc > 6)
	{
		printf("Error\nNumber of parameter invalid\n");
		return (1);
	}
	param = init_param(argc, argv);
	if (param.number == -1)
	{
		printf("Error\nParameter invalid\n");
		return (2);
	}
	gettimeofday(&param.start, NULL);
	param.lastmeal = param.start;
	param.flagdeath = malloc(sizeof(char));
	param.flagdeath[0] = 0;
	printf("%p\n", param.flagdeath);
	printf("param.number = %d	param death = %zd	param eat = %zd	param sleep = %zd\n", param.number, param.death, param.eat, param.sleep);
	create_thread(param);
	free(param.flagdeath);
}
