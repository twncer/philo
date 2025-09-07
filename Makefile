# CFLAGS = 0

# all:
# 	@cc -lpthread *.c */*.c -o philo
# 	@echo Made


CFLAGS = -Wall -Wextra -g
LDFLAGS = -lpthread

NAME = philo

all: $(NAME)

$(NAME):
	@cc $(CFLAGS) *.c */*.c $(LDFLAGS) -o $(NAME)
	@echo "Made"

debug: CFLAGS += -fsanitize=thread -O0
debug: $(NAME)

tsan: CFLAGS += -fsanitize=thread
tsan: $(NAME)

clean:
	@rm -f $(NAME)

.PHONY: all debug tsan clean