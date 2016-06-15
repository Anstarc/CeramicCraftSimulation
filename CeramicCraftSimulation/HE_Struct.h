#pragma once
#include <math.h>

class HE_vert;
class HE_face;
class HE_edge;

class HE_vert
{
public:
	float x, y, z;		//3d coordinates
	HE_edge* edge;		// one of the half-edges_list emanating from the vertex
	float normal[3];	// vertex normal
	int id;				// index 
	int degree;			// vertex degree
	bool tag;			// tag for programming easily
public:
	HE_vert(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
		:x(_x), y(_y), z(_z), edge(NULL), id(-1), degree(0), tag(false)
	{}
	void RC_To_CC()
	{
		float r=sqrt(x*x + z*z);
		float a = acos(x / r);
		x = a; z = r;
	}
	void CC_To_RC()
	{
		float x1 = z*cos(x);
		float z1 = -z*sin(x);
		x = x1; z = z1;
	}

};

class HE_edge
{
public:
	HE_vert* vert;   // vertex at the end of the half-edge
	HE_edge* pair;   // oppositely oriented adjacent half-edge 
	HE_face* face;   // face the half-edge borders
	HE_edge* next;   // next half-edge around the face
	int id;			 // index
	bool tag;		 // tag for programming easily
public:
	HE_edge()
		:vert(NULL), pair(NULL), face(NULL), next(NULL), id(-1), tag(false)
	{  }
};

class HE_face
{
public:
	HE_edge* edge;		// one of the half-edges_list bordering the face	
	int valence;		// the number of edges_list 
	float normal[3];	// face normal
	int id;				// index
	bool tag;           // tag for programming easily
public:
	HE_face()
		:edge(NULL), id(-1), tag(false)
	{}

};
