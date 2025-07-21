# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yannis <yannis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/21 09:04:02 by yannis            #+#    #+#              #
#    Updated: 2025/07/21 10:31:15 by yannis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm
SRCDIR = src
OBJDIR = obj

SRCS = 	main.c

SRCFILES = $(addprefix $(SRCDIR)/, $(SRCS))
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

MLX = mlx/libmlx.a
LIBFT = libft/libft.a
HEADER = cub3d.h
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLXFLAGS) $(LIBFT)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(LIBFT):
	make -C ./libft

clean:
	$(RM) -r $(OBJDIR)
	make -C ./libft clean

fclean: clean
	$(RM) $(NAME)
	make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re