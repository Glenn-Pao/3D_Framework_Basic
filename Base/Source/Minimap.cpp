#include "Minimap.h"

CMinimap::CMinimap(void)
	: m_cMinimap_Background(NULL)
	, m_cMinimap_Border(NULL)
	, m_cMinimap_Avatar(NULL)
	, angle(0)
	, x(0)
	, y(0)
	, size_x(0)
	, size_y(0)
{
}


CMinimap::~CMinimap(void)
{
}

// Set the background mesh to this class
bool CMinimap::SetBackground(Mesh* aBackground)
{
	if (aBackground != NULL)
	{
		m_cMinimap_Background = aBackground;
		return true;
	}
	return false;
}

// Get the background mesh to this class
Mesh* CMinimap::GetBackground(void)
{
	return m_cMinimap_Background;
}

// Set the Border mesh to this class
bool CMinimap::SetBorder(Mesh* aBorder)
{
	if (aBorder != NULL)
	{
		m_cMinimap_Border = aBorder;
		return true;
	}
	return false;
}

// Get the Border mesh to this class
Mesh* CMinimap::GetBorder(void)
{
	return m_cMinimap_Border;
}

// Set the Avatar mesh to this class
bool CMinimap::SetAvatar(Mesh* anAvatar)
{
	if (anAvatar != NULL)
	{
		m_cMinimap_Avatar = anAvatar;
		return true;
	}
	return false;
}

// Get the Avatar mesh to this class
Mesh* CMinimap::GetAvatar(void)
{
	return m_cMinimap_Avatar;
}

// Set angle of avatar
bool CMinimap::SetAngle(const int angle)
{
	this->angle = angle;
	return true;
}
// Get angle
int CMinimap::GetAngle(void)
{
	return angle;
}
// Set position of avatar in minimap
bool CMinimap::SetPosition(const int x, const int y)
{
	this->x = x;
	this->y = y;
	return true;
}
// Get position x of avatar in minimap
int CMinimap::GetPosition_x(void)
{
	return x;
}
// Get position y of avatar in minimap
int CMinimap::GetPosition_y(void)
{
	return y;
}
// Set size of minimap (for calculation of avatar in minimap)
bool CMinimap::SetSize(const int size_x, const int size_y)
{
	this->size_x = size_x;
	this->size_y = size_y;
	return true;
}
// Get size of minimap (for calculation of avatar in minimap)
int CMinimap::GetSize_x(void)
{
	return size_x;
}
// Get size of minimap (for calculation of avatar in minimap)
int CMinimap::GetSize_y(void)
{
	return size_y;
}
