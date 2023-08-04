#ifndef PARSER_H
#define PARSER_H

#include "../include/lexer.h"

typedef struct s_cmd
{
	SymTok			type;
	char			**cmd;
	char			**input;
	char			**output;
	char			**outapp;
	struct s_cmd	*next;
}	t_cmd;

char *pars_expan(t_lexer *data, char **env);

#endif
