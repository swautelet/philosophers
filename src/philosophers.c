/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:18:23 by swautele          #+#    #+#             */
/*   Updated: 2022/03/29 17:21:25 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

int	main(int argc, char **argv)
{
	t_param			param;

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
	printf("param.number = %d	param death = %d	param eat = %d	param sleep = %d\n", param.number, param.death, param.eat, param.sleep);
	create_thread(param);
}
