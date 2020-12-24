#ifndef EXPR_CL_H
#define EXPR_CL_H
//#include "function_cl.h"
class expr //: public func
{
	private:
		char* exprs, *tmp_str;
		int size, calc_count;
		double rez, x, y;
		char* cptr;
	public:
		expr(void);
		expr(const char* inp);
		expr(const expr& ex2);
		void fromch(const char* inp);
		~expr(void);
		virtual double calculate(double *x);
		int GetCalc_count();
	private:
		void convert();
		double number();
		double primary();
		double term();
		double expression();
};
#endif