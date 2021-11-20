MY_NAME		:= my_containers
STD_NAME	:= std_containers
obj     	:= ./main.o
CC			:= clang++
CFLAGS		:= -Wall -Werror -Wextra

all: $(MY_NAME) $(STD_NAME)

deps := $(patsubst %.o, %.d, $(obj))
-include $(deps)
DEPFLAGS = -MMD -MF $(@:.o=.d)

$(MY_NAME): $(obj)
	$(CC) $(CFLAGS) $(obj) -o $(MY_NAME)

$(STD_NAME): $(obj)
	sh toStd.bash
	$(CC) $(CFLAGS) $(obj) -o $(STD_NAME)
	sh toFt.bash

%.o: %.c Makefile
	$(CC) -c $< $(DEPFLAGS)

clean:
	rm -f $(obj) $(deps)

fclean: clean
	rm -f $(MY_NAME)
	rm -f $(STD_NAME)

re: fclean all

.PHONY: clean all fclean re