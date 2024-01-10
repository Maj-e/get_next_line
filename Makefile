# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 18:24:27 by mjeannin          #+#    #+#              #
#    Updated: 2024/01/10 18:52:06 by mjeannin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= get_next_line.a

SRCS 			=  get_next_line.c get_next_line_utils.c

OBJS 			= $(SRCS:.c=.o)

CC 				= gcc
CFLAGS 			= -Wall -Wextra -Werror
RM 				= rm -f

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -c $(SRCS)
	ar crs $(NAME)	$(OBJS)
all:	$(NAME)
clean :
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re:	clean all


.PHONY: all clean fclean re