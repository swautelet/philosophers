/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonwautelet <simonwautelet@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:26:13 by swautele          #+#    #+#             */
/*   Updated: 2022/04/04 00:33:28 by simonwautel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

void	*philo_routine(void *info)
{
	t_param			*data;

	data = (t_param *)info;
	// printf("hello from philo no %d i got number = %d death = %zd eat = %zd sleep = %zd \n", data->pos, data->number, data->death, data->eat, data->sleep);
	// printf("%p\n", data->speachrod);
	if (data->pos % 2 == 1)
		while (time_since(data->start) < 1000 + (data->eat / 2))
			usleep(1);
	else if (data->pos % 2 == 1 && data->eat == 1)
		while (time_since(data->start) < 1001)
			usleep(1);
	else
		while (time_since(data->start) < 1000)
			usleep(1);
	while (time_since(data->lastmeal) < data->death && data->flagdeath[0] == 0)
	{
		pthread_mutex_lock(data->lfork);
		pthread_mutex_lock(data->speachrod);
		if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
			printf("%d	philo n° %d has taken a fork\n", time_since(data->start) - 1000, data->pos);
		pthread_mutex_unlock(data->speachrod);
		if (data->lfork == data->rfork)
			break ;
		pthread_mutex_lock(data->rfork);
		// if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
			// printf("%zd	philo no %d has taken a fork\n", time_since(data->start) - 1000, data->pos);
		pthread_mutex_lock(data->speachrod);
		if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
			printf("%d	philo n° %d is eating\n", time_since(data->start) - 1000, data->pos);
		gettimeofday(&data->lastmeal, NULL);
		pthread_mutex_unlock(data->speachrod);
		if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
			my_sleep(data->eat);
		pthread_mutex_unlock(data->lfork);
		pthread_mutex_unlock(data->rfork);
		pthread_mutex_lock(data->speachrod);
		if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
			printf("%d	philo n° %d is sleeping\n",time_since(data->start) - 1000, data->pos);
		pthread_mutex_unlock(data->speachrod);
		if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
			my_sleep(data->sleep);
		pthread_mutex_lock(data->speachrod);
		if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
			printf("%d	philo n° %d is thinking\n", time_since(data->start) - 1000, data->pos);
		pthread_mutex_unlock(data->speachrod);
	}
	if (data->lfork == data->rfork)
	{
		pthread_mutex_unlock(data->lfork);
		pthread_mutex_unlock(data->speachrod);
		my_sleep(data->death);
	}
	pthread_mutex_lock(data->speachrod);
	data->flagdeath[0]++;
	if (data->flagdeath[0] == 1)
	{
		printf("%d	philo n° %d died\n", time_since(data->start) - 1000, data->pos);
	}
	pthread_mutex_unlock(data->speachrod);
	return (NULL);
}
