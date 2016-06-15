#pragma once
#include "Mesh3D.h"

class HE_vert
{
public:
	float a, r, y;		//3d coordinates
	HE_edge* edge;		// one of the half-edges_list emanating from the vertex
	float normal[3];	// vertex normal
	int id;				// index 
	int degree;			// vertex degree
	bool tag;			// tag for programming easily
public:
	HE_vert(float _a = 0.0f, float _r = 0.0f, float _y = 0.0f)
		:a(_a), y(_y), r(_r), edge(NULL), id(-1), degree(0), tag(false)
	{}
	void ComputeRectangularCoordinates(float x[3])
	{
		x[0] = r*cos(a); x[1] = y; x[2] = -r*sin(a);
	}
};



class Model :
	public Mesh3D
{

public:
	Model();
	~Model();

	bool VertToCCVert(Mesh3D* m_pmesh);

	HE_vert* insert_vertex(float a, float r, float y);

	HE_vert* insert_rcvertex(float x, float y, float z);

	bool isborder(HE_vert* hv); //check whether the vertex is on border

};

