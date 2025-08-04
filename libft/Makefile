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
		ft_strncmp \
		free_split \
		get_next_line/get_next_line \
		ft_isdigit \
		ft_strndup \
		ft_str_trim_nl \
		line_digit

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addprefix $(OBJDIR)/, $(FILES:=.o))

all: $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $@ $^

clean:
	$(RM) -r $(OBJDIR)
	$(RM) $(NAME)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: bonus all clean fclean re