/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:26:13 by swautele          #+#    #+#             */
/*   Updated: 2022/03/29 17:38:19 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

void	*philo_routine(void *info)
{
	t_param			*data;
	struct timeval	now;

	data = (t_param *)info;
	printf("hello from philo no %d i got number = %d death = %d eat = %d sleep = %d \n", data->pos, data->number, data->death, data->eat, data->sleep);
	gettimeofday(&now, NULL);
	while (now.tv_usec - data->start.tv_usec < data->death)
	{
		pthread_mutex_lock(data->lfork);
		pthread_mutex_lock(data->rfork);
		printf("philo no %d can finally eat with my two forks %p and %p\n",data->pos, data->lfork, data->rfork);
		gettimeofday(&data->start, NULL);
		gettimeofday(&now, NULL);
		while (now.tv_usec - data->start.tv_usec < data->eat)
			gettimeofday(&now, NULL);
		pthread_mutex_unlock(data->lfork);
		pthread_mutex_unlock(data->rfork);
		printf("philo no %d sleep now\n", data->pos);
		while (now.tv_usec - data->start.tv_usec < data->sleep + data->eat)
			gettimeofday(&now, NULL);
	}
	printf("philo no %d is dead\n", data->pos);
	return (NULL);
}
