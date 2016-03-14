#include "Grid.h"
#include "stdio.h"

/********************************************************************************
Constructor
********************************************************************************/
CGrid::CGrid(void)
	: index_x(0)
	, index_y(0)
	, xSize(1)
	, ySize(1)
	, theGridMesh(NULL)
	, ListOfObjects(NULL)
	, m_bDisplayed(true)
{
}

/********************************************************************************
Destructor
********************************************************************************/
CGrid::~CGrid(void)
{
	DeleteObjects();
}

/********************************************************************************
Initialise this grid
********************************************************************************/
void CGrid::Init(const int index_x, const int index_y, const int xSize, const int ySize)
{
	this->index_x = index_x;
	this->index_y = index_y;
	this->xSize = xSize;
	this->ySize = ySize;
}

/********************************************************************************
Set a Mesh to this grid
********************************************************************************/
void CGrid::SetMesh(Mesh* theGridMesh)
{
	this->theGridMesh = theGridMesh;
}

/********************************************************************************
Add a new object to this grid
********************************************************************************/
void CGrid::AddObject(CSceneNode* theObject)
{
	for (int i = 0; i < (int)ListOfObjects.size(); i++)
	{
		if (ListOfObjects[i] == theObject)
		{
			return;
		}
	}
	theObject->SetTextureID(theGridMesh->textureID);
	theObject->currentGridIndex.push_back(Vector3((float)index_x, (float)index_y, 0));

	ListOfObjects.push_back( theObject );
}

/********************************************************************************
Remove an object to this grid
********************************************************************************/
void CGrid::RemoveObject(CSceneNode* theObject)
{
	for (int i = 0; i < (int)ListOfObjects.size(); i++)
	{
		if (ListOfObjects[i] == theObject)
		{
			for (int j = 0; j < (int)theObject->currentGridIndex.size(); j++)
			{
				if (theObject->currentGridIndex[j] == Vector3((float)index_x, (float)index_y, 0))
				{
					theObject->currentGridIndex.erase(ListOfObjects[i]->currentGridIndex.begin() + j);
					break;
				}
			}
			ListOfObjects.erase(ListOfObjects.begin() + i);
			return;
		}
		
	}
}

/********************************************************************************
 Get list of objects in this grid
 ********************************************************************************/
vector<CSceneNode*> CGrid::GetListOfObject(void)
{
	return ListOfObjects;
}

/********************************************************************************
RenderScene
********************************************************************************/
void CGrid::Render(void)
{
	/*
	glPushMatrix();
	glTranslatef( (float)index_x*xSize, 0, (float)index_y*ySize);

	// Draw the grid's surface
	glPushAttrib(GL_ENABLE_BIT);
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
	glColor4f( 1.0f, 1.0f, 0.0f, 0.6f);
	glBegin( GL_QUADS );
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(xSize, 0.0f, 0.0f);

	glVertex3f(xSize, 0.0f, ySize);
	glVertex3f(0.0f, 0.0f, ySize);
	glEnd();
	glDisable( GL_BLEND );
	glPopAttrib();

	// Draw the lines of the grid
	glPushAttrib(GL_ENABLE_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(10);
	glBegin( GL_LINES );
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(xSize, 0.0f, 0.0f);

	glVertex3f(xSize, 0.0f, 0.0f);
	glVertex3f(xSize, 0.0f, ySize);

	glVertex3f(xSize, 0.0f, ySize);
	glVertex3f(0.0f, 0.0f, ySize);

	glVertex3f(0.0f, 0.0f, ySize);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glLineWidth(1);
	glPopAttrib();
	glPopMatrix();
	*/
}

/********************************************************************************
RenderObjects
********************************************************************************/
void CGrid::RenderObjects(const int RESOLUTION)
{
	/*
	glPushAttrib(GL_ENABLE_BIT);
	// Draw the Grid and its list of objects
	for (int i=0; i<(int)ListOfObjects.size(); i++)
	{
	ListOfObjects[i]->Render(RESOLUTION);
	}
	glPopAttrib();
	*/
}

/********************************************************************************
Delete object from this grid
********************************************************************************/
void CGrid::DeleteObjects(void)
{
	if (theGridMesh)
	{
		delete theGridMesh;
		theGridMesh = NULL;
	}

	for (int i = 0; i < (int)ListOfObjects.size(); i++)
	{
		// Do not delete the objects as they are stored in CSceneGraph and will be deleted there.
		//delete ListOfObjects[i];
		ListOfObjects[i] = NULL;
	}
	ListOfObjects.clear();
}

/********************************************************************************
 Update the grid
 ********************************************************************************/
void CGrid::Update(void)
{
}

/********************************************************************************
Update the grid
********************************************************************************/
void CGrid::Update(const int ResolutionType)
{
	for (int i = 0; i < (int)ListOfObjects.size(); i++)
	{
		// Update the resolution type for each scene node object
		ListOfObjects[i]->Update(ResolutionType);
	}
}

/********************************************************************************
 PrintSelf
 ********************************************************************************/
void CGrid::PrintSelf()
{
	cout << "* CGrid::PrintSelf() ***********************************************************" << endl;
	if (theGridMesh)
		cout << "theGridMesh : OK" << endl;
	else
		cout << "theGridMesh : NULL" << endl;
	cout << "index_x : " << index_x << endl;
	cout << "index_y : " << index_y << endl;
	cout << "xSize   : " << xSize << endl;
	cout << "ySize   : " << ySize << endl;
	cout << "********************************************************************************" << endl;
}

/********************************************************************************
Get Top Left position of this grid
********************************************************************************/
Vector3 CGrid::GetTopLeft()
{
	return Vector3((float)index_x * xSize, 999999.0f, (float)index_y * ySize);
}

/********************************************************************************
Get Bottom Right position of this grid
********************************************************************************/
Vector3 CGrid::GetBottomRight()
{
	return Vector3((float)index_x * xSize + xSize, -999999.0f, (float)index_y * ySize + ySize);
}