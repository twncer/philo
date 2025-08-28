CFLAGS = 0

all:
	@cc *.c */*.c -lreadline -o philo
	@echo Made