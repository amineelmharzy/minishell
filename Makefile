all:
	gcc -lreadline init.c get_real_command.c ft_calloc.c ft_isalnum.c ft_joinchar.c ft_joinstr.c init_env.c ft_strdup.c ft_split.c ft_strlen.c ft_strjoin.c ft_strncmp.c is_fine_with_quotes.c parse_iofiles.c ft_split_with_space.c utils.c exec_command.c check_infiles.c herdoc.c get_infile.c get_next_line.c ft_strchr.c init_outfiles.c ft_split_with_pipe.c set_infile.c check_command.c ft_itoa.c ft_strlen_to_char.c expand_env.c set_outfile.c handle_errors.c implement_redirections.c count_args.c -lreadline

install:
	apt install libreadline-dev -y
