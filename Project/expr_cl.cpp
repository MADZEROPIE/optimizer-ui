#include <string.h>
#include <cmath>
#include <stdlib.h>
#include <ctype.h>

#include "expr_cl.h"
void replace(char* dst, char* src);
expr::~expr(void)
{
	if (tmp_str != 0)
		delete[] tmp_str;
	if (exprs != 0){
		delete[] exprs;
		exprs = 0;
		size = 0;
	}
}
int expr::GetCalc_count()
{
	return calc_count;
}

expr::expr(void)
{
	size=0;
	exprs = tmp_str = 0;
}
expr::expr(const char* inp)
{
	size=calc_count=0;
	while (inp[size++]!='\0'){}
	exprs=new char[size];
	tmp_str = new char[size];
	for (int i=0; i<size; i++)
		exprs[i]=inp[i];
	convert();
}
void expr::fromch(const char* inp)
{
	size=calc_count=0;
	while (inp[size++]!='\0'){}
	if (exprs!=0)
		delete[] exprs;
	if (tmp_str != 0)
		delete[] tmp_str;
	exprs=new char[size];
	tmp_str = new char[size];
	for (int i = 0; i<size; i++)
		exprs[i]=inp[i];
	convert();
}
expr::expr(const expr& ex2)
{
	exprs=ex2.exprs;
	size=ex2.size;
	if (exprs!=0 && size!=0)
	{
		exprs=new char[size];
		tmp_str = new char[size];
		for (int i = 0; i<size; i++)
			exprs[i]=ex2.exprs[i];
		convert();
	}
	else
	{
		size=0;
		exprs=0;
	}
}
void expr::convert()
{
	char *tmp, *tmp2=exprs;
	int j=0;
	while ((tmp=strstr(exprs, "cos"))!=0)
		replace(tmp, "$  ");
	while ((tmp=strstr(exprs, "sin"))!=0)
		replace(tmp, "#  ");
	while ((tmp=strstr(exprs, "ln"))!=0)
		replace(tmp, "@ ");
	while ((tmp=strstr(exprs, "lg"))!=0)
		replace(tmp, "! ");
	while ((tmp=strstr(exprs, "tg"))!=0)
		replace(tmp, "& ");
	while ((tmp=strstr(exprs, "exp"))!=0)
		replace(tmp, "~  ");
	while ((tmp=strstr(exprs, "sh"))!=0)
		replace(tmp, "% ");
	while ((tmp=strstr(exprs, "pi"))!=0)
		replace(tmp, "p ");
	for (int i=0; i<size; i++)
		if (exprs[i]!=' ')
			tmp_str[j++] = exprs[i];
	size=j;
	j=0;
	while(j<size)
		exprs[j++] = tmp_str[j];
}
double expr::calculate(double* X)
{
	calc_count++;
	x=X[0];
	y = X[1];
	cptr=exprs;
	rez=expression();
	return rez;
}
double expr::number()
{
	char* endptr;
	double result;
	int l = 0;
	if (*cptr=='x')
	{
		cptr++;
		return x;
	}
	else if (*cptr == 'y')
	{
		cptr++;
		return y;
	}
	else
	{
		while( isdigit(*cptr) || *cptr=='-' || *cptr=='+' || *cptr=='e' || *cptr=='E' || *cptr=='.')
		{
			tmp_str[l] = *cptr;
			cptr++;
			l++;
		}
		tmp_str[l] = '\0';
		result = strtod(tmp_str, &endptr);
		while(*endptr != '\0')
		{
			l--;
			cptr--;
			tmp_str[l] = '\0';
			result = strtod(tmp_str, &endptr);
		}
	}
	return result;
}

double expr::primary()
{
   double result;
   if(*cptr=='(')
   {
      cptr++;
      result = expression();
      cptr++;
   }
   else
   {
      result = number();
   }
   return result;
}
double expr::term()
{
	double result = 0;
	result = primary();
	while(*cptr=='*' || *cptr=='/' || *cptr=='^' || *cptr=='$' || *cptr=='#' || *cptr=='@' || *cptr=='&' || *cptr=='~' || *cptr=='%' || *cptr=='!')
	{
		switch(*cptr)
		{
		case '*':
			cptr++;
			result *= term();
			break;
		case '/':
			cptr++;
			result/=term();
			break;
		case '^':
			cptr++;
			result=pow(result, number());
			//result=pow(result, primary());//!!!
		//	result = exp(primary()*log(result));
			break;
		case '$':
			cptr++;
			result=cos(primary());
			break;
		case '#':
			cptr++;
			result=sin(primary());
			break;
		case '@':
			cptr++;
			result=log(primary());
			break;
		case '!':
			cptr++;
			result=log10(primary());
			break;
		case '&':
			cptr++;
			result=tan(primary());
			break;
		case '~':
			cptr++;
			result=exp(primary());
			break;
		case '%':
			cptr++;
			result=sinh(primary());
			break;
		}
	}
	return result;
}
double expr::expression()
{
   double result = 0;
   if(*cptr=='-')
   {
       cptr++;
       result = -term();
   }
   else
   {
       if(*cptr=='+')
			cptr++;
       result = term();
   }
   while(*cptr=='+' || *cptr=='-'){
       if(*cptr=='+'){
		  cptr++;
	   result += term();
       }
       else{
	   cptr++;
	   result -= term();
       }
   }
   return result;
}
void replace(char* dst, char* src)
{
		int i=0;
		while (src[i]!='\0')
			*dst++=src[i++];
}