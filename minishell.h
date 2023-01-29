/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:28:54 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/01/29 17:19:02 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char				**ft_split(char *str, char set);
char				*ft_strjoin(char *s1, char *s2);
int					ft_strlen(char *str);
int					ft_strncmp(char *s1, char *s2, int n);
void				ft_putstr_fd(char *s, int fd);

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
	char			*command;
	char			*cmd;
	char			*prompt;
	char			*rcommand;
	char			**path;
	char			**envp;
	char			**commands;
	char			**parsed_command;
	char			**real_command;
	struct s_env	*env;
}					t_shell;

t_env				*create_node(char *var);
void				insert_node_to_end(t_env **head, t_env *new_node);
void				init_env(t_shell *shell);
void				add_env_var(t_shell *shell, char *var);
void				ft_putstr_fd(char *s, int fd);
void				env(t_shell *shell);
int					get_path(t_shell *shell);
void				echo(t_shell *shell);
void				cd(t_shell *shell);
void				export(t_shell *shell);
char				*ft_strchr(const char *s, int c);
char				**ft_split_semicolon(char *str);
char				*ft_strtrim(char *s1, char *set);
void				*ft_calloc(size_t elementCount, size_t elementSize);
char				*ft_strdup(char *src);
char				*ft_joinchar(char *s1, char c);
char				*ft_joinstr(char *s1, char *s2);
char				*is_env(t_shell *shell, char *s, int n);
int					ft_isalnum(int c);
int					is_fine_with_quotes(char *command);
void				free_env(t_shell *shell);

#endif