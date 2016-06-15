#pragma once
#include "Mesh3D.h"





class Model :
	public Mesh3D
{

public:
	Model();
	~Model();

	bool VertToCVert();

	bool CVertToVert();

	HE_vert* insert_vertex(float a, float r, float y);

	HE_vert* insert_rcvertex(float x, float y, float z);

	bool isborder(HE_vert* hv); //check whether the vertex is on border

};

