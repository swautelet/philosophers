/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:37:00 by swautele          #+#    #+#             */
/*   Updated: 2022/04/22 18:48:30 by swautele         ###   ########.fr       */
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
static void	kill_child(int id[200], t_param *data)
{
	int	ret;
	int	i;

	ret = 0;
	i = 200;
	while (i >= 0 && ret >= 0)
	{
		i = waitpid(-1, &ret, WNOHANG);
		if (i > 0)
		{
			i = -1;
			// usleep(1000);
			while (id[++i] != 0 && i <= 200)
				kill(id[i], SIGINT);
			sem_post(data->speachrod);
		}
	}
}

static void	processinator(t_param *data)
{
	int	i;
	int	id[200];

	memset(id, 0, sizeof(int) * 200);
	i = -1;
	while (++i <= data->number)
	{
		id[i] = fork();
		if (id[i] == 0)
		{
			data->pos = i;
			philo_routine(data);
			exit (0);
		}
	}
	kill_child(id, data);
	sem_close(data->forks);
	sem_close(data->speachrod);
}

int	create_process(t_param *param)
{
	sem_unlink("/forks");
	sem_unlink("/speach");
	param->speachrod = sem_open("/speach", O_CREAT, S_IRUSR | S_IWUSR, 1);
	param->forks = sem_open("/forks", O_CREAT, S_IRUSR | S_IWUSR,
			param->number);
	gettimeofday(&param->start, NULL);
	param->lastmeal = param->start;
	processinator(param);
	return (0);
}
