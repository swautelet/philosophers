/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonwautelet <simonwautelet@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:26:13 by swautele          #+#    #+#             */
/*   Updated: 2022/04/21 21:02:59 by simonwautel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

static void	l_to_rfork(t_param	*data)
{
	sem_wait(data->forks);
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	philo n° %d has taken a fork\n",
			time_since(data->start), data->pos);
	pthread_mutex_unlock(data->speachrod);
	if (data->number == 1)
		return ;
	sem_wait(data->forks);
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	philo n° %d has taken a fork\n",
			time_since(data->start), data->pos);
	pthread_mutex_unlock(data->speachrod);
}

static void	r_to_lfork(t_param	*data)
{
	sem_wait(data->forks);
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	philo n° %d has taken a fork\n",
			time_since(data->start), data->pos);
	pthread_mutex_unlock(data->speachrod);
	if (data->number == 1)
		return ;
	sem_wait(data->forks);
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	philo n° %d has taken a fork\n",
			time_since(data->start), data->pos);
	pthread_mutex_unlock(data->speachrod);
}

static int	philo_eat(t_param	*data)
{
	int	check;

	check = 0;
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death
		&& data->meal != 0)
	{
		if (data->meal > 0)
			data->meal--;
		printf("%d	philo n° %d is eating\n", time_since(data->start),
			data->pos);
		if (data->meal == 0)
			check = 1;
	}
	gettimeofday(&data->lastmeal, NULL);
	pthread_mutex_unlock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		if (my_sleep(data->eat, data) == -1)
			check = -1;
	sem_post(data->forks);
	sem_post(data->forks);
	return (check);
}

static int	philo_sleep(t_param	*data)
{
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	philo n° %d is sleeping\n", time_since(data->start),
			data->pos);
	pthread_mutex_unlock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		if (my_sleep(data->sleep, data) == -1)
			return (-1);
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	philo n° %d is thinking\n", time_since(data->start),
			data->pos);
	pthread_mutex_unlock(data->speachrod);
	return (0);
}

void	*philo_routine(void *info)
{
	t_param	*data;

	data = (t_param *)info;
	while (time_since(data->lastmeal) < data->death && data->flagdeath[0] == 0
		&& data->meal != 0)
	{
		if (data->pos % 2 == 0)
			l_to_rfork(data);
		else
			r_to_lfork(data);
		if (data->number == 1)
			break ;
		if (philo_eat(data) != 0)
			break ;
		if (philo_sleep(data) != 0)
			break ;
	}
	if (data->number == 1)
	{
		my_sleep(data->death, data);
		sem_post(data->forks);
	}
	philo_die(data);
	return (NULL);
}
