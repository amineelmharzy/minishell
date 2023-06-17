CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror
RLFLAGS = -L /Users/ael-mhar/readline/lib -I /Users/ael-mhar/readline/include/readline -lreadline
#RLFLAGS = -lreadline
SRCS = check_ambiguous_redirect.c check_command.c check_empty_iofiles.c check_empty_pipe.c check_infiles.c close_builtin.c count_args.c exec_command.c exec_lcommand.c exit_status.c expand_env.c free_all.c ft_atoi.c ft_calloc.c ft_isalnum.c ft_itoa.c ft_joinchar.c ft_joinstr.c ft_split.c ft_split_with_pipe.c ft_split_with_space.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strlen_to_char.c ft_strncmp.c get_infile.c get_next_line.c get_path.c get_real_command.c handle_errors.c herdoc.c implement_redirections.c init_iofiles.c init_outfiles.c init_shell.c is_fine_with_quotes.c minishell.c parse_file.c parse_iofiles.c run.c set_infile.c set_outfile.c syntax_errors.c utils.c builtins/cd.c builtins/echo.c builtins/env.c builtins/export.c builtins/pwd.c builtins/run_builtin.c builtins/run_env.c builtins/unset.c builtins/utils.c
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

fbonus:
	make fclean -C bonus/

install-moacos:
	brew install $(DEPENDENCIES)
install-linux:
	sudo apt install libreadline-dev -y

leak: all
	valgrind --leak-check=full --track-origins=yes $(NAME)

.PHONY : all clean fclean re bonus
