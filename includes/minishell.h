/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:06:37 by araysse           #+#    #+#             */
/*   Updated: 2022/09/20 12:38:41 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>
//#include <>
typedef struct redirec
{
	char	*type;
	char	*value;
	struct  redirec *next;
}	t_redirection;

typedef struct t_comand
{
	char	**cmd;
	t_redirection	*redirection;
	struct t_comand	*next;
}	t_cmd;

typedef struct lexer_struct
{
	char c;
	unsigned int i;
	char *contents;
} lexer_t;

typedef struct token_struct
{
	enum
	{
		token_herdoc,
		token_apend,
		token_infile,
		token_outfile,
		token_word,
		token_pipe
	} type;
	char 	*value;
} token_t;
// fuction extern
unsigned int	ft_tstrlen(char *str);
// lexer_struct
lexer_t		*init_lexer(char *contents);

void	lexer_advance(lexer_t *lexer);

void	lexer_skip_whitespace(lexer_t *lexer);
token_t	*lexer_get_next_token(lexer_t *lexer, char **env);
char	*lexer_collect_string(lexer_t *lexer, char **env);
token_t *lexer_collect_id(lexer_t *lexer, char **env);
token_t	*lexer_advance_with_token(lexer_t *lexer, token_t *token);
char	*lexer_get_current_char_as_atring(lexer_t	*lexer);
token_t	*lexer_infile(lexer_t *lexer);
token_t	*lexer_outfile(lexer_t *lexer);
char	*lexer_collect_single_quot(lexer_t *lexer);
char	*ft_strcat(char *dest, char *src);
// token_struct

token_t	*init_token(int type, char *value);

// pars
char    *ft_find_in_path(char **env, char *str);
char	*ft_tsubstr(char *s, unsigned int start, size_t len);
// static int	min(int a, int b);
char	*ft_tstrjoin(char *s1, char *s2);
int		ft_tstrncmp(const char *s1, const char *s2, size_t n);
char	*find_in_env(lexer_t *lexer, char **env);
char	*get_alnum(char *str, lexer_t *lexer);
char	*find_in_env2(lexer_t *lexer, char **env);
void    rl_replace_line(const char *text, int clear_undo);
void	ft_lstadd_back(t_cmd **alst, t_cmd *new);
int		is_redirection(token_t *token);
char	*ft_getchar(char c);
char	*struct_cmd(lexer_t *lexer, token_t *token, char *str, char **env);
void 	collect_redirection(t_redirection *redir, lexer_t *lexer, token_t *token, char **env);
t_redirection	*struct_redir(token_t *token, lexer_t *lexer, char **env);
void	ft_lstadd_bak(t_redirection **alst, t_redirection *new);
void	ft_lstnew(t_cmd **cmd, t_redirection* redir, char* str);
char	**ft_tsplit(const char *s, char c);
#endif
