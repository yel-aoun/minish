/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:06:37 by araysse           #+#    #+#             */
/*   Updated: 2022/10/14 11:54:27 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct redirec
{
	char			*type;
	char			*value;
	struct redirec	*next;
}	t_redir;

typedef struct t_comand
{
	char			**cmd;
	int				infile;
	int				outfile;
	t_redir			*redirection;
	struct t_comand	*next;
}	t_cmd;

typedef struct lexer_struct
{
	char			c;
	unsigned int	i;
	char			*contents;
}	t_lexer;

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
	}	e_type;
	char	*value;
}	t_token;

unsigned int	ft_tstrlen(char *str);
t_lexer			*init_lexer(char *contents);
void			lexer_advance(t_lexer *lexer);

void			lexer_skip_whitespace(t_lexer *lexer);
t_token			*lexer_next(t_lexer *lexer, char **env, int k);
char			*lexer_collect_string(t_lexer *lexer, char **env, int k);
t_token			*lexer_collect_id(t_lexer *lexer, char **env, int k);
t_token			*lxr_ad_tok(t_lexer *lexer, t_token *token);
char			*lxr_as_str(t_lexer	*lexer);
t_token			*lexer_infile(t_lexer *lexer);
t_token			*lexer_outfile(t_lexer *lexer);
char			*lexer_collect_single_quot(t_lexer *lexer, int k);
char			*ft_strcat(char *dest, char *src);

t_token			*init_tok(int type, char *value);

char			*f_in_path(char **env, char *str);
char			*ft_tsubstr(char *s, unsigned int start, size_t len);			
char			*ft_tstrjoin(char *s1, char *s2);
int				ft_tstrncmp(char *s1, char *s2, size_t n);
char			*find_in_env(t_lexer *lexer, char **env);
char			*get_alnum(char *str, t_lexer *lexer);
char			*find_in_env2(t_lexer *lexer, char **env);
void			rl_replace_line(const char *text, int clear_undo);
void			ft_lstadd_back(t_cmd **alst, t_cmd *new);
int				is_redirection(t_token *token);
char			*ft_getchar(char c);
char			*struct_cmd(t_lexer *lexer, t_token *token \
				, char *str, char **env);
void			col_redir(t_redir *redir, t_lexer *lexer \
				, t_token *token, char **env);
t_redir			*struct_redir(t_token *token, t_lexer *lexer, char **env);
void			ft_lstadd_bak(t_redir **alst, t_redir *new);
void			ft_lstnew(t_cmd **cmd, t_redir *redir, char *str);
char			**ft_tsplit(char *s, char c);
char			*ft_eror(char *s, int i, int k);
void			ft_after_pipe(t_lexer **lexer, t_token *token, char **env);
int				valid_char(t_lexer *lexer);
void			ft_free_struct(t_cmd **cmd);
void			ft_free2(t_redir **redir);
void			function(t_cmd **cmd, t_lexer **lexer \
				, char **env, t_token **token);
void			free_tok1(t_redir *redir, t_token *tok1);
void			tok1_word(t_redir *redir, t_token *tok1, t_token *token);
void			increment(t_token **tok1, t_lexer *lexer1, char **env);
int				after_pipe(t_token **tok2, t_lexer *lexer2 \
				, t_token *token, char **env);
int				help_parce(t_token **tok3, t_lexer *lexer3);
char			**hepl_split(char *s, char c, char **str, int k);
int				word_size(char const *s, char c, int start);
char			**return_null(void);
#endif
