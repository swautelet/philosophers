/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:37:00 by swautele          #+#    #+#             */
/*   Updated: 2022/03/31 15:19:03 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_thread(t_param *param)
{
	int				i;
	pthread_mutex_t	*fork;
	pthread_t		*philo;
	t_param			*info;

	fork = malloc(sizeof(pthread_mutex_t) * param->number);
	philo = malloc(sizeof(pthread_t) * param->number);
	info = malloc(sizeof(t_param) * param->number);
	// param->speachrod = malloc(sizeof(pthread_mutex_t));
	// pthread_mutex_init(param->speachrod, NULL);
	// printf("%p\n", param->speachrod);
	gettimeofday(&param->start, NULL);
	param->lastmeal = param->start;
	param->lastmeal.tv_sec++;
	i = -1;
	while (++i < param->number)
	{
		*(info + i) = *param;
		(info + i)->pos = i;
		if (i > 0)
			(info + i)->lfork = fork + i - 1;
		else
			(info + i)->lfork = fork + param->number - 1;
		(info + i)->rfork = fork + i;
		pthread_mutex_init(fork + i, NULL);
	}
	i = -1;
	while (++i < param->number)
		pthread_create(philo + i, NULL, &philo_routine, info + i);
	i = -1;
	while (++i < param->number)
		pthread_join(*(philo + i), NULL);
	i = -1;
	while (++i < param->number)
		pthread_mutex_destroy(fork + i);
	// pthread_mutex_destroy(param->speachrod);
	// free (param->speachrod);
	free (fork);
	free (philo);
	free (info);
	return (0);
}
