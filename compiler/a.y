%token IF_T ELSE_T WHILE_T VAR_T INPUT_T PRINT_T VARNAME NUMBER
%token PBAZZ PBASTE AND_T GTE_T LTE_T EQ_T NEQ_T GT_T LT_T BREAK_T CONTINUE_T
%token FUNC_T PROC_T RETURN_T
%left AND_T '|' '^'

%{
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <fstream>

struct var_block {
    std::string name;
    int stack_number;
    int block_number;
};

std::stack<std::string> whileStack;
std::stack<std::string> ifStack;
std::vector<std::string> vars;
std::vector<var_block> var_blocks;
std::vector<std::string> funcs;
std::vector<std::string> procs;

int stack_top = -1;
int block_num = 0;

int currentparamcount = 0;

std::string result = "";
std::string subendlabel = "";
std::string substartlabel = "";


int tmpNum = 0;
int labelNum = 0;

std::string newLabel()
{
	char * g = new char[15];
	itoa (++labelNum, g, 10);
	return  std::string("?L") + std::string(g);
}

void removeTemp()
{
	--tmpNum;
}

std::string newTemp()
{
	char * g = new char[15];
	itoa (++tmpNum, g, 10);
	return  std::string("#T") + std::string(g);
}

bool isTemp(std::string s)
{
	if (s[0] == '#')
		return true;
	return false;
}

bool isVar(std::string s)
{
    return (s[0] < '0' || s[0] > '9');
}

void yyerror(char *);
int yylex(void);



std::string findInStack(std::string s)
{
    if (!isVar(s))
    {
        return s;
    }
    
    for (int i = var_blocks.size() - 1; i >= 0; --i)
    {
        if (var_blocks[i].name == s)
        {
            char * g = new char[15];
            itoa (stack_top - var_blocks[i].stack_number, g, 10);
            return std::string("[") + g + "]";
        }
    }
    yyerror((char *)(std::string("Unrecognized variable name ") + s).data());
    return "-1";
}

void add_var_to_stack(std::string s)
{
    var_block newvarblock;
    newvarblock.name = s;
    ++stack_top;
    newvarblock.stack_number = stack_top;
    newvarblock.block_number = block_num;
    var_blocks.push_back(newvarblock);
}

void remove_all_stack_with_block_num(int n)
{
    int num = 0;
    
    while(var_blocks[var_blocks.size()-1].block_number == n)
    {
        ++num;
        --stack_top;
        var_blocks.pop_back();
    }
    char * g = new char[15];
    itoa (num, g, 10);
	result += std::string("pop ") + g + "\n";
    
}


extern FILE * yyin;
extern FILE *fopen(const char *filename, const char *mode);

%}

%%
p: s | s p;
s: WHILE_S | IF_S | VAR_S | ASS_S | PRINT_S | INPUT_S | FUNC_S | PROC_S | CALL_S ';';
pi: si | si pi;
si: WHILE_S | IF_S | VAR_S | ASS_S | PRINT_S | INPUT_S | CALL_S ';' | FUNC_RETURN_S | RETURN_S;
wp: ws | ws wp;
ws: WHILE_S | IF_W_S | VAR_S | ASS_S | PRINT_S | INPUT_S | BREAK_S | CONTINUE_S | CALL_S ';' | FUNC_RETURN_S | RETURN_S;
procp: procs | procs procp;
procs: WHILE_S | IF_S | VAR_S | ASS_S | PRINT_S | INPUT_S | RETURN_S | CALL_S ';';
funcp: funcs | funcs funcp;
funcs: WHILE_S | IF_S | VAR_S | ASS_S | PRINT_S | INPUT_S | FUNC_RETURN_S | CALL_S ';';

CALL_S: VARNAME 
{
    bool isFunc = false;
    
    for (int kk = 0; kk < funcs.size(); ++kk)
    {
        if (funcs[kk] == vars[$1])
        {
            isFunc = true;
            break;
        }
    }
    
    if (isFunc)
    {
        result += "push 0\n";
        
        ++stack_top;
        //std::cout << $$;
    }
}
 PBAZZ PARAMS_S PBASTE
{

    bool isFunc = false;
    
    for (int kk = 0; kk < funcs.size(); ++kk)
    {
        if (funcs[kk] == vars[$1])
        {
            isFunc = true;
            break;
        }
    }
    
    if (isFunc)
    {
        result += "push 0\n";
    }
    
    result += std::string("call ") + "?LS" + vars[$1] + "\n";
    
    
    //std::cout << $$ << " " << $1 << " " << $2 << " " << $3 << " " << $4 << " " << $5 << " ";
    
    
    if (isFunc)
    {
        //std::cout << $$;
        char * g = new char[15];
        itoa ($4+1, g, 10);
        result += std::string("[") + g + "]=[0]\n";
        result += "pop 1\n";
    }
    --stack_top;
    char * g = new char[15];
    itoa ($4, g, 10);
	result += std::string("pop ") + g + "\n";
}
;

PARAMS_S: PARAMS ',' PARAM { $$ = $1 + 1; } | PARAM { $$ = 1; } | { $$ = 0; };

PARAMS: PARAMS ',' PARAM { $$ = $1 + 1; } | PARAM { $$ = 1; };

PARAM: EXP {
	if (isVar(vars[$1]))
    {
        result += "push " + findInStack(vars[$1]) + "\n";
        if (isTemp(vars[$1]))
        {
            removeTemp();
            result += "pop 1\n";
            --stack_top;
            var_blocks.pop_back();
        }
    }
    else
    {
        result += "push " + vars[$1] + "\n";
    }
    
    
};



FUNC_S: FUNC_T VARNAME


 PBAZZ ARGS PBASTE {
    substartlabel = std::string("?LS") + vars[$2];
    subendlabel = std::string("?LE") + vars[$2];
    funcs.push_back(vars[$2]);
	result += "goto " + subendlabel + "\n";
	result += substartlabel + ":\n";
} '{'

{
    add_var_to_stack(std::string("return"));
    ++block_num;
    ++stack_top;
}
 funcp '}' 
 
 
 
 {
    
    remove_all_stack_with_block_num(block_num);
    --block_num;
    --stack_top;
    --stack_top;
    var_blocks.pop_back();
	result += "return\n";
	result += subendlabel + ":\n";
    for (int i = 0; i < currentparamcount; ++i)
    {
        --stack_top;
        var_blocks.pop_back();
    }
    currentparamcount = 0;
}

PROC_S: PROC_T VARNAME



 PBAZZ ARGS_S PBASTE {
    substartlabel = std::string("?LS") + vars[$2];
    subendlabel = std::string("?LE") + vars[$2];
    procs.push_back(vars[$2]);
    
	result += "goto " + subendlabel + "\n";
	result += substartlabel + ":\n";
} 
'{'
{
    ++block_num;
    ++stack_top;
}
 procp 
  
 '}'
 {
    remove_all_stack_with_block_num(block_num);
    --block_num;
    --stack_top;
	result += "return\n";
	result += subendlabel + ":\n";
    for (int i = 0; i < currentparamcount; ++i)
    {
        --stack_top;
        var_blocks.pop_back();
    }
    currentparamcount = 0;
};

ARGS_S: ARGS ',' ARG | ARG |;

ARGS: ARGS ',' ARG | ARG;

ARG: VARNAME {
    add_var_to_stack(vars[$1]);
    ++currentparamcount;
};

RETURN_S: RETURN_T ';' {
    int num = 0;
    
    for (int jji = var_blocks.size()-1; var_blocks[jji].block_number == block_num; --jji)
    {
        ++num;
    }
    char * g = new char[15];
    itoa (num, g, 10);
	result += std::string("pop ") + g + "\n";
    
	result += "return\n";
};

FUNC_RETURN_S: RETURN_T EXP ';' {
    if (isVar(vars[$2]))
    {
        result += findInStack("return") + "=" + findInStack(vars[$2]) + "\n";
        if (isTemp(vars[$2]))
        {
            removeTemp();
            result += "pop 1\n";
            --stack_top;
            var_blocks.pop_back();
        }
    }
    else
    {
        result += findInStack("return") + "=" + vars[$2] + "\n";
    }
    int num = 0;
    
    for (int jji = var_blocks.size()-1; var_blocks[jji].block_number == block_num; --jji)
    {
        ++num;
    }
    char * g = new char[15];
    itoa (num, g, 10);
	result += std::string("pop ") + g + "\n";
    
	result += "return\n";
    
};

BREAK_S: BREAK_T ';' {
	std::string w_end = whileStack.top();

	result += "goto " + w_end + "_POPS\n";
};


CONTINUE_S: CONTINUE_T ';' {
	std::string w_end = whileStack.top();
	whileStack.pop();
	std::string w_beginning = whileStack.top();
	whileStack.push(w_end);
	result += "goto " + w_beginning + "\n";
};


PRINT_S: PRINT_T VARNAME ';' { 

result += "print " + findInStack(vars[$2]) + "\n";

};
INPUT_S: INPUT_T VARNAME ';' { result += "input " + findInStack(vars[$2]) + "\n";};

IF_S: IF_T PBAZZ EXP PBASTE {
	std::string w_globalend = newLabel();
	ifStack.push(w_globalend);
	std::string w_end = newLabel();
	ifStack.push(w_end);
	if (isTemp(vars[$3]))
	{
        result += "if not " + findInStack(vars[$3]) + " pop goto " + w_end + "\n";
		removeTemp();
        --stack_top;
        var_blocks.pop_back();
    }
    else
    {
        result += "if not " + findInStack(vars[$3]) + " goto " + w_end + "\n";
    }
}
'{' 
{
    ++block_num;
}


pi




 '}' {
	std::string w_end = ifStack.top();
	ifStack.pop();
    remove_all_stack_with_block_num(block_num);
    --block_num;
	result += "goto " + ifStack.top() + "\n";
	result += w_end + ":\n";
} ELSEIF_ST;


ELSEIF_ST: ELSE_T IF_T PBAZZ EXP PBASTE {
	std::string w_end = newLabel();
	ifStack.push(w_end);
	if (isTemp(vars[$4]))
	{
        result += "if not " + findInStack(vars[$4]) + " pop goto " + w_end + "\n";
		removeTemp();
        --stack_top;
        var_blocks.pop_back();
    }
    else
    {
        result += "if not " + findInStack(vars[$4]) + " goto " + w_end + "\n";
    }
}
'{'
{
    ++block_num;
}


 pi




 '}' {
	std::string w_end = ifStack.top();
	ifStack.pop();
    remove_all_stack_with_block_num(block_num);
    --block_num;
	result += "goto " + ifStack.top() + "\n";
	result += w_end + ":\n";
    
    
} ELSEIF_ST
| ELSE_ST 
| {
	std::string w_gend = ifStack.top();
	ifStack.pop();
	result += w_gend + ":\n";
};
ELSE_ST: ELSE_T
'{'
{
    ++block_num;
}


 pi




 '}' {
	std::string w_end = ifStack.top();
	ifStack.pop();
    remove_all_stack_with_block_num(block_num);
    --block_num;
	result += w_end + ":\n";
};






IF_W_S: IF_T PBAZZ EXP PBASTE {
	std::string w_globalend = newLabel();
	ifStack.push(w_globalend);
	std::string w_end = newLabel();
	ifStack.push(w_end);
	if (isTemp(vars[$3]))
	{
        result += "if not " + findInStack(vars[$3]) + " pop goto " + w_end + "\n";
		removeTemp();
        --stack_top;
        var_blocks.pop_back();
    }
    else
    {
        result += "if not " + findInStack(vars[$3]) + " goto " + w_end + "\n";
    }
}
'{'
{
    ++block_num;
}


 wp 
 
 
 
 
 '}' {
	std::string w_end = ifStack.top();
	ifStack.pop();
    remove_all_stack_with_block_num(block_num);
    --block_num;
	result += "goto " + ifStack.top() + "\n";
	result += w_end + ":\n";
    
    
} ELSEIF_W_ST;
ELSEIF_W_ST: ELSE_T IF_T PBAZZ EXP PBASTE {
	std::string w_end = newLabel();
	ifStack.push(w_end);
	if (isTemp(vars[$4]))
	{
        result += "if not " + findInStack(vars[$4]) + " pop goto " + w_end + "\n";
		removeTemp();
        --stack_top;
        var_blocks.pop_back();
    }
    else
    {
        result += "if not " + findInStack(vars[$4]) + " goto " + w_end + "\n";
    }
}
'{'
{
    ++block_num;
}


 wp




 '}' {
	std::string w_end = ifStack.top();
	ifStack.pop();
    remove_all_stack_with_block_num(block_num);
    --block_num;
	result += "goto " + ifStack.top() + "\n";
	result += w_end + ":\n";
    
    
} ELSEIF_W_ST
| ELSE_W_ST 
| {
	std::string w_gend = ifStack.top();
	ifStack.pop();
	result += w_gend + ":\n";
};
ELSE_W_ST: ELSE_T
'{'
{
    ++block_num;
}


 wp


 

 '}' {
	std::string w_end = ifStack.top();
	ifStack.pop();
    remove_all_stack_with_block_num(block_num);
    --block_num;
	result += w_end + ":\n";
};



WHILE_S: WHILE_T {
	std::string w_start = newLabel();
	std::string w_end = newLabel();
	whileStack.push(w_start);
	whileStack.push(w_end);
	result += w_start + ":\n";
}
PBAZZ EXP PBASTE {
    //std::cout << vars[$1] << " " << vars[$2] << " " << vars[$3] << " " << vars[$4] ;
	std::string w_end = whileStack.top();
	whileStack.pop();
	std::string w_start = whileStack.top();
	whileStack.push(w_end);
	
	if (isTemp(vars[$4]))
	{
        result += "if not " + findInStack(vars[$4]) + " pop goto " + w_end + "\n";
		removeTemp();
        --stack_top;
        var_blocks.pop_back();
    }
    else
    {
        result += "if not " + findInStack(vars[$4]) + " goto " + w_end + "\n";
    }
}
'{'
{
    ++block_num;
}


 wp



 '}' {
	std::string w_end = whileStack.top();
	whileStack.pop();
	std::string w_start = whileStack.top();
	result += "goto " + w_start + "\n";
    result += w_end + "_POPS:";
	remove_all_stack_with_block_num(block_num);
    --block_num;
	result += w_end + ":\n";
	whileStack.pop();
};

ASS_S: VARNAME '=' EXP ';' {
    if (isVar(vars[$3]))
    {
        result += findInStack(vars[$1]) + "=" + findInStack(vars[$3]) + "\n";
        if (isTemp(vars[$3]))
        {
            removeTemp();
            result += "pop 1\n";
            --stack_top;
            var_blocks.pop_back();
        }
    }
    else
    {
        result += findInStack(vars[$1]) + "=" + vars[$3] + "\n";
    }
};

VAR_S: VAR_T VARNAME ';' 
{
    result += "push 0\n";
    add_var_to_stack(vars[$2]);
    
}

| VAR_T VARNAME '=' EXP ';' {
    
	if (isTemp(vars[$4]))
    {
		removeTemp();
        var_blocks[var_blocks.size()-1].name = vars[$2];
    }
    else if (isVar(vars[$4]))
    {
        result += "push 0\n";
        add_var_to_stack(vars[$2]);
        result += findInStack(vars[$2]) + "=" + findInStack(vars[$4]) + "\n";
        ++stack_top;
	}
    else
    {
        result += "push 0\n";
        add_var_to_stack(vars[$2]);
        
        result += findInStack(vars[$2]) + "=" + vars[$4] + "\n";
    }
    
};
    
EXP: 
EXP AND_T EXP {
	std::string q = vars[$3];
	if (isTemp(vars[$1]))
	{
		$$ = $1;
		if (isTemp(vars[$3]))
		{
			vars.erase(vars.begin() + $3);
			removeTemp();
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "&" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "&" + findInStack(q) + "\n";
        }
        
	}
	else if (isTemp(vars[$3]))
	{
		$$ = $3;
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "&" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		$$ = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "&" + findInStack(q) + "\n";
	}
	
	//std::cout << "AND:" << vars[$1] << "," << q << std::endl;
	}

| EXP '|' EXP {
	std::string q = vars[$3];
	if (isTemp(vars[$1]))
	{
		$$ = $1;
		if (isTemp(vars[$3]))
		{
			vars.erase(vars.begin() + $3);
			removeTemp();
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "|" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "|" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[$3]))
	{
		$$ = $3;
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "|" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		$$ = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "|" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	}
| EXP '^' EXP {
	std::string q = vars[$3];
	if (isTemp(vars[$1]))
	{
		$$ = $1;
		if (isTemp(vars[$3]))
		{
			vars.erase(vars.begin() + $3);
			removeTemp();
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "^" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "^" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[$3]))
	{
		$$ = $3;
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "^" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		$$ = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "^" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	}
| EXP1 { $$ = $1; };

EXP1: EXP1 GT_T EXP2 {
	std::string q = vars[$3];
	if (isTemp(vars[$1]))
	{
		$$ = $1;
		if (isTemp(vars[$3]))
		{
			vars.erase(vars.begin() + $3);
			removeTemp();
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + ">" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + ">" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[$3]))
	{
		$$ = $3;
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + ">" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		$$ = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + ">" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	}
| EXP1 LT_T EXP2 {
	std::string q = vars[$3];
	if (isTemp(vars[$1]))
	{
		$$ = $1;
		if (isTemp(vars[$3]))
		{
			vars.erase(vars.begin() + $3);
			removeTemp();
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "<" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "<" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[$3]))
	{
		$$ = $3;
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "<" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		$$ = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "<" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	}
| EXP1 LTE_T EXP2 {
	std::string q = vars[$3];
	if (isTemp(vars[$1]))
	{
		$$ = $1;
		if (isTemp(vars[$3]))
		{
			vars.erase(vars.begin() + $3);
			removeTemp();
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "<=" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "<=" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[$3]))
	{
		$$ = $3;
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "<=" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		$$ = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "<=" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	}
| EXP1 GTE_T EXP2 {
	std::string q = vars[$3];
	if (isTemp(vars[$1]))
	{
		$$ = $1;
		if (isTemp(vars[$3]))
		{
			vars.erase(vars.begin() + $3);
			removeTemp();
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + ">=" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + ">=" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[$3]))
	{
		$$ = $3;
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + ">=" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		$$ = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + ">=" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	}
| EXP1 EQ_T EXP2 {
	std::string q = vars[$3];
	if (isTemp(vars[$1]))
	{
		$$ = $1;
		if (isTemp(vars[$3]))
		{
			vars.erase(vars.begin() + $3);
			removeTemp();
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "==" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "==" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[$3]))
	{
		$$ = $3;
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "==" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		$$ = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "==" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	}
| EXP1 NEQ_T EXP2 {
	std::string q = vars[$3];
	if (isTemp(vars[$1]))
	{
		$$ = $1;
		if (isTemp(vars[$3]))
		{
			vars.erase(vars.begin() + $3);
			removeTemp();
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "!=" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "!=" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[$3]))
	{
		$$ = $3;
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "!=" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		$$ = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "!=" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	}
| EXP2 { $$ = $1; };

EXP2: EXP2 '+' EXP3 {
	std::string q = vars[$3];
	if (isTemp(vars[$1]))
	{
		$$ = $1;
		if (isTemp(vars[$3]))
		{
			vars.erase(vars.begin() + $3);
			removeTemp();
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "+" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "+" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[$3]))
	{
		$$ = $3;
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "+" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		$$ = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "+" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	}
| EXP2 '-' EXP3 {
	std::string q = vars[$3];
	if (isTemp(vars[$1]))
	{
		$$ = $1;
		if (isTemp(vars[$3]))
		{
			vars.erase(vars.begin() + $3);
			removeTemp();
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "-" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "-" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[$3]))
	{
		$$ = $3;
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "-" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		$$ = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "-" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	}
| EXP3 { $$ = $1; };

EXP3: EXP3 '*' EXP4 {
	std::string q = vars[$3];
	if (isTemp(vars[$1]))
	{
		$$ = $1;
		if (isTemp(vars[$3]))
		{
			vars.erase(vars.begin() + $3);
			removeTemp();
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "*" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "*" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[$3]))
	{
		$$ = $3;
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "*" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		$$ = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "*" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	}
| EXP3 '/' EXP4 {
	std::string q = vars[$3];
	if (isTemp(vars[$1]))
	{
		$$ = $1;
		if (isTemp(vars[$3]))
		{
			vars.erase(vars.begin() + $3);
			removeTemp();
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "/" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "/" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[$3]))
	{
		$$ = $3;
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "/" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		$$ = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "/" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	}
| EXP3 '%' EXP4 {
	std::string q = vars[$3];
	if (isTemp(vars[$1]))
	{
		$$ = $1;
		if (isTemp(vars[$3]))
		{
			vars.erase(vars.begin() + $3);
			removeTemp();
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "%" + findInStack(q) + "\n";
            result += "pop 1\n";
            --stack_top;
            
		}
        else
        {
            result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "%" + findInStack(q) + "\n";
        }
	}
	else if (isTemp(vars[$3]))
	{
		$$ = $3;
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "%" + findInStack(q) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		$$ = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
        result += findInStack(vars[$$]) + "=" + findInStack(vars[$1]) + "%" + findInStack(q) + "\n";
	}
    
	//std::cout << "OR:" << vars[$1] << "," << q << std::endl;
	}
| EXP4 { $$ = $1; }
| '!' EXP4  {
	if (isTemp(vars[$2]))
	{
		$$ = $2;
        result += std::string("~") + findInStack(vars[$$]) + "\n";
	}
	else
	{
		std::string nt = newTemp();
		$$ = vars.size();
		vars.push_back(nt);
        add_var_to_stack(nt);
        result += "push 0\n";
		result += findInStack(vars[$$]) + "=" + findInStack(vars[$2]) + "\n";
        
        result += std::string("~") + findInStack(vars[$$]) + "\n";
	}
	
	//std::cout << "NOT:" << vars[$1] << std::endl;
};

EXP4: CALL_S { 

std::string nt = newTemp();
$$ = vars.size();
vars.push_back(nt);
add_var_to_stack(nt);

} | EXP5 { $$ = $1; } ;
EXP5: VARNAME { $$ = $1; }
| NUMBER  { $$ = $1; }
| PBAZZ EXP PBASTE { $$ = $2; }

;


%%
void yyerror(char *s) {
	fprintf(stderr, "%s\n", s);
}
int main(int argc, char *argv[])
{
//	yylex();
	if (argc > 2)
	{
		yyin = fopen(argv[1], "r");
		std::ofstream myfile;
		myfile.open(argv[2]);
		yyparse();
		myfile << result;
		myfile.close();
		fclose(yyin);
	}
    else if (argc == 2)
    {
        yyin = fopen(argv[1], "r");
        yyparse();
        std::cout << result;
    }
	else
	{
		yyparse();
		std::cout << result;
	}
	
	return 0;
}