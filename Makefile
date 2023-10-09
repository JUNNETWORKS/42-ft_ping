NAME := ft_ping
CC := gcc
CFLAGS := -Werror -Wall -Wextra
# CFLAGS += -g -fsanitize=thread
# flags -MMD -MP -MF for generating dependency files
CFLAGS += -MMD -MP

SRC_DIR := src
OBJS_DIR := objs
DEPS_DIR := deps

SRCS := $(shell find src -type f -name '*.c')
OBJS := $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPENDENCIES := $(OBJS:.o=.d)

.PHONY: all
all: ${NAME}

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MF $(DEPS_DIR)/$(<:.c=.d) -c $< -o $@

-include $(DEPENDENCIES)

$(NAME): $(OBJS)
	$(LIBFT_MAKE)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

.PHONY: clean
clean:
	${RM} ${OBJS}
	${RM} ${DEPS}

.PHONY: fclean
fclean: clean
	${RM} ${NAME}

.PHONY: re
re: fclean all

.PHONY: all clean fclean re