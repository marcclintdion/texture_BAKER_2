/*===================================================================================================
**
**	Author	:	Robert Bateman
**	E-Mail	:	rbateman@bournemouth.ac.uk
**	Brief	:	This Sourcefile is part of a series explaining how to load and render Alias Wavefront
**				Files somewhat efficently. If you are simkply after a reliable Obj Loader, then I would
**				Recommend version8; or possibly version9 and the supplied loader for extreme efficency.
**
**	Note	:	This Source Code is provided as is. No responsibility is accepted by myself for any
**				damage to hardware or software caused as a result of using this code. You are free to
**				make any alterations you see fit to this code for your own purposes, and distribute
**				that code either as part of a source code or binary executable package. All I ask is
**				for a little credit somewhere for my work!
** 
**				Any source improvements or bug fixes should be e-mailed to myself so I can update the
**				code for the greater good of the community at large. Credit will be given to the 
**				relevant people as always....
**				
**
**				Copyright (c) Robert Bateman, www.robthebloke.org, 2004
**
**				
**				National Centre for Computer Animation,
**				Bournemouth University,
**				Talbot Campus,
**				Bournemouth,
**				BH3 72F,
**				United Kingdom
**				ncca.bournemouth.ac.uk
**	
**
===================================================================================================*/



/*===================================================================================================
**
**	This version now reads in any n sided polygon, but this time it triangulates all polygons when
**	they are read in. This will make the job of converting the data to vertex arrays much easier
**	later on....
**
===================================================================================================*/


/*===================================================================================================
**
**												Includes
**
**=================================================================================================*/

/*
**	Need the windows headers to be included for openGL when coding on WIN32
*/
#ifdef WIN32
#include <windows.h>
#endif

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "ObjLoader.h"




/* Ignored until Version6 */
void ConvertMeshTo(ObjFile id,unsigned char What)
{
}
void SetLightPosition(float lx,float ly,float lz)
{
}
void SetTextures(ObjFile id,const char BumpTex[],const char BaseTex[])
{
}

/*===================================================================================================
**
**										Internal Data Structures
**
**=================================================================================================*/


/*
**	To start with, only deal with the obj file as a list of points. Essentually,
**	if we are able to draw the points out they should roughly describe the mesh.
**	So, lets look for the 'v' flag that says that the 3 floats after it describes a
**	Vertex. Essentually then, we need to have a structure for a vertex.
*/
typedef struct
{
	float x,			/*	The x component of the vertex position	*/
		  y,			/*	The y component of the vertex position	*/
		  z;			/*	The z component of the vertex position	*/
} ObjVertex;


/*
**	Now, the normal vector flag 'vn' could also do with a structure to represent it,
**	this will ultimately look very similar to the Vertex structure seeing as they have
**	similar data
*/
typedef struct
{
	float x,			/*	The x component of the normal vector	*/
		  y,			/*	The y component of the normal vector	*/
		  z;			/*	The z component of the normal vector	*/
} ObjNormal;


/*
**	A Texturing co-ordinate usually has only two values, the u and the v. Make a third
**	struct for this fact.
*/
typedef struct
{
	float u,			/*	The u parametric texturing co-ordinate	*/
		  v;			/*	The v parametric texturing co-ordinate	*/
} ObjTexCoord;


/*
**	Each face is composed of a number of `corners`. At each `corner` there will be at a
**	minimum, one vertex coordinate, and possibly a normal vector and a texturing co-ordinate.
**	Seeing as quite often a specific vertex is used by a number of faces, rather than store the
**	vertices in the face structure itself, we can use an integer reference to the position of the
**	vertex in the array. Basically it allows us the ability of storing the data as a 4byte value
**	rather than the 12 needed for a vertex.
**
**	To summaraise,
**
**		Each face is comprised of a number of `corners`, in this case the number will be held in
**	the value "m_iVertexCount". Taking into account the worst case scenario, for each corner, we
**	could have a vertex, normal and a texturing co-ordinate (usual actually). So we may need to hold
**	3 * m_iVertexCount number of indices for our faces. It kindof makes sense to basically dynamically
**	allocate an array to hold the vertex indicies, an array for the normal indices and one for the uv
**	coords. These are m_aVertexIndices, m_aNormalIndices, and m_aTexCoordIndicies respectivley.
**
**	So our full face structure looks a bit like this :
*/
typedef struct
{
	unsigned int  m_aVertexIndices[3],		/*	array of indicies that reference the vertex array in the mesh	*/
				  m_aNormalIndices[3],		/*	array of indicies that reference the normal array in the mesh	*/
				  m_aTexCoordIndicies[3];	/*	array of indicies that reference the uv coordinate array in the mesh	*/

} ObjFace;

/*
**	Each mesh is held as a structure with arrays of it's vertices, normals and texturing co-ordinates.
**	An Array of faces then references the arrays. There is also a pointer to the next node in the linked
**	list.
*/
typedef struct _ObjMesh
{
	ObjVertex		*m_aVertexArray;		/*	Array of vertices that make up this mesh	*/
	ObjNormal		*m_aNormalArray;		/*	Array of normals that make up this mesh		*/
	ObjTexCoord		*m_aTexCoordArray;		/*	Array of texturing co-ordinates that make up this mesh */
	ObjFace			*m_aFaces;				/*	Array of faces that make up this mesh */

	unsigned int	 m_iNumberOfVertices,	/*	The number of vertices in the m_aVertexArray array	*/
					 m_iNumberOfNormals,	/*	The number of normals in the m_aNormalArray array	*/
					 m_iNumberOfTexCoords,	/*	The number of uv's in the m_aTexCoordArray array	*/
					 m_iNumberOfFaces;		/*	The number of faces in the m_aFaces array			*/

	struct _ObjMesh *m_pNext;			/*	Each mesh will be stored internally as a node on a linked list */
	ObjFile			 m_iMeshID;				/*	the ID of the mesh	*/

} ObjMesh;

ObjMesh *pMesh = NULL;

/*
**	This function will take a pointer to the mesh and the number of extra triangles that
**	are required. It will then resize the polygon face array within the mesh and return
**	the index of the first new face that was allocated.
*/
unsigned int ResizeTriangleArray(ObjMesh *pMesh,unsigned int iExtraTriangleCount)
{
	/*
	**	Create a temporary pointer to the old face array in the mesh
	*/
	ObjFace *pTempFaces = pMesh->m_aFaces;

	/*
	**	Keep track of the old face count
	*/
	unsigned int iTemp  = pMesh->m_iNumberOfFaces;

	/*
	**	Increase the number of faces that will be stored in the mesh
	*/
	pMesh->m_iNumberOfFaces += iExtraTriangleCount;

	/*
	**	Allocate the number of faces now required by this mesh. Note, you could use
	**	realloc for this, but it's just my personal preference to do it this way.
	*/
	pMesh->m_aFaces = (ObjFace*)malloc(pMesh->m_iNumberOfFaces*sizeof(ObjFace));

	/*
	**	If we assert here then the memory allocation for the meshes failed
	*/
	assert(pMesh->m_aFaces);

	/*
	**	Copy across the data that was stored in the old array
	*/
	memcpy(pMesh->m_aFaces,pTempFaces,iTemp*sizeof(ObjFace));

	/*
	**	Delete the data held in the previous array
	*/
	free(pTempFaces);

	memset(&pMesh->m_aFaces[ iTemp ],0,iExtraTriangleCount*sizeof(ObjFace) );

	/*
	**	return the old size of the array (thats the same as the index of the first new triangle).
	*/
	return iTemp;

}

/*===================================================================================================
**
**										Global Variables
**
**=================================================================================================*/

/*
**	The global head of the linked list of meshes. This is a linked list because it is possible that you will be
**	loading and deleting meshes during the course of the programs execution.
*/
ObjMesh *g_LinkedListHead = NULL;

/* 
**	This is used to generate a unique ID for each Obj File
*/
unsigned int g_ObjIdGenerator=0;

/*
**	This function is only called from within the *.c file and is used to create an ObjMesh structure and
**	initialise its values (adds the mesh to the linked list also).
*/
ObjMesh *MakeOBJ( void )
{


	pMesh = (ObjMesh*) malloc (sizeof(ObjMesh));

	/*	If the program asserts here, then there was a memory allocation failure	*/
	assert(pMesh);

	/*
	**	Initialise all pointers to NULL
	*/
	pMesh->m_aFaces				= NULL;
	pMesh->m_aNormalArray		= NULL;
	pMesh->m_aTexCoordArray		= NULL;
	pMesh->m_aVertexArray		= NULL;
	pMesh->m_iNumberOfFaces		= 0;
	pMesh->m_iNumberOfNormals	= 0;
	pMesh->m_iNumberOfTexCoords = 0;
	pMesh->m_iNumberOfVertices	= 0;
	pMesh->m_iMeshID			= ++g_ObjIdGenerator;


	/*
	**	Insert the mesh at the beginning of the linked list
	*/
	pMesh->m_pNext				= g_LinkedListHead;
	g_LinkedListHead			= pMesh;

	return pMesh;
}

ObjFile LoadOBJ(const char *filename)
{
	
	unsigned int vc=0,nc=0,tc=0,fc=0;
	char buffer[256];
	FILE *fp = NULL;

	/*
	**	Open the file for reading
	*/
	fp = fopen(filename,"r");

	/*
	**	If the program asserted here, then the file could not be found or opened
	*/
	assert(fp);

	/*
	**	Create the mesh structure and add it to the linked list
	*/
	pMesh = MakeOBJ();

	/*
	**	Run through the whole file looking for the various flags so that we can count
	**	up how many data elements there are. This is done so that we can make one memory
	**	allocation for the meshes data and then run through the file once more, this time
	**	reading in the data. It's purely done to reduce system overhead of memory allocation due
	**	to otherwise needing to reallocate data everytime we read in a new element.
	*/
	while(!feof(fp))
	{
		memset(buffer,0,200);

		/*	Grab a line at a time	*/
		fgets(buffer,256,fp);

		/*	look for the 'vn' - vertex normal - flag	*/
		if( strncmp("vn ",buffer,3) == 0 )
		{
			++pMesh->m_iNumberOfNormals;
		}
		else

		/*	look for the 'vt' - texturing co-ordinate - flag  */
		if( strncmp("vt ",buffer,3) == 0 )
		{
			++pMesh->m_iNumberOfTexCoords;
		}
		else

		/*	look for the 'v ' - vertex co-ordinate - flag  */
		if( strncmp("v ",buffer,2) == 0 )
		{
			++pMesh->m_iNumberOfVertices;
		}
		else

		/*	look for the 'f ' - face - flag  */
		if( strncmp("f ",buffer,2) == 0 )
		{
			++pMesh->m_iNumberOfFaces;
		}
	}

	/*
	**	close the file for now....
	*/
	fclose(fp);

	/*
	**	Allocate the memory for the data arrays and check that it allocated ok
	*/
	pMesh->m_aVertexArray	= (ObjVertex*  )malloc( pMesh->m_iNumberOfVertices	* sizeof(ObjVertex)	  );
	assert(pMesh->m_aVertexArray);

	/*	there are occasionally times when the obj does not have any normals in it */
	if( pMesh->m_iNumberOfNormals > 0 )
	{
		pMesh->m_aNormalArray	= (ObjNormal*  )malloc( pMesh->m_iNumberOfNormals	* sizeof(ObjNormal)	  );
		assert(pMesh->m_aNormalArray);
	}

	/*	there are occasionally times when the obj does not have any tex coords in it */
	if( pMesh->m_iNumberOfTexCoords > 0 )
	{
		pMesh->m_aTexCoordArray = (ObjTexCoord*)malloc( pMesh->m_iNumberOfTexCoords	* sizeof(ObjTexCoord) );
		assert(pMesh->m_aTexCoordArray);
	}

	pMesh->m_aFaces			= (ObjFace*    )malloc( pMesh->m_iNumberOfFaces		* sizeof(ObjFace)	  );
	assert(pMesh->m_aFaces);

	/*
	**	Now we know how much data is contained in the file and we've allocated memory to hold it all.
	**	What we can therefore do now, is load up all of the data in the file easily.
	*/
	fp = fopen(filename,"r");

	while(!feof(fp))
	{
		memset(buffer,0,255);

		/*	Grab a line at a time	*/
		fgets(buffer,256,fp);

		/*	look for the 'vn' - vertex normal - flag	*/
		if( strncmp("vn ",buffer,3) == 0 )
		{
			sscanf((buffer+2),"%f%f%f",
							&pMesh->m_aNormalArray[ nc ].x,
							&pMesh->m_aNormalArray[ nc ].y,
							&pMesh->m_aNormalArray[ nc ].z);
			++nc;
		}
		else

		/*	look for the 'vt' - texturing co-ordinate - flag  */
		if( strncmp("vt ",buffer,3) == 0 )
		{
			sscanf((buffer+2),"%f%f",
							&pMesh->m_aTexCoordArray[ tc ].u,
							&pMesh->m_aTexCoordArray[ tc ].v);
			++tc;
		}
		else

		/*	look for the 'v ' - vertex co-ordinate - flag  */
		if( strncmp("v ",buffer,2) == 0 )
		{
			sscanf((buffer+1),"%f%f%f",
							&pMesh->m_aVertexArray[ vc ].x,
							&pMesh->m_aVertexArray[ vc ].y,
							&pMesh->m_aVertexArray[ vc ].z);
			++vc;
		}
		else

		/*	look for the 'f ' - face - flag  */
		if( strncmp("f ",buffer,2) == 0 )
		{
			/*
			**	some data for later....
			*/
			char *pSplitString = NULL;
			unsigned int i,ii = 0;
			unsigned int iNewTrianglesIndex = 0,
						 iNumberOfExtraTriangles = 0;
			unsigned int aFirstIndices[3],
						 aSecondIndices[3];

			ObjFace *pf = NULL;

			/*
			**	These next few lines are used to figure out how many '/' characters there
			**	are in the string. This gives us the information we need to find out how
			**	many vertices are used in this face (by dividing by two)
			*/
			for(i=0;i<strlen(buffer);i++)
			{
				if(buffer[i] == '/')
					ii++;
			}
			ii/=2;

			/*
			**	This is where it all gets confusing, What I'm going to do is to convert all polys
			**	With vertices above 3 to triangles. The number of triangles I require will be (ii-2).
			**	For example, with a poly that has vertices a,b,c,d,e; there will be 3 triangles comprised
			**	of verts (a,b,c), (a,c,d) and (a,d,e) respectively. We need to check the amount of triangles
			**	that will be needed for this polygon and resize the array accordingly.
			*/
			if( (ii-2) > 1 )
			{
				iNumberOfExtraTriangles = ii-3;
				iNewTrianglesIndex = ResizeTriangleArray(pMesh,iNumberOfExtraTriangles);
			}

			/*
			**	Pointer to the face we are currently dealing with. It's only used so that
			**	the code becomes more readable and I have less to type.
			*/
			pf = &pMesh->m_aFaces[ fc ];


			/*
			**	tokenise the string using strtok(). Basically this splits the string up
			**	and removes the spaces from each chunk. This way we only have to deal with
			**	one set of indices at a time for each of the poly's vertices.
			*/
			pSplitString = strtok((buffer+2)," \t\n");
			i=0;

			/*
			**	Get the vertex structures that we know WILL exists (there has to be a minimum of three)
			*/
			for(i=0;i<3;i++)
			{
				if( tc > 0 &&
					nc > 0 )
				{
					sscanf(pSplitString, "%d/%d/%d",
						&pf->m_aVertexIndices   [i],
						&pf->m_aTexCoordIndicies[i],
						&pf->m_aNormalIndices   [i] );

					/* need to reduce the indices by 1 because array indices start at 0, obj starts at 1  */
					--pf->m_aTexCoordIndicies[i];
					--pf->m_aNormalIndices   [i];
				}
				else
				if( tc > 0 )
				{
					sscanf(pSplitString, "%d/%d/",
						&pf->m_aVertexIndices   [i],
						&pf->m_aTexCoordIndicies[i] );

					/* need to reduce the indices by 1 because array indices start at 0, obj starts at 1  */
					--pf->m_aTexCoordIndicies[i];
				}
				else
				if( nc > 0 )
				{
					sscanf(pSplitString, "%d//%d",
						&pf->m_aVertexIndices   [i],
						&pf->m_aNormalIndices   [i] );

					/* need to reduce the indices by 1 because array indices start at 0, obj starts at 1  */
					--pf->m_aNormalIndices   [i];
				}

				/* need to reduce the indices by 1 because array indices start at 0, obj starts at 1  */
				--pf->m_aVertexIndices[i];

				/*
				**	In order to start constructing our triangles that are created after ww split the poly,
				**	we need to store som of the indices that are going to be used for the extra additional
				**	triangles after this. Basically we store the first and last sets of indices from this
				**	first triangle becasue they will be used as the first & second sets for the next triangle.
				*/
				switch(i)
				{
				case 0:
					aFirstIndices[0] = pf->m_aVertexIndices[i];
					aFirstIndices[1] = pf->m_aNormalIndices[i];
					aFirstIndices[2] = pf->m_aTexCoordIndicies[i];
					break;

				case 2:
					aSecondIndices[0] = pf->m_aVertexIndices[i];
					aSecondIndices[1] = pf->m_aNormalIndices[i];
					aSecondIndices[2] = pf->m_aTexCoordIndicies[i];
					break;
				default:
					break;
				}

				pSplitString = strtok(NULL," \t\n");
			}
			++fc;

			/*
			**	Get the additional triangles that may be there
			*/
			for(i=0;i<iNumberOfExtraTriangles;i++)
			{
				pf = &pMesh->m_aFaces[ iNewTrianglesIndex + i ];
				if( tc > 0 &&
					nc > 0 )
				{
					sscanf(pSplitString, "%d/%d/%d",
						&pf->m_aVertexIndices   [2],
						&pf->m_aTexCoordIndicies[2],
						&pf->m_aNormalIndices   [2] );

					/* need to reduce the indices by 1 because array indices start at 0, obj starts at 1  */
					--pf->m_aTexCoordIndicies[2];
					--pf->m_aNormalIndices   [2];
				}
				else
				if( tc > 0 )
				{
					sscanf(pSplitString, "%d/%d/",
						&pf->m_aVertexIndices   [2],
						&pf->m_aTexCoordIndicies[2] );

					/* need to reduce the indices by 1 because array indices start at 0, obj starts at 1  */
					--pf->m_aTexCoordIndicies[2];
				}
				else
				if( nc > 0 )
				{
					sscanf(pSplitString, "%d//%d",
						&pf->m_aVertexIndices   [2],
						&pf->m_aNormalIndices   [2] );

					/* need to reduce the indices by 1 because array indices start at 0, obj starts at 1  */
					--pf->m_aNormalIndices   [2];
				}

				/* need to reduce the indices by 1 because array indices start at 0, obj starts at 1  */
				--pf->m_aVertexIndices[2];

				/*
				**	Now assign the other indices for the triangle
				*/
				pf->m_aVertexIndices[0]		= aFirstIndices[0];
				pf->m_aNormalIndices[0]		= aFirstIndices[1];
				pf->m_aTexCoordIndicies[0]	= aFirstIndices[2];

				pf->m_aVertexIndices[1]		= aSecondIndices[0];
				pf->m_aNormalIndices[1]		= aSecondIndices[1];
				pf->m_aTexCoordIndicies[1]	= aSecondIndices[2];

				/*
				**	Copy over the indices for the next triangle.
				*/
				aSecondIndices[0] = pf->m_aVertexIndices[2];
				aSecondIndices[1] = pf->m_aNormalIndices[2];
				aSecondIndices[2] = pf->m_aTexCoordIndicies[2];

				pSplitString = strtok(NULL," \t\n");
			}
		}
	}

	fclose(fp);

	return pMesh->m_iMeshID;
}




void DrawOBJ(ObjFile id)
{

}

/*
**	Calling free() on NULL is VERY BAD in C, so make sure we
**	check all pointers before calling free.
*/
void DeleteMesh(ObjMesh* pMesh)
{
	/*
	**	If the pointer is valid
	*/
	if(pMesh)
	{
		/*	delete the face array */
		if(pMesh->m_aFaces)
		{
			free(pMesh->m_aFaces);
			pMesh->m_aFaces = NULL;
		}

		/*	delete the vertex array */
		if(pMesh->m_aVertexArray)
		{
			free(pMesh->m_aVertexArray);
			pMesh->m_aVertexArray = NULL;
		}

		/*	delete the normal array */
		if(pMesh->m_aNormalArray)
		{
			free(pMesh->m_aNormalArray);
			pMesh->m_aNormalArray = NULL;
		}

		/*	delete the texturing co-ordinate array */
		if(pMesh->m_aTexCoordArray)
		{
			free(pMesh->m_aTexCoordArray);
			pMesh->m_aTexCoordArray = NULL;
		}

		/*	free the mesh */
		free( pMesh );
	}
}

void DeleteOBJ(ObjFile id)
{
	/*
	**	Create two pointers to walk through the linked list
	*/
	ObjMesh *pCurr,
			*pPrev = NULL;

	/*
	**	Start traversing the list from the start
	*/
	pCurr = g_LinkedListHead;

	/*
	**	Walk through the list until we either reach the end, or
	**	we find the node we are looking for
	*/
	while(pCurr != NULL && pCurr->m_iMeshID != id)
	{
		pPrev = pCurr;
		pCurr = pCurr->m_pNext;
	}

	/*
	**	If we found the node that needs to be deleted
	*/
	if(pCurr != NULL)
	{
		/*
		**	If the pointer before it is NULL, then we need to
		**	remove the first node in the list
		*/
		if(pPrev == NULL)
		{
			g_LinkedListHead = pCurr->m_pNext;
		}

		/*
		**	Otherwise we are removing a node from somewhere else
		*/
		else
		{
			pPrev->m_pNext = pCurr->m_pNext;
		}

		/*
		**	Free the memory allocated for this mesh
		*/
		DeleteMesh(pCurr);
	}
}

/*
**	Delete all of the meshes starting from the front.
*/
void CleanUpOBJ(void)
{
	ObjMesh *pCurr;
	while(g_LinkedListHead != NULL)
	{
		pCurr = g_LinkedListHead;
		g_LinkedListHead = g_LinkedListHead->m_pNext;
		DeleteMesh(pCurr);
	}
}
