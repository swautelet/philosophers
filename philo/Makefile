# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swautele <swautele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/29 14:48:19 by swautele          #+#    #+#              #
#    Updated: 2022/04/26 16:02:44 by swautele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
FILES = src/philosophers.c \
	src/param.c \
	src/thread.c \
	src/ft_atoi.c \
	src/routine.c \
	src/time.c
CC = gcc
CFLAGS = -Wextra -Werror -Wall
OBJECT = $(FILES:.c=.o)
DFLAGS = -g -fsanitize=thread

all : $(NAME)

clean :
	rm -f $(OBJECT)

fclean : clean
	rm -f $(NAME)

$(NAME) : $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o $(NAME)

.o : .c
	$(CC) $(CFLAGS) $? -o $@

test :
	$(CC) $(CFLAGS) $(DFLAGS) $(FILES) -o $(NAME)
	./$(NAME) 20 410 200 200 10 && ./$(NAME) 5 610 200 200 10 && ./$(NAME) 4 310 200 100 10

re : fclean all

bonus :
	make -C ../philo_bonus

save :
	git commit -am autosave
	git push https://github.com/swautelet/philosophers.git

.phony : save test fclean clean