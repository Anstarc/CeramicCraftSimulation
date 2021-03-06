#pragma once

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include "../HLBFGS/HLBFGS.h"

#include "OptimizationParameter.h"


class MeshOptimization
{

public:

	static void Optimize_by_HLBFGS(int N, double *init_x, int num_iter, int M, int T, bool with_hessian);
	static void Init();
	static void evalfunc(int N, double* x, double *prev_x, double* f, double* g);
	static void newiteration(int iter, int call_iter, double *x, double* f, double *g, double* gnorm);
	static void evalfunc_h(int N, double *x, double *prev_x, double *f, double *g, HESSIAN_MATRIX& hessian);
	static void UpdateMesh(double* x);

	static OptimizeParameter* opp;
	static VERTEX_LIST vertex_list;

};