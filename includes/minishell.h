/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araysse <araysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:06:37 by araysse           #+#    #+#             */
/*   Updated: 2022/10/05 11:09:36 by araysse          ###   ########.fr       */
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
}	t_redir;

typedef struct t_comand
{
	char	**cmd;
	int 	fd[2];
	int		infile;
	int		outfile;
	t_redir	*redirection;
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
token_t	*lexer_next(lexer_t *lexer, char **env);
char	*lexer_collect_string(lexer_t *lexer, char **env);
token_t *lexer_collect_id(lexer_t *lexer, char **env);
token_t	*lxr_ad_tok(lexer_t *lexer, token_t *token);
char	*lxr_as_str(lexer_t	*lexer);
token_t	*lexer_infile(lexer_t *lexer);
token_t	*lexer_outfile(lexer_t *lexer);
char	*lexer_collect_single_quot(lexer_t *lexer);
char	*ft_strcat(char *dest, char *src);
// token_struct

token_t	*init_tok(int type, char *value);

// pars
char    *f_in_path(char **env, char *str);
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
void 	col_redir(t_redir *redir, lexer_t *lexer, token_t *token, char **env);
t_redir	*struct_redir(token_t *token, lexer_t *lexer, char **env);
void	ft_lstadd_bak(t_redir **alst, t_redir *new);
void	ft_lstnew(t_cmd **cmd, t_redir *redir, char* str);
char	**ft_tsplit(char *s, char c);
char	*ft_eror(int i);
void	ft_after_pipe(lexer_t *lexer, token_t *token, char **env);
int		valid_char(lexer_t *lexer);
void	ft_free_struct(t_cmd **cmd);
void	ft_free2(t_redir **redir);
void	function(t_cmd **cmd, lexer_t **lexer, char **env, token_t **token);
#endif
