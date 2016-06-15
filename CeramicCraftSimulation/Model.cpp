#include "stdafx.h"
#include "Model.h"


bool Model::VertToCCVert(Mesh3D* m_pmesh)
{
	clear_data();

}

HE_vert* Model::insert_rcvertex(float x, float y, float z)
{
	float r = sqrt(x*x + z*z);
	HE_vert* hv = new HE_vert(acos(x / r), r, y);
	if (vertices_list == NULL) {
		vertices_list = new VERTEX_LIST;
	}
	hv->id = (int)vertices_list->size();
	vertices_list->push_back(hv);

	return hv;
}

