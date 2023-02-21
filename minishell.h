/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:31:33 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/21 12:30:29 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BUFFER_SIZE 1

# define E_PERM "Permission denied"
# define E_NOTF "No such file or directory"
# define E_PIPE "syntax error near unexpected token `|'"
# define E_REDR "syntax error near unexpected token `newline'"
# define E_TOMR "too many arguments"
# define E_NCMD "command not found"

char				**ft_split(char *str, char set);
char				*ft_strjoin(char *s1, char *s2);
int					ft_strlen(char *str);
int					ft_strncmp(char *s1, char *s2, int n);
void				ft_putstr_fd(char *s, int fd);

typedef struct s_env
{
	char			*key;
	char			*value;
	char			**key_val;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
	int				stdin_fd;
	int				stdout_fd;
	int				ofile;
	int				ifile;
	int				exit_status;
	int				is_pipe;
	char			cwd[PATH_MAX];
	char			*command;
	char			*cmd;
	char			*prompt;
	char			*herdoc_output;
	char			*infile;
	char			*outfile;
	char			*rcommand;
	char			**path;
	char			**envp;
	char			**commands;
	char			**parsed_command;
	char			**infiles;
	char			**outfiles;
	char			**afiles;
	char			**herdocs;
	struct s_env	*env;
}					t_shell;

void				init_shell(t_shell *shell, char **envp);
void				insert_node_to_end(t_shell *shell, t_env *new_node);
void				add_env_var(t_shell *shell, char *var);
void				ft_putstr_fd(char *s, int fd);
void				env(t_shell *shell, int opt);
int					get_path(t_shell *shell);
void				echo(t_shell *shell);
void				cd(t_shell *shell);
void				export(t_shell *shell);
void				pwd(t_shell *shell);
void				unset(t_shell *shell);
char				*ft_strchr(const char *s, int c);
char				**ft_split_semicolon(char *str);
char				*ft_strtrim(char *s1, char *set);
void				*ft_calloc(size_t elementCount, size_t elementSize);
char				*ft_strdup(char *src);
char				*ft_joinchar(char *s1, char c);
char				*ft_joinstr(char *s1, char *s2);
char				*is_env(t_shell *shell, char *s, int n, int ret);
int					ft_isalnum(int c);
int					is_fine_with_quotes(char *command);
void				free_all(t_shell *shell, int option);
int					parse_infiles(t_shell *shell);
int					implement_redirection(t_shell *shell);
char				**ft_split_with_space(char *command);
void				exec_command(t_shell *shell);
int					check_infiles(t_shell *shell);
char				*herdoc(t_shell *shell);
char				*get_next_line(int fd);
char				*get_infile(t_shell *shell);
int					init_outfiles(t_shell *shell);
int					init_iofiles(t_shell *shell);
char				**ft_split_with_pipe(char *command);
int					count_pipes(char *str);
int					count_iofiles(char *str, char *set);
int					count_args(char *command);
void				exec_lastcommand(t_shell *shell);
void				set_infile(t_shell *shell);
void				set_outfile(t_shell *shell);
int					check_command(t_shell *shell, int i);
char				*ft_itoa(int n);
char				*get_real_command(t_shell *shell);
int					ft_strlen_to_char(char *str, char c);
int					expand_env(t_shell *shell, char *str, char **real);
int					iofiles_errors(t_shell *shell, char *set);
int					parse_error(t_shell *shell);
char				*parse_iofiles(t_shell *shell, char *set);
void				print_error(t_shell *shell, char *target, char *error,
						int status);
void				_print_error(t_shell *shell, char *error, int status);
int					check_identifier(t_shell *shell, char *str);
char				*exported_key(char *var);
void				ft_putstr_fd(char *s, int fd);
int					init_outfd(t_shell *shell);
char				*get_infile(t_shell *shell);
t_env				*create_node(char *var);

#endif
