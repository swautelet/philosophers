/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:26:13 by swautele          #+#    #+#             */
/*   Updated: 2022/04/26 16:17:18 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

static int	l_to_rfork(t_param	*data)
{
	pthread_mutex_lock(data->lfork);
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	%d has taken a fork\n",
			time_since(data->start), data->pos);
	pthread_mutex_unlock(data->speachrod);
	if (data->lfork == data->rfork)
		return (-1);
	pthread_mutex_lock(data->rfork);
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	%d has taken a fork\n",
			time_since(data->start), data->pos);
	pthread_mutex_unlock(data->speachrod);
	return (0);
}

static int	r_to_lfork(t_param	*data)
{
	if (data->pos % 2 == 1)
		return (l_to_rfork(data));
	if (data->eat >= data->death)
		return (-1);
	pthread_mutex_lock(data->rfork);
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	%d has taken a fork\n",
			time_since(data->start), data->pos);
	pthread_mutex_unlock(data->speachrod);
	if (data->lfork == data->rfork)
		return (-1);
	pthread_mutex_lock(data->lfork);
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	%d has taken a fork\n",
			time_since(data->start), data->pos);
	pthread_mutex_unlock(data->speachrod);
	return (0);
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
		printf("%d	%d is eating\n", time_since(data->start),
			data->pos);
		if (data->meal == 0)
			check = 1;
		gettimeofday(&data->lastmeal, NULL);
	}
	else
		check = -1;
	pthread_mutex_unlock(data->speachrod);
	if (my_sleep(data->eat, data) == -1)
		check = -1;
	pthread_mutex_unlock(data->rfork);
	pthread_mutex_unlock(data->lfork);
	return (check);
}

static int	philo_sleep(t_param	*data)
{
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	%d is sleeping\n", time_since(data->start),
			data->pos);
	pthread_mutex_unlock(data->speachrod);
	if (my_sleep(data->sleep, data) == -1)
		return (-1);
	pthread_mutex_lock(data->speachrod);
	if (data->flagdeath[0] == 0 && time_since(data->lastmeal) < data->death)
		printf("%d	%d is thinking\n", time_since(data->start),
			data->pos);
	else
	{
		pthread_mutex_unlock(data->speachrod);
		return (-1);
	}
	pthread_mutex_unlock(data->speachrod);
	return (0);
}

void	*philo_routine(void *info)
{
	t_param	*data;

	data = (t_param *)info;
	if (data->pos % 2 == 1)
		usleep((data->eat / 3 * 2) * 1000);
	while (time_since(data->lastmeal) < data->death && data->meal != 0)
	{
		if (r_to_lfork(data) == -1)
			break ;
		if (data->lfork == data->rfork)
			break ;
		if (philo_eat(data) != 0)
			break ;
		if (philo_sleep(data) != 0)
			break ;
		usleep(500);
	}
	if (data->lfork == data->rfork)
	{
		my_sleep(data->death + 1, data);
		pthread_mutex_unlock(data->lfork);
	}
	philo_die(data);
	return (NULL);
}
