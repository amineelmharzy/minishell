#all :
#	gcc -lreadline init.c get_real_command.c ft_calloc.c ft_isalnum.c ft_joinchar.c ft_joinstr.c ft_strdup.c ft_split.c ft_strlen.c ft_strjoin.c ft_strncmp.c is_fine_with_quotes.c parse_iofiles.c ft_split_with_space.c exec_command.c check_infiles.c herdoc.c get_next_line.c ft_strchr.c init_outfiles.c ft_split_with_pipe.c set_infile.c check_command.c ft_itoa.c ft_strlen_to_char.c expand_env.c set_outfile.c handle_errors.c implement_redirections.c count_args.c builtins/*.c get_path.c get_infile.c utils.c init_shell.c free_all.c init_iofiles.c check_empty_iofiles.c -lreadline -L /Users/ael-mhar/goinfre/homebrew/opt/readline/lib -I /Users/ael-mhar/goinfre/homebrew/opt/readline/include/readline -o minishell

all :
	gcc -lreadline init.c get_real_command.c ft_calloc.c ft_isalnum.c ft_joinchar.c ft_joinstr.c ft_strdup.c ft_split.c ft_strlen.c ft_strjoin.c ft_strncmp.c is_fine_with_quotes.c parse_iofiles.c ft_split_with_space.c exec_command.c check_infiles.c herdoc.c get_next_line.c ft_strchr.c init_outfiles.c ft_split_with_pipe.c set_infile.c check_command.c ft_itoa.c ft_strlen_to_char.c expand_env.c set_outfile.c handle_errors.c implement_redirections.c count_args.c builtins/*.c get_path.c get_infile.c utils.c init_shell.c free_all.c init_iofiles.c check_empty_iofiles.c ft_atoi.c -lreadline  -o minishell

install:
	apt install libreadline-dev -y

leak:
	valgrind --leak-check=full --track-origins=yes  --leak-check=full ./a.out
