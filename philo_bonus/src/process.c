/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonwautelet <simonwautelet@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:37:00 by swautele          #+#    #+#             */
/*   Updated: 2022/04/21 20:58:18 by simonwautel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// static void	init_philo(t_param *param, t_param *info, pthread_mutex_t *fork)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < param->number)
// 	{
// 		*(info + i) = *param;
// 		(info + i)->pos = i + 1;
// 		if (i > 0)
// 			(info + i)->lfork = fork + i - 1;
// 		else
// 			(info + i)->lfork = fork + param->number - 1;
// 		(info + i)->rfork = fork + i;
// 		pthread_mutex_init(fork + i, NULL);
// 	}
// }

static void	processinator(t_param *data)
{
	int	i;
	int	id;

	i = -1;
	while (++i < data->number)
	{
		id = fork();
		if (id != 0)
		{
			philo_routine(data);
			break ;
		}
	}
	i = -1;
	while (++i < data->number)
		wait(&id);
	sem_close(data->forks);
	// sem_unlink("forks");
}

int	create_process(t_param *param)
{
	param->forks = malloc(sizeof(sem_t));
	if (param->forks == NULL)
		return (-1);
	param->speachrod = malloc(sizeof(pthread_mutex_t));
	if (param->speachrod == NULL)
	{
		free (param->forks);
		return (-1);
	}
	pthread_mutex_init(param->speachrod, NULL);
	param->forks = sem_open("forks", O_CREAT, O_RDWR, param->number);
	gettimeofday(&param->start, NULL);
	param->lastmeal = param->start;
	// init_philo(param, param, fork);
	processinator(param);
	free (param->speachrod);
	free (param->forks);
	return (0);
}
