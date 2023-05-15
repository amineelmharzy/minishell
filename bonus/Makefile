CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror 
RLFLAGS = -L /Users/ael-mhar/homebrew/opt/readline/lib -I /Users/ael-mhar/homebrew/opt/readline/include/readline
SRCS = $(wildcard *.c) $(wildcard builtins/*.c)
OBJS = $(SRCS:.c=.o)
NAME = minishell
NAMEOBJ = minishell.o
NAMESRC = minishell.c

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

all : $(NAME)

$(NAMEOBJ) : $(NAMESRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS) $(NAMEOBJ)
	$(CC) $(CFLAGS) $(RLFLAGS) -lreadline $^ -o $@

clean :
	$(RM) $(OBJS) $(NAMEOBJ)

fclean : clean
	$(RM) $(NAME)

re: fclean all

install:
	apt install libreadline-dev -y

leak: all
	valgrind --leak-check=full --track-origins=yes  --leak-check=full ./minishell


.PHONY = all clean fclean re
