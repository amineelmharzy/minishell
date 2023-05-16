CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror 
RLFLAGS = -L /Users/ael-mhar/homebrew/opt/readline/lib -I /Users/ael-mhar/homebrew/opt/readline/include/readline
SRCS = $(wildcard *.c) $(wildcard builtins/*.c)
OBJS = $(SRCS:.c=.o)
NAME = minishell
NAMEOBJ = minishell.o
NAMESRC = minishell.c
DEPENDENCIES = readline

%.o : %.c
	@$(CC) $(FLAGS) -c $< -o $@

all : $(NAME)

$(NAMEOBJ) : $(NAMESRC)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS) $(NAMEOBJ)
	@$(CC) $(CFLAGS) $(RLFLAGS) -lreadline $^ -o $@

clean :
	@$(RM) $(OBJS) $(NAMEOBJ)

fclean : clean
	@$(RM) $(NAME)

bonus:
	make -C bonus

re: fclean all

install:
	brew install readline

leak: all
	valgrind --leak-check=full --track-origins=yes $(NAME)

.PHONY = all clean fclean bonus re
