#pragma once
#include <list>

class CSceneNode
{
public:
	// constructor
	CSceneNode() { }

	// destructor - calls destroy
	virtual ~CSceneNode() { Destroy(); }

	// release this object from memory
	void Release() { delete this; }

	// update our scene node
	virtual void Update()
	{
		// loop through the list and update the children
		for (std::list<CSceneNode*>::iterator i = m_lstChildren.begin();
			i != m_lstChildren.end(); i++)
		{
			(*i)->Update();
		}
	}

	// destroy all the children
	void Destroy()
	{
		for (std::list<CSceneNode*>::iterator i = m_lstChildren.begin();
			i != m_lstChildren.end(); i++)
			(*i)->Release();

		m_lstChildren.clear();
	}

	// add a child to our custody
	void AddChild(CSceneNode* pNode)
	{
		m_lstChildren.push_back(pNode);
	}

protected:
	// list of children
	std::list<CSceneNode*> m_lstChildren;
};