#include "stdafx.h"
#include "Index_AGP_alg.h"
#include "data_structures.h"
#include "math_functions.h"
#include "Map.h"
#include <math.h>
//using namespace System;
double map_norm(double a, double b, int m_type)
{
	double x[2], y[2];
	mapd(a, 12, y, 2, m_type);
	mapd(b, 12, x, 2, m_type);
	return dmax(dabs(y[0] - x[0]), dabs(y[1] - x[1]));
}
template<class T>
int re_alloc(T **ptr, int cur_size, int step)
{
	T *tmp=new T[cur_size+step];
	if(tmp!=NULL)
	{
		for (int i=0; i<cur_size; i++)
			tmp[i]=(*ptr)[i];
		delete[] *ptr;
		*ptr=tmp;
		return 1;
	}
	return 0;
}
Index_AGP::Index_AGP() : lim(1100), mem_step(1000), r(0), is_mem_allocated(false)
{}
double norm_2d(double *x, double* y)
{
	return dmax(dabs(y[0] - x[0]), dabs(y[1] - x[1]));
}
int Index_AGP::GetSearchInfSize()
{
	return it_count;
}
void Index_AGP::SetUp(func** functions, int restr_num, double a, double b, double prec, double* r_consts, double res, int map, int map_type, int local, int loc_pow, int stop)
{
	stop_type = stop;
	alpha = loc_pow;
	t_func=functions[restr_num];
	restrictions=functions;
	restr_count=restr_num;
	reserves = res;
	eps = prec;
	r_point = a;
	l_point = b;
	t = 0;
	local_percent = (int)local/10.0;
	m = map;
	if (map_type > 0 && map_type < 4)
		m_type = map_type;
	else
		m_type = 1;
	v_max = v = 1;
	if (r)
		delete[] r;
	r = new double[restr_count + 1];
	for (int i = 0; i < restr_count + 1; i++)
		r[i] = r_consts[i];
}
point Index_AGP::Start(double* a, int max_it_count)
{
	if (!is_mem_allocated){
		AllocMem();
		is_mem_allocated = true;
	}
	int it_type;
	double preimages[4], val;
	int p_count = 0, i_count=0;
	sq[0].x = r_point;
	sq[1].x = l_point;
	sq[0].v = sq[1].v = 0;
	sq[2].x = (r_point + l_point) / 3;
	mapd(sq[2].x, m, y, 2, m_type);

	//for (it_count = 2; i_count < max_it_count && norm_2d(y, a) > eps; it_count++)
	for (it_count = 2; i_count < max_it_count; it_count++)
	{
		if (stop_type == 0 && norm_2d(y, a) < eps)
			break;
		else if (map_norm(sq[t + 1].x, sq[t].x, m_type) < eps / 10)
			break;
		v = GetIndex(it_count);
		sq[it_count].v = v;
		if (m_type == 3)
		{
			invmad(m, preimages, 4, &p_count, y, 2, 1);
			i_count++;
			val = sq[it_count].val;
			for (int i = 0; i < p_count; i++)
			{
				sq[it_count + i].v = v;
				sq[it_count + i].val = val;
				sq[it_count + i].x = preimages[i];
				ins_pos = sort(sq, it_count + i + 1);
				UpdateLipConsts(v_indexes[v - 1]);
				v_indexes[v - 1]->Add(sq[ins_pos]);
			}
			it_count += p_count - 1;
		}
		else
		{
			i_count = it_count;
			ins_pos = sort(sq, it_count + 1);
			UpdateLipConsts(v_indexes[v - 1]);
			v_indexes[v - 1]->Add(sq[ins_pos]);
		}
		//////
//		if (v_indexes[v - 1]->GetSize() > 20)
//			r[v - 1] = 2;
		//////////
		//v_indexes[v-1]->Add(sq[ins_pos]);

		if (v > v_max)
		{
			for (int i = 0; i < v - 1; i++)
				set_ranks[i] = -reserves*lip_const[i];
			v_max = v;
		}
	//	UpdateLipConsts(v_indexes[v - 1]);
	//	v_indexes[v - 1]->Add(sq[ins_pos]);
		if (v == v_max)
			set_ranks[v - 1] = v_indexes[v - 1]->find_min_val();

		it_type = (int)fmod(it_count, (double)(11 - local_percent));
		if (it_type == 0 && local_percent && it_count>100)
			UpdateRanks(true);
		else
			UpdateRanks(false);

		if (sq[t + 1].x == sq[t].x)
		{
			sq[it_count] = sq[t + 1];
			mapd(sq[it_count].x, m, y, 2, m_type);
			break;
		}

		if (sq[t].v == sq[t + 1].v)
			sq[it_count + 1].x = (sq[t + 1].x + sq[t].x) / 2 - sgn(sq[t + 1].val - sq[t].val)*square((sq[t + 1].val - sq[t].val) / lip_const[sq[t].v - 1]) / (2 * r[sq[t].v - 1]);
		else
			sq[it_count + 1].x = (sq[t + 1].x + sq[t].x) / 2;

		mapd(sq[it_count + 1].x, m, y, 2, m_type);

		if (it_count > lim - 50)
		{
			re_alloc(&sq, lim, mem_step);
		//	re_alloc(&ranks, lim, mem_step);
			lim += mem_step;
		}
	}
	result = sq[it_count];
	result.val = t_func->calculate(y);
	if (stop_type!=0)
	for (int i = 0; i < it_count; i++)
		if (sq[i].val < result.val)
			result = sq[i];
	if (m_type == 3)
		result.v = i_count;
	else
		result.v = it_count;

	for (int j = 0; j < restr_count + 1; j++)
		v_indexes[j]->Reset();

	set_ranks[0] = 0;
	lip_const[0] = 1;
	return result;
}
Index_AGP::~Index_AGP(){
	if (r)
		delete[] r;
	if (is_mem_allocated)
	{
	//	delete[] ranks;
		delete[] sq;
		delete[] lip_const;
		delete[] set_ranks;
		for (int j = 0; j < restr_count + 1; j++)
			delete v_indexes[j];
		delete[] v_indexes;
	}
}
void Index_AGP::UpdateLipConsts(IndxSet* set)
{
	double max = lip_const[v - 1], tmp;
	int set_size = set->GetSize();
	point cur_point;

	for(int k=0; k<set_size; k++)
	{
		cur_point=set->Get(k);
		if (sq[ins_pos].x != cur_point.x)
		{
			tmp = dabs(sq[ins_pos].val - cur_point.val) / sqrt(dabs(sq[ins_pos].x - cur_point.x));
			if (max < tmp)
				max = tmp;
		}
	}
	if (max != 0)
		lip_const[v - 1] = max;
	else
		lip_const[v-1]=1;
		
}
void Index_AGP::UpdateRanks(bool is_local)
{
	double dx, max=-HUGE_VAL, rank_j;
	for(int j=0; j<it_count; j++)
	{
		dx = sqrt(dabs(sq[j + 1].x - sq[j].x));
		if (dx == 0)
		{
			t = j;
			break;
		}
		if(sq[j+1].v==sq[j].v)
			rank_j=dx+square((sq[j+1].val-sq[j].val)/(r[sq[j].v-1]*lip_const[sq[j].v-1]))/dx-2*(sq[j+1].val+sq[j].val-2*set_ranks[sq[j].v-1])/(r[sq[j].v-1]*lip_const[sq[j].v-1]);
		else if(sq[j+1].v>sq[j].v)
			rank_j =2*dx-4*(sq[j+1].val-set_ranks[sq[j+1].v-1])/(r[sq[j+1].v-1]*lip_const[sq[j+1].v-1]);
		else if(sq[j+1].v<sq[j].v)
			rank_j=2*dx-4*(sq[j].val-set_ranks[sq[j].v-1])/(r[sq[j].v-1]*lip_const[sq[j].v-1]);
		

		if (is_local)
		{
			if (sq[j + 1].v == sq[j].v)
				rank_j /= sqrt((sq[j + 1].x - set_ranks[sq[j + 1].v - 1])*(sq[j].x - set_ranks[sq[j + 1].v - 1])) / lip_const[sq[j + 1].v - 1] + pow(1.5, -alpha);
			else if (sq[j + 1].v>sq[j].v)
				rank_j /= (sq[j + 1].x - set_ranks[sq[j + 1].v - 1]) / lip_const[sq[j + 1].v - 1] + pow(1.5, -alpha);
			else if (sq[j + 1].v<sq[j].v)
				rank_j /= (sq[j].x - set_ranks[sq[j].v - 1]) / lip_const[sq[j].v - 1] + pow(1.5, -alpha);
		}
		if (rank_j>max)
		{
			max = rank_j;
			t = j;
		}
	}
}
void Index_AGP::UpdateSetRanks()
{
	if (v_indexes[v - 1]->GetSize() > 1)
	{
		if (set_ranks[v - 1] > sq[ins_pos].val)
			set_ranks[v - 1] = sq[ins_pos].val;
	}
	else
		set_ranks[v - 1] = v_indexes[v - 1]->Get(0).val;
}
int Index_AGP::GetIndex(int pos)
{
	int indx=1;
	for(int j=0; j<restr_count; j++)
	{
		sq[pos].val = restrictions[j]->calculate(y);
		if ( sq[pos].val>0 )
			break;
		else
			indx++;
	}
	if (indx==restr_count+1)
		sq[pos].val=t_func->calculate(y);
	return indx;
}
void Index_AGP::AllocMem()
{
	sq=new point[lim];
//	ranks=new double[lim];
	lip_const=new double[restr_count+1];
	set_ranks=new double[restr_count+1];
	v_indexes=new IndxSet*[restr_count+1];

	for(int j=0; j<restr_count+1; j++)
	{
		set_ranks[j]=0;
		lip_const[j]=1;
		v_indexes[j]=new IndxSet(lim, mem_step);
	}
}
point* Index_AGP::GetSearchInf()
{
	return sq;
}
/*
void Index_AGP::UpdateRanks(bool is_local)
{
	double dx, max = -HUGE_VAL, rank_j;
	for (int j = 0; j<it_count; j++)
	{
		dx = sqrt(dabs(sq[j + 1].x - sq[j].x));
		if (dx == 0)
		{
			t = j;
			break;
		}
		if (sq[j + 1].v == sq[j].v)
			ranks[j] = dx + square((sq[j + 1].val - sq[j].val) / (r[sq[j].v - 1] * lip_const[sq[j].v - 1])) / dx - 2 * (sq[j + 1].val + sq[j].val - 2 * set_ranks[sq[j].v - 1]) / (r[sq[j].v - 1] * lip_const[sq[j].v - 1]);
		else if (sq[j + 1].v>sq[j].v)
			ranks[j] = 2 * dx - 4 * (sq[j + 1].val - set_ranks[sq[j + 1].v - 1]) / (r[sq[j + 1].v - 1] * lip_const[sq[j + 1].v - 1]);
		else if (sq[j + 1].v<sq[j].v)
			ranks[j] = 2 * dx - 4 * (sq[j].val - set_ranks[sq[j].v - 1]) / (r[sq[j].v - 1] * lip_const[sq[j].v - 1]);


		if (is_local)
		{
			if (sq[j + 1].v == sq[j].v)
				ranks[j] /= sqrt((sq[j + 1].x - set_ranks[sq[j + 1].v - 1])*(sq[j].x - set_ranks[sq[j + 1].v - 1])) / lip_const[sq[j + 1].v - 1] + pow(1.5, -alpha);
			else if (sq[j + 1].v>sq[j].v)
				ranks[j] /= (sq[j + 1].x - set_ranks[sq[j + 1].v - 1]) / lip_const[sq[j + 1].v - 1] + pow(1.5, -alpha);
			else if (sq[j + 1].v < sq[j].v)
				ranks[j] /= (sq[j].x - set_ranks[sq[j].v - 1]) / lip_const[sq[j].v - 1] + pow(1.5, -alpha);
		}
		if (ranks[j] > max)
		{
			max = ranks[j];
			t = j;
		}
	}
	}*/