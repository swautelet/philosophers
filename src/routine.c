/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:26:13 by swautele          #+#    #+#             */
/*   Updated: 2022/03/30 15:54:29 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

void	*philo_routine(void *info)
{
	t_param			*data;

	data = (t_param *)info;
	printf("hello from philo no %d i got number = %d death = %zd eat = %zd sleep = %zd \n", data->pos, data->number, data->death, data->eat, data->sleep);
	// printf("%p\n", data->speachrod);
	while (time_since(data->lastmeal) < data->death && data->flagdeath[0] == 0 && data->lfork != data->rfork)
	{
		pthread_mutex_lock(data->lfork);
		pthread_mutex_lock(data->rfork);
		pthread_mutex_lock(data->speachrod);
		gettimeofday(&data->lastmeal, NULL);
		if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		{
			printf("%zd	philo no %d can finally eat with my two forks %p and %p\n", time_since(data->start), data->pos, data->lfork, data->rfork);
		}
		pthread_mutex_unlock(data->speachrod);
		my_sleep(data->eat);
		pthread_mutex_unlock(data->lfork);
		pthread_mutex_unlock(data->rfork);
		pthread_mutex_lock(data->speachrod);
		if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
			printf("%zd	philo no %d sleep now\n",time_since(data->start), data->pos);
		pthread_mutex_unlock(data->speachrod);
		if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
			my_sleep(data->sleep);
	}
	// if (data->lfork == data->rfork)
		// my_sleep(data->death);
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0)
		printf("%zd	philo no %d is dead time since last meal = %zd\n", time_since(data->start), data->pos, time_since(data->lastmeal));
	data->flagdeath[0] = 1;
	pthread_mutex_unlock(data->speachrod);
	return (NULL);
}
