//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "HotList.h"
#include "Hot.h"
#include "List.h"
#include "Node.h"

//---------------------------------------------------------------
// Rules:
// 
// You cannot count anywhere in your creation of the list
//     (iterate the list and create Hot objects on the fly)
// Do not use placement new or new array...
//     (create each Hot object with new individually)
// Assume you will create 1000s of Hot objects...
//     (make sure you clean it up in the destructor)
// You cannot add or change data in Hot, HotList, List, Node
//     (no need for any data changes... make it work as-is)
//
//---------------------------------------------------------------
//
// Add the constructor, destructor and find method here:
// 
//     HotList(const List *const pList);
//     ~HotList();
//     Hot *Find(unsigned int _key);
//
//---------------------------------------------------------------

HotList::HotList(const List *const pList)
{
	this->poHead = nullptr;
	Hot* tmpHot = this->poHead;
	Node* tmpNode = pList->poHead;

	while (tmpNode)
	{
		if (!this->poHead)
		{
			this->poHead = new Hot();
			tmpHot = this->poHead;
			tmpHot->key = tmpNode->key;
			tmpHot->pData = tmpNode;
			tmpHot->pNext = nullptr;

			tmpNode = tmpNode->pNext;
		}

		else
		{
			tmpHot->pNext = new Hot();
			tmpHot = tmpHot->pNext;
			tmpHot->key = tmpNode->key;
			tmpHot->pData = tmpNode;
			tmpHot->pNext = nullptr;

			tmpNode = tmpNode->pNext;
		}
	}

}

HotList::~HotList()
{
	Hot* pTmp = this->poHead;
	Hot* pDeleteMe = pTmp;

	while (pTmp)
	{
		pDeleteMe = pTmp;
		pTmp = pTmp->pNext;
		delete pDeleteMe;
	}
}

Hot *HotList::Find(unsigned int _key) const
{
	Hot* pTmp = this->poHead;
	while (pTmp != nullptr)
	{
		if (_key == pTmp->key)
		{
			break;
		}

		pTmp = pTmp->pNext;
	}
	return pTmp;
}

// ---  End of File ---
