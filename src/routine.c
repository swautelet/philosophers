/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:26:13 by swautele          #+#    #+#             */
/*   Updated: 2022/03/30 14:36:02 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

void	*philo_routine(void *info)
{
	t_param			*data;

	data = (t_param *)info;
	printf("hello from philo no %d i got number = %d death = %zd eat = %zd sleep = %zd \n", data->pos, data->number, data->death, data->eat, data->sleep);
	// printf("%p\n", data->speachrod);
	while (time_since(data->lastmeal) < data->death && data->flagdeath[0] == 0)
	{
		pthread_mutex_lock(data->lfork);
		pthread_mutex_lock(data->rfork);
		pthread_mutex_lock(data->speachrod);
		if (data->flagdeath[0] == 0)
		{
			gettimeofday(&data->lastmeal, NULL);
			printf("%zd	philo no %d can finally eat with my two forks %p and %p\n", time_since(data->start), data->pos, data->lfork, data->rfork);
		}
		pthread_mutex_unlock(data->speachrod);
		my_sleep(data->eat);
		pthread_mutex_unlock(data->lfork);
		pthread_mutex_unlock(data->rfork);
		pthread_mutex_lock(data->speachrod);
		if (data->flagdeath[0] == 0)
			printf("%zd	philo no %d sleep now\n",time_since(data->start), data->pos);
		pthread_mutex_unlock(data->speachrod);
		if (data->flagdeath[0] == 0)
			my_sleep(data->sleep);
	}
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0)
		printf("philo no %d is dead\n", data->pos);
	data->flagdeath[0] = 1;
	pthread_mutex_unlock(data->speachrod);
	return (NULL);
}
