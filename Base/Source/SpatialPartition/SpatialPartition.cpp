#include "SpatialPartition.h"
#include "stdio.h"
#include <algorithm>

// For Occlusion. Sorting of grids based on distance to a position
struct MyStruct
{
	float key;
	int indexValue;

	MyStruct(float k, int iv) : key(k), indexValue(iv) {}
};

struct less_than_key
{
	inline bool operator() (const MyStruct& struct1, const MyStruct& struct2)
	{
		return (struct1.key < struct2.key);
	}
};

std::vector < MyStruct > vec;

/********************************************************************************
Constructor
********************************************************************************/
CSpatialPartition::CSpatialPartition(void)
: theGrid(NULL)
, xSize(0)
, ySize(0)
, xGridSize(0)
, yGridSize(0)
, xNumOfGrid(0)
, yNumOfGrid(0)
{
}

/********************************************************************************
Destructor
********************************************************************************/
CSpatialPartition::~CSpatialPartition(void)
{
	for (int i = 0; i < xNumOfGrid; i++)
	{
		for (int j = 0; j < yNumOfGrid; j++)
		{
			theGrid[i*yNumOfGrid + j].DeleteObjects();
		}
	}
	delete[] theGrid;
}

/********************************************************************************
Initialise the spatial partition
********************************************************************************/
bool CSpatialPartition::Init(const int xSize, const int ySize, const int xNumOfGrid, const int yNumOfGrid)
{
	if ((xSize > 0) && (ySize > 0)
		&& (xNumOfGrid > 0) && (yNumOfGrid > 0))
	{
		this->xNumOfGrid = xNumOfGrid;
		this->yNumOfGrid = yNumOfGrid;
		this->xGridSize = xSize;
		this->yGridSize = ySize;
		this->xSize = xGridSize * xNumOfGrid;
		this->ySize = yGridSize * yNumOfGrid;

		// Create an array of grids
		theGrid = new CGrid[xNumOfGrid*yNumOfGrid];

		// Initialise the array of grids
		for (int i = 0; i < xNumOfGrid; i++)
		{
			for (int j = 0; j < yNumOfGrid; j++)
			{
				theGrid[i*yNumOfGrid + j].Init(i, j, xSize, ySize);
			}
		}
		return true;
	}
	return false;
}

/********************************************************************************
Get xNumOfGrid
********************************************************************************/
int CSpatialPartition::GetxNumOfGrid(void)
{
	return xNumOfGrid;
}

/********************************************************************************
Get yNumOfGrid
********************************************************************************/
int CSpatialPartition::GetyNumOfGrid(void)
{
	return yNumOfGrid;
}

/********************************************************************************
Get a particular grid
********************************************************************************/
CGrid* CSpatialPartition::GetGrid(const int xIndex, const int yIndex)
{
	CGrid* grid = &theGrid[xIndex*yNumOfGrid + yIndex];
	return grid;
}

/********************************************************************************
Get a particular grid's Mesh
********************************************************************************/
Mesh* CSpatialPartition::GetGridMesh(const int xIndex, const int yIndex)
{
	if (theGrid[xIndex*yNumOfGrid + yIndex].m_bDisplayed == true)
		return theGrid[xIndex*yNumOfGrid + yIndex].theGridMesh;
	else
		return NULL;
}

/********************************************************************************
Set a particular grid
********************************************************************************/
void CSpatialPartition::SetGridMesh(const int xIndex, const int yIndex, Mesh* theGridMesh)
{
	theGrid[xIndex*yNumOfGrid + yIndex].SetMesh(theGridMesh);
}

/********************************************************************************
Add a new object model
********************************************************************************/
void CSpatialPartition::AddObject(CSceneNode* theObject)
{
	// Get the indices of the 2 values of each position
	Vector3 temp = theObject->GetTopLeft();
	Vector3 temp2 = theObject->GetBottomRight();
	int index_topleft_x = ((int)theObject->GetTopLeft().x / (xSize/xNumOfGrid));
	int index_topleft_z = ((int)theObject->GetTopLeft().z / (ySize/yNumOfGrid));
	int index_bottomright_x = ((int)theObject->GetBottomRight().x / (xSize/xNumOfGrid));
	int index_bottomright_z = ((int)theObject->GetBottomRight().z / (ySize/yNumOfGrid));

	// Calculate the index of each position
	int index_topleft = index_topleft_x*yNumOfGrid + index_topleft_z;
	int index_bottomright = index_bottomright_x*yNumOfGrid + index_bottomright_z;

	// Add them to each grid
	if ((index_topleft >= 0) && (index_topleft<xNumOfGrid*yNumOfGrid))
	{
		theGrid[index_topleft].AddObject(theObject);
	}

	// if part of the object is in another grid, then add it in as well.
	if ((index_bottomright >= 0) && (index_bottomright<xNumOfGrid*yNumOfGrid))
	{
		if (index_topleft != index_bottomright)
		{
			theGrid[index_bottomright].AddObject(theObject);
		}
	}
}

/********************************************************************************
Calculate the squared distance from camera to a grid's centrepoint
********************************************************************************/
float CSpatialPartition::CalculateDistanceSquare(Vector3* theCameraPosition, const int xIndex, const int yIndex)
{
	float xDistance = (xIndex * xNumOfGrid + (xSize / 2)) - theCameraPosition->x;
	float yDistance = (yIndex * yNumOfGrid + (ySize / 2)) - theCameraPosition->z;

	return (float)(xDistance*xDistance + yDistance*yDistance);
}

/********************************************************************************
Calculate the squared distance from camera to a grid's centrepoint
********************************************************************************/
float CSpatialPartition::CalculateDistanceSquare(Vector3 thePosition, Vector3 direction, const int xIndex, const int yIndex)
{
	float xDistance = (xIndex * xGridSize + (xGridSize / 2)) - thePosition.x;
	float yDistance = (yIndex * yGridSize + (yGridSize / 2)) - thePosition.z;

	return (float)(xDistance*xDistance + yDistance*yDistance);
}

/********************************************************************************
Find the index of a grid which is nearest to a position
********************************************************************************/
void CSpatialPartition::FindNearestGrid(Vector3 position, Vector3 direction)
{

	float m_fDistance = -1.0f;

	for (int i = 0; i < xNumOfGrid; i++)
	{
		for (int j = 0; j < yNumOfGrid; j++)
		{
			m_fDistance = CalculateDistanceSquare(position, direction, i, j);
			vec.push_back(MyStruct(m_fDistance, i*yNumOfGrid + j));
		}
	}

#if _DEBUG
	// Display the list of grids BEFORE sorting
	cout << "BEFORE SORT" << endl;
	for (int i = 0; i < (int)vec.size(); i++)
	{
		cout << i << ": index=" << vec[i].indexValue << ", key = "
			<< vec[i].key << " => " << theGrid[vec[i].indexValue].m_bDisplayed << endl;
	}
#endif

	// Sort the vector
	std::sort(vec.begin(), vec.end(), less_than_key());

#if _DEBUG
	// Display the list of grids AFTER sorting
	cout << "AFTER SORT" << endl;
	for (int i = 0; i < (int)vec.size(); i++)
	{
		cout << i << ": index=" << vec[i].indexValue << ", key = "
			<< vec[i].key << " => " << theGrid[vec[i].indexValue].m_bDisplayed << endl;
	}
#endif
}

/********************************************************************************
Render the spatial partition
********************************************************************************/
void CSpatialPartition::Render(Vector3* theCameraPosition)
{
	for (int i = 0; i < xNumOfGrid; i++)
	{
		for (int j = 0; j < yNumOfGrid; j++)
		{
			// Render the Grid and its objects
			//glPushMatrix();
			// Check the distance for this grid then decide the LOD to display
			if (theCameraPosition)
			{
				float distanceGrid2Camera = CalculateDistanceSquare(theCameraPosition, i, j);
				if (distanceGrid2Camera < 900)
				{
					theGrid[i*yNumOfGrid + j].RenderObjects(0);
				}
				else if (distanceGrid2Camera < 3600)
				{
					theGrid[i*yNumOfGrid + j].RenderObjects(1);
				}
				else
				{
					theGrid[i*yNumOfGrid + j].RenderObjects(2);
				}
			}
			//glPopMatrix();
		}
	}

	for (int i = 0; i < xNumOfGrid; i++)
	{
		for (int j = 0; j < yNumOfGrid; j++)
		{
			// Render the Grid and its objects
			//glPushMatrix();
			theGrid[i*yNumOfGrid + j].Render();
			//glPopMatrix();
		}
	}
}

/********************************************************************************
Update the spatial partition
********************************************************************************/
void CSpatialPartition::Update(Vector3 theCameraPosition, Vector3 theCameraNormal)
{
	for (int i = 0; i < xNumOfGrid; i++)
	{
		for (int j = 0; j < yNumOfGrid; j++)
		{
			if (prevCameraPosition != theCameraPosition)
			{
				float distanceGrid2Camera = CalculateDistanceSquare(theCameraPosition, theCameraNormal, i, j);
				if (distanceGrid2Camera < 400000)
				{
					// Update the Grids
					theGrid[i*yNumOfGrid + j].Update(CModel::RESOLUTION_HIGH);
				}
				else if (distanceGrid2Camera < 800000)
				{
					// Update the Grids
					theGrid[i*yNumOfGrid + j].Update(CModel::RESOLUTION_MEDIUM);
				}
				else
				{
					// Update the Grids
					theGrid[i*yNumOfGrid + j].Update(CModel::RESOLUTION_LOW);
				}
			}
		}
	}
	prevCameraPosition = theCameraPosition;

	/*
	// Check for Occlusion
	FindNearestGrid(theCameraPosition, theCameraNormal);	// Find the grid which is nearest to the camera

	theOcclusionChecker.SetScreenCoordinate(theCameraPosition);	// Set the position of the plane where all grids will map to
	theOcclusionChecker.SetScreenNormal(theCameraNormal);

#if _DEBUG
	cout << "theCameraPosition: " << theCameraPosition << endl;
#endif

#if _DEBUG
#endif

	if ((int)vec.size() > 1)
	{
		// Use the nearest grid as the reference grid
		Vector3 positionReference_TopLeft = theOcclusionChecker.GetProjectedCoordinate(theGrid[vec[0].indexValue].GetTopLeft());
		Vector3 positionReference_BottomRight = theOcclusionChecker.GetProjectedCoordinate(theGrid[vec[0].indexValue].GetBottomRight());
#if _DEBUG
		cout << "0. Before projection: " << theGrid[vec[0].indexValue].GetTopLeft() << ", " << theGrid[vec[0].indexValue].GetBottomRight() << endl;
		cout << "0. After projection: " << positionReference_TopLeft << ", " << positionReference_BottomRight << endl << endl;
#endif
		// Set the nearest grid's display boolean flag to true first
		theGrid[vec[0].indexValue].m_bDisplayed = true;

		for (int i = 1; i<(int)vec.size(); i++)
		{
			// Use the nearest grid as the reference positions
			Vector3 positionCheck_TopLeft = theOcclusionChecker.GetProjectedCoordinate(theGrid[vec[i].indexValue].GetTopLeft());
			Vector3 positionCheck_BottomRight = theOcclusionChecker.GetProjectedCoordinate(theGrid[vec[i].indexValue].GetBottomRight());

#if _DEBUG
			cout << i << ". Before projection: " << theGrid[vec[i].indexValue].GetTopLeft() << ", " << theGrid[vec[i].indexValue].GetBottomRight() << endl;
			cout << i << ". After projection: " << positionCheck_TopLeft << ", " << positionReference_BottomRight << endl;
			cout << "----- Start of Occlusion -----" << endl;
#endif

			// Set the grid's display boolean flag to false first
			theGrid[vec[i].indexValue].m_bDisplayed = false;

			// Check the top left corner of a grid against the reference positions
			if (positionReference_TopLeft.x > positionCheck_TopLeft.x)
			{
#if _DEBUG
				cout << "positionReference_TopLeft.x set from " << positionReference_TopLeft.x << "to " << positionCheck_TopLeft.x << endl;
#endif
				positionReference_TopLeft.x = positionCheck_TopLeft.x;
				theGrid[vec[i].indexValue].m_bDisplayed = true;
			}
			if (positionReference_TopLeft.z > positionCheck_TopLeft.z)
			{
#if _DEBUG
				cout << "positionReference_TopLeft.z set from " << positionReference_TopLeft.z << "to " << positionCheck_TopLeft.z << endl;
#endif
				positionReference_TopLeft.z = positionCheck_TopLeft.z;
				theGrid[vec[i].indexValue].m_bDisplayed = true;
			}

			// Check the bottom right corner of a grid against the reference positions
			if (positionReference_BottomRight.x < positionCheck_BottomRight.x)
			{
#if _DEBUG
				cout << "positionReference_BottomRight.x set from " << positionReference_BottomRight.x << "to " << positionCheck_BottomRight.x << endl;
#endif
				positionReference_BottomRight.x = positionCheck_BottomRight.x;
				theGrid[vec[i].indexValue].m_bDisplayed = true;
			}
			if (positionReference_BottomRight.z < positionCheck_BottomRight.z)
			{
#if _DEBUG
				cout << "positionReference_BottomRight.z set from " << positionReference_BottomRight.z << "to " << positionCheck_BottomRight.z << endl;
#endif
				positionReference_BottomRight.z = positionCheck_BottomRight.z;
				theGrid[vec[i].indexValue].m_bDisplayed = true;
			}
#if _DEBUG
			cout << "======= End of Occlusion =====" << endl;
			cout << "Current Reference: " << positionReference_TopLeft << ", " << positionReference_BottomRight << endl << endl;
#endif
		}

#if _DEBUG
		cout << endl << "Printout of vec" << endl;
		for (int i = 0; i<(int)vec.size(); i++)
		{
			cout << i << " : " << theGrid[vec[i].indexValue].GetTopLeft() << ", "
				<< theGrid[vec[i].indexValue].GetBottomRight()
				<< theGrid[vec[i].indexValue].m_bDisplayed << endl;
		}
#endif

		// Clear the list of grids in the vec vector.
		vec.clear();
	}*/
}


/********************************************************************************
PrintSelf
********************************************************************************/
void CSpatialPartition::PrintSelf()
{
	cout << "* CSpatialPartition::PrintSelf() ***********************************************" << endl;
	cout << "xSize        : " << xSize << endl;
	cout << "ySize        : " << ySize << endl;
	cout << "xNumOfGrid   : " << xNumOfGrid << endl;
	cout << "xNumOfGrid   : " << xNumOfGrid << endl;
	if (theGrid)
	{
		cout << "theGrid : OK" << endl;
		cout << "Printing out theGrid below: " << endl;
		for (int i = 0; i < xNumOfGrid; i++)
		{
			for (int j = 0; j < yNumOfGrid; j++)
			{
				theGrid[i*yNumOfGrid + j].PrintSelf();
			}
		}
	}
	else
		cout << "theGrid : NULL" << endl;

	cout << "Occlusion Checking:" << endl;
	theOcclusionChecker.PrintSelf();

	cout << "********************************************************************************" << endl;
}


/********************************************************************************
Check a position for collision with objects in any grids
********************************************************************************/
int CSpatialPartition::CheckForCollision(Vector3 position, int hitPoints)
{
	int GridIndex_x = ((int)position.x / (xSize/xNumOfGrid));
	int GridIndex_z = ((int)position.z / (ySize/yNumOfGrid));

	// Calculate the index of each position
	int GridIndex = GridIndex_x * yNumOfGrid + GridIndex_z;

	// Add them to each grid
	if ((GridIndex >= 0) && (GridIndex < xNumOfGrid * yNumOfGrid))
	{
		vector<CSceneNode*> theListOfObjects = theGrid[GridIndex].GetListOfObject();

		Vector3 ObjectTopLeft, ObjectBottomRight;
		for (int i = 0; i < (int)theListOfObjects.size(); i++)
		{
			if (theListOfObjects[i]->CheckForCollision(position, hitPoints) == true)
			{
				if (theListOfObjects[i]->GetCrowned() == true && theListOfObjects[i]->GetStatus() == false)
				{
					return 2;
				}
				else if (theListOfObjects[i]->GetTimeDead() > 0.f && theListOfObjects[i]->GetVel().IsZero() == false)
				{
					return 4;
				}
				else if (theListOfObjects[i]->GetTimeDead() > 0.f)
				{
					return 3;
				}
				else
				{
					return 1;
				}
			}
		}
	}
	return 0;
}


/********************************************************************************
Check two position for collision with objects in any grids
********************************************************************************/
int CSpatialPartition::CheckForCollision(Vector3 position_start, Vector3 position_end, int hitPoints)
{
	int GridIndex_x = ((int)position_start.x / (xSize/xNumOfGrid));
	int GridIndex_z = ((int)position_start.z / (ySize/yNumOfGrid));

	// Calculate the index of each position
	int GridIndex = GridIndex_x * yNumOfGrid + GridIndex_z;

	// Add them to each grid
	if ((GridIndex >= 0) && (GridIndex < xNumOfGrid * yNumOfGrid))
	{
		vector<CSceneNode*> theListOfObjects = theGrid[GridIndex].GetListOfObject();

		Vector3 ObjectTopLeft, ObjectBottomRight;
		for (int i = 0; i < (int)theListOfObjects.size(); i++)
		{
			Vector3 hits = Vector3(0, 0, 0);
			if (theListOfObjects[i]->CheckForCollision(position_start, position_end, hits, hitPoints))
			{
				if (theListOfObjects[i]->GetCrowned() == true && theListOfObjects[i]->GetStatus() == false)
				{
					return 2;
				}
				else if (theListOfObjects[i]->GetTimeDead() > 0.f && theListOfObjects[i]->GetVel().IsZero() == false)
				{
					return 4;
				}
				else if (theListOfObjects[i]->GetTimeDead() > 0.f)
				{
					return 3;
				}
				else
				{
					return 1;
				}
			}
		}
	}
	return 0;
}


/********************************************************************************
Check object for collision with objects in any grids
********************************************************************************/
CSceneNode* CSpatialPartition::CheckForCollision(CSceneNode* object, int hitPoints)
{
	Vector3 ObjectCenter = object->GetTopLeft() - (object->GetTopLeft() - object->GetBottomRight()) * 0.5;

	int GridIndex_x = ((int)ObjectCenter.x / (xSize / xNumOfGrid));
	int GridIndex_z = ((int)ObjectCenter.z / (ySize / yNumOfGrid));

	// Calculate the index of each position
	int GridIndex = GridIndex_x * yNumOfGrid + GridIndex_z;

	// Add them to each grid
	if ((GridIndex >= 0) && (GridIndex < xNumOfGrid * yNumOfGrid))
	{
		vector<CSceneNode*> theListOfObjects = theGrid[GridIndex].GetListOfObject();

		Vector3 ObjectTopLeft, ObjectBottomRight;
		for (int i = 0; i < (int)theListOfObjects.size(); i++)
		{
			if (theListOfObjects[i]->CheckForCollision(object, hitPoints) == true)
			{
				return theListOfObjects[i];
				/*if (theListOfObjects[i]->GetCrowned() == true && theListOfObjects[i]->GetStatus() == false)
				{
					return 2;
				}
				else if (theListOfObjects[i]->GetTimeDead() > 0.f && theListOfObjects[i]->GetVel().IsZero() == false)
				{
					return 4;
				}
				else if (theListOfObjects[i]->GetTimeDead() > 0.f)
				{
					return 3;
				}
				else
				{
					return 1;
				}*/
			}
		}
	}
	return NULL;
}


/********************************************************************************
Check object current grid
********************************************************************************/
void CSpatialPartition::CheckObjectGrid(CSceneNode* object)
{
	for (int i = 0; i < (int)object->currentGridIndex.size(); i++)
	{
		CGrid* grid = GetGrid((int)(object->currentGridIndex[i].x), (int)(object->currentGridIndex[i].y));
		Vector3 GridTopLeft = grid->GetTopLeft();
		Vector3 GridBottomRight = grid->GetBottomRight();
		Vector3 ObjectTopLeft = object->GetTopLeft();
		Vector3 ObjectBottomRight = object->GetBottomRight();

		if (((GridTopLeft.x < ObjectTopLeft.x) || (GridTopLeft.z < ObjectTopLeft.z)) ||
			((GridBottomRight.x > ObjectTopLeft.x) || (GridBottomRight.z > ObjectTopLeft.z)))
		{
			grid->RemoveObject(object);

			AddObject(object);
		}
		else if (((GridTopLeft.x < ObjectBottomRight.x) || (GridTopLeft.z < ObjectBottomRight.z)) ||
			((GridBottomRight.x > ObjectBottomRight.x) || (GridBottomRight.z > ObjectBottomRight.z)))
		{
			grid->RemoveObject(object);

			AddObject(object);
		}
	}
}