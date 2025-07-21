NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rc
RM = rm -f

OBJDIR = obj

FILES = ft_strlen \
		ft_strcpy \
		ft_atoi \
		ft_substr \
		ft_strjoin \
		ft_split \
		ft_putendl_fd \
		get_next_line/get_next_line \

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addprefix $(OBJDIR)/, $(FILES:=.o))

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $@ $^

all: $(NAME)

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: bonus all clean fclean re