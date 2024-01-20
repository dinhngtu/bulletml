/* ï¾ƒè±¢ï¾–ï½µï½­ï¾‹ï½¡ï¾…ï¾…ï¾‚
typedef double NumType;

#define YYSTYPE double
#define YYERROR_VERBOSE

#include <cmath>
#include <cctype>

#include <vector>
#include <sstream>

#include "calc.h"
#include "formula.h"
#include "formula-variables.h"

int yyerror(char* s);
int yylex();

const char* yyinStr;

typedef Formula<NumType> CalcFormula;
typedef Number<NumType> CalcNumber;
typedef Random<NumType> CalcRandom;
typedef Rank<NumType> CalcRank;
typedef Param<NumType> CalcParam;
typedef Operator CalcOperator;

namespace {
	CalcFormula* formula;
	std::vector<CalcFormula*> formulas;

	CalcFormula* f(double d) { return formulas[(int)d]; }

	int paramId;
}

%}

/* BISONÀë¸À */
%token NUM RAND RANK PARAM
%left '-' '+'
%left '*' '/'
%left NEG     /* negation--Ã±¹à¥Ş¥¤¥Ê¥¹ */
%right '^'    /* ¤Ù¤­¾è´Ø¿ô        */

/* Ê¸Ë¡µ¬Â§¤¬Â³¤¯ */
%%
input:    /* ¶õÊ¸»úÎó */
        | input line
;

line:     '\n'
| exp '\n'  { formula = f($1); return 0; }
;

exp:    NUM {
	        $$ = formulas.size();
	        formulas.push_back(new CalcFormula(new CalcNumber($1)));
        }
        | RAND {
	        $$ = formulas.size();
            formulas.push_back(new CalcFormula(new CalcRandom()));
        }
        | RANK {
			$$ = formulas.size();
			formulas.push_back(new CalcFormula(new CalcRank()));
		}
        | PARAM {
			$$ = formulas.size();
			formulas.push_back(new CalcFormula(new CalcParam(paramId)));
		}
        | exp '+' exp {
		    $$ = formulas.size();
			formulas.push_back(new CalcFormula(f($1), op_add, f($3)));
		}
        | exp '-' exp {
		    $$ = formulas.size();
			formulas.push_back(new CalcFormula(f($1), op_sub, f($3)));
		}
        | exp '*' exp {
		    $$ = formulas.size();
			formulas.push_back(new CalcFormula(f($1), op_mul, f($3)));
		}
        | exp '/' exp {
		    $$ = formulas.size();
			formulas.push_back(new CalcFormula(f($1), op_div, f($3)));
		}
        | '-' exp  %prec NEG {
		    $$ = $2;
			f($2)->setHeadSub();
		}
        | '(' exp ')' {
		    $$ = $2;
		}
;
%%

/**
 * »ú¶ç²òÀÏ´ï¤Ï¡¢¿ôÃÍ¤òÆÉ¤á¤Ğ¡¢double·¿¤ÎÃÍ¤ò¥¹¥¿¥Ã¥¯¤ËÀÑ¤ó¤Ç
 * ¥È¡¼¥¯¥ó¡ÖNUM¡×¤òÊÖ¤·¡¢¿ôÃÍ°Ê³°¤òÆÉ¤á¤Ğ¡¢¤½¤ÎÊ¸»ú¤Î¥¢¥¹¥­¡¼Éä¹æ¤òÊÖ¤¹¡£
 * ¶õÇò¤È¥¿¥Ö¤ÏÆÉ¤ßÈô¤Ğ¤µ¤ì¤ë¡£¥Õ¥¡¥¤¥ë¤¬½ª¤ï¤ë¤È0¤òÊÖ¤¹¡£
 */

#include <ctype.h>
#include <stdio.h>

int yylex ()
{
	int c;

	/* ¶õÇòÎà¤òÆÉ¤ßÈô¤Ğ¤¹  */
	while ((c = *(yyinStr++)) == ' ' || c == '\t')
		;
	/* ¿ôÃÍ¤ò½èÍı¤¹¤ë   */
	if (c == '.' || isdigit (c))
    {
		yyinStr--;
		sscanf (yyinStr, "%lf", &yylval);
		while ((c = *(++yyinStr)) == '.' || isdigit(c)) {}
		return NUM;
    }

	// ÊÑ¿ô¤ò½èÍı¤¹¤ë */
	if (c == '$') {
		if (strncmp(yyinStr, "rand", 4) == 0) {
			yyinStr += 4;
			return RAND;
		}
		else if (strncmp(yyinStr, "rank", 4) == 0) {
		    yyinStr += 4;
			return RANK;
        }
		else {
			std::istringstream iss(std::string(yyinStr).substr(0, 1));
			iss >> paramId;
			yyinStr++;
			return PARAM;
		}
	}

	/* ¥Õ¥¡¥¤¥ë¤Î½ª¤ï¤ê¤ò½èÍı¤¹¤ë  */
	if (c == '\0')
		return 0;
	/* 1Ê¸»ú¤òÊÖ¤¹ */
	return c;
}

int yyerror(char* s) {
	printf("yyerror: %s\n", s);
	return 0;
}

std::auto_ptr<CalcFormula> calc(const std::string& str) {
	std::string fml = str + '\n';
	yyinStr = fml.c_str();
	yyparse();
	return std::auto_ptr<CalcFormula>(formula);
}

