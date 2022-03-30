/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swautele <swautele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:12:43 by swautele          #+#    #+#             */
/*   Updated: 2022/03/30 13:08:16 by swautele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_param{
	int				number;
	ssize_t			death;
	ssize_t			eat;
	ssize_t			sleep;
	int				meal;
	int				pos;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	struct timeval	start;
	struct timeval	lastmeal;
	char			*flagdeath;
}	t_param;

int		ft_atoi(const char *str, char *flagerr);
int		create_thread(t_param param);
t_param	init_param(int argc, char **argv);
void	*philo_routine(void *info);
ssize_t	time_since(struct timeval last);
void	my_sleep(ssize_t time);

#endif
