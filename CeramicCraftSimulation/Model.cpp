#include "stdafx.h"
#include "Model.h"


bool Model::VertToCVert()
{

	for (VERTEX_ITER viter = vertices_list->begin(); viter != vertices_list->end(); viter++)
	{
		//(*viter)->RC_To_CC();
	}
	return true;
}


bool Model::CVertToVert()
{
	for (VERTEX_ITER viter = vertices_list->begin(); viter != vertices_list->end(); viter++)
	{
		//(*viter)->CC_To_RC();
	}
	return true;
}