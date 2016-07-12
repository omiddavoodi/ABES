%{
#include <stdio.h>
#include <stdlib.h>
#include "a.tab.h"
#include <string>
#include <vector>

extern std::vector<std::string> vars;
%}

alpha [A-Za-z_]
digit [0-9]

%%
[ \t\n] 
"if" return(IF_T);
"else" return(ELSE_T);
"while" return(WHILE_T);
"var" return(VAR_T);
"print" return(PRINT_T);
"input" return(INPUT_T);
"break" return(BREAK_T);
"continue" return(CONTINUE_T);
"func" return(FUNC_T);
"proc" return(PROC_T);
"return" return(RETURN_T);
[(] return(PBAZZ);
[)] return(PBASTE);
"&" return(AND_T);
">=" return(GTE_T);
"<=" return(LTE_T);
"==" return(EQ_T);
"!=" return(NEQ_T);
">" return(GT_T);
"<" return(LT_T);
{alpha}({alpha}|{digit})* {yylval = vars.size(); vars.push_back(std::string(yytext)); return (VARNAME);};
{digit}+ {yylval = vars.size(); vars.push_back(std::string(yytext)); return(NUMBER);};
.	return yytext[0];
%%

int yywrap(void) {
	return 1;
}
