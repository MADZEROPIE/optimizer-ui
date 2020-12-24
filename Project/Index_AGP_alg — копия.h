#ifndef INDEX_AGP_H
#define INDEX_AGP_H
#include "stdafx.h"
#include "math_functions.h"
#include "data_structures.h"
#include "expr_cl.h"
#include "function_cl.h"
#define MAX_IT_COUNT 5000
double IndexAGP(expr* func, expr* restr, int restr_num, double a, double b, double eps, double* r);
class Index_AGP
{
	private:
		int lim, it_count, mem_step, ins_pos, v, v_max, t, restr_count, m, m_type, local_percent, alpha, stop_type;
		point *sq, result;
		double *ranks, *lip_const, *set_ranks, eps, *r, r_point, l_point, reserves, y[2];
		IndxSet **v_indexes;
		func* t_func, **restrictions;
		bool is_mem_allocated;
		int GetIndex(int pos);
		void AllocMem();
		void UpdateLipConsts(IndxSet* set);
		void UpdateRanks(bool is_local);
		void UpdateSetRanks();
	public:
		Index_AGP();
		void SetUp(func** functions, int restr_num, double a, double b, double eps, double* r_consts, double res, int map_t, int map_type, int local, int loc_pow, int stop);
		point Start(double* x_opt, int max_it_count);
		point* GetSearchInf();
		int GetSearchInfSize();
		~Index_AGP();
};
#endif
