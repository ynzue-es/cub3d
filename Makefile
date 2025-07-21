# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yannis <yannis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/21 09:04:02 by yannis            #+#    #+#              #
#    Updated: 2025/07/21 12:22:53 by yannis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm
SRCDIR = src
OBJDIR = obj

SRCS = 	main.c \
		utils.c \
		parsing/parse_cub.c \

SRCFILES = $(addprefix $(SRCDIR)/, $(SRCS))
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBFT = libft/libft.a
LIBFT_FILES = ft_strlen.c \
			  ft_strcpy.c \
			  ft_atoi.c \
			  ft_substr.c \
			  ft_strjoin.c \
			  ft_split.c \
			  ft_putendl_fd.c \
			  get_next_line/get_next_line.c \
			  
LIBFT_SRCS = $(addprefix libft/, $(LIBFT_FILES))

MLX = mlx/libmlx.a
HEADER = cub3d.h
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLXFLAGS) $(LIBFT)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(LIBFT): $(LIBFT_SRCS)
	make -C ./libft

-include $(OBJS:.o=.d)

clean:
	$(RM) -r $(OBJDIR)
	make -C ./libft clean

fclean: clean
	$(RM) $(NAME)
	make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re