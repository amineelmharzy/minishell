CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror 
RLFLAGS = -lreadline #-L /Users/ael-mhar/homebrew/opt/readline/lib -I /Users/ael-mhar/homebrew/opt/readline/include/readline
SRCS = $(wildcard *.c) $(wildcard builtins/*.c)
OBJS = $(SRCS:.c=.o)
NAME = ./minishell
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

re: fclean all

bonus:
	make -C bonus/

install-moacos:
	brew install $(DEPENDENCIES)
install-linux:
	sudo apt install libreadline-dev -y

leak: all
	valgrind --leak-check=full --track-origins=yes $(NAME)

.PHONY = all clean fclean re bonus
