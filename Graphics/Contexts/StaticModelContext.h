/*
	MilkshapeModel.h

		Loads and renders a Milkshape3D model.

	Author:	Brett Porter
	Email: brettporter@yahoo.com
	Website: http://www.geocities.com/brettporter/
	Copyright (C)2000, Brett Porter. All Rights Reserved.

	This file may be used only as long as this copyright notice remains intact.
*/

#ifndef MILKSHAPEMODEL_H
#define MILKSHAPEMODEL_H

#include <Graphics/Contexts/GraphicalContext.h>
class TextureContext;

class StaticModelContext: public GraphicalContext
{
	public:
		StaticModelContext(const char* _name = nullptr);
		virtual ~StaticModelContext();
		void draw();
		void load();
		void unload();
		void bind();

    private:
        void destroyContent();
		bool loadModelData( const char *filename );
		unsigned int list;

		// Use this to record the drawing function
		struct Mesh
		{
			int m_materialIndex;
			int m_numTriangles;
			int *m_pTriangleIndices;
		};

		//	Material properties
		struct Material
		{
			float m_ambient[4], m_diffuse[4], m_specular[4], m_emissive[4];
			float m_shininess;
			TextureContext* mTextureContext;
		};

		//	Triangle structure
		struct Triangle
		{
			float m_vertexNormals[3][3];
			float m_s[3], m_t[3];
			int m_vertexIndices[3];
		};

		//	Vertex structure
		struct Vertex
		{
			char m_boneID;	// for skeletal animation
			float m_location[3];
		};

		unsigned int record();

		//	Meshes used
		int m_numMeshes;
		Mesh *m_pMeshes;

		//	Materials used
		int m_numMaterials;
		Material *m_pMaterials;

		//	Triangles used
		int m_numTriangles;
		Triangle *m_pTriangles;

		//	Vertices Used
		int m_numVertices;
		Vertex *m_pVertices;
};

#endif // ifndef MILKSHAPEMODEL_H
