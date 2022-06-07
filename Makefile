# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imaalem <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/17 19:31:26 by imaalem           #+#    #+#              #
#    Updated: 2021/12/13 21:21:53 by imaalem          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CFLAG = -Wall -Werror -Wextra -D BUFFER_SIZE=128  -g

SRC = src/so_long.c gnl/get_next_line.c gnl/utils_str.c  gnl/utils_put.c src/check_error.c src/parse_map.c \
		src/so_long_utils.c src/utils_parsing.c src/so_long_utils_texture.c  src/so_long_utils_general.c \

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
			make -C minilib
			gcc -o $(NAME) $(OBJ) $(CFLAG) -I minilib minilib/libmlx_Linux.a -lXext -lX11 -L/usr/X11R6/lib

%.o : %.c	
			gcc $(CFLAG) -I minilib/ -o $@ -c $<

clean :
		rm -rf $(OBJ)

fclean : clean
		rm -rf $(NAME)

re : fclean all
	 make re -C minilib
.PHONY : all clean fclean re
