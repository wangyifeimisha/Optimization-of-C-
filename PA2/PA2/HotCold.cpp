//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// Users
#include "Bloated.h"
#include "Node.h"
#include "hotcold.h"

HotCold::HotCold(const Bloated * const pBloated)
{
	unsigned int numBloated = 0;
	Node* temp = pBloated->GetListHead();
	while (temp)
	{
		numBloated++;
		temp = temp->pNext;
	}

	this->pHotHead = new HotNode[numBloated]();
	this->pColdHead = new ColdNode[numBloated]();

	HotNode* pFirst = this->pHotHead;
	HotNode* pLast = this->pHotHead + numBloated - 1;
	HotNode* pCurr = pFirst;

	HotNode* tempHot = this->pHotHead;
	ColdNode* tempCold = this->pColdHead;
	temp = pBloated->GetListHead();
	
	// initialize the all nodes
	for (unsigned int i = 0; i < numBloated; ++i)
	{
		// copy data from bloated
		tempHot->key = temp->key;
		tempHot->pCold = tempCold;
		tempHot->pCold->key = temp->key;
		tempHot->pCold->aa = temp->aa;
		tempHot->pCold->bb = temp->bb;
		tempHot->pCold->cc = temp->cc;
		tempHot->pCold->dd = temp->dd;
		tempHot->pCold->x = temp->x;
		tempHot->pCold->y = temp->y;
		tempHot->pCold->z = temp->z;
		tempHot->pCold->w = temp->w;
		tempHot->pCold->A = temp->A;
		tempHot->pCold->B = temp->B;
		tempHot->pCold->C = temp->C;
		tempHot->pCold->D = temp->D;
		tempHot->pCold->MA = temp->MA;
		tempHot->pCold->MB = temp->MB;
		tempHot->pCold->MC = temp->MC;
		tempHot->pCold->MD = temp->MD;
		tempHot->pCold->ME = temp->ME;
		//strcpy_s(tempHot->pCold->name, Node::NAME_SIZE, temp->name);
		memcpy_s(tempHot->pCold->name, Node::NAME_SIZE, temp->name, Node::NAME_SIZE);
		
		pCurr->pNext = (pCurr + 1);
		pCurr->pPrev = (pCurr - 1);
		pCurr++;
		temp++;
		tempHot++;
		tempCold++;
	}

	// fix up the first and last node
	pLast->pNext = nullptr;
	pFirst->pPrev = nullptr;

	
	
}

HotCold::~HotCold()
{
	delete[] this->pHotHead;
	delete[] this->pColdHead;
}

//----------------------------------------------------------------------------------
// Find Key using linked lists (pointers only) 
//    Hint: use ->pNext
//    YOU MUST - iterate through the nodes in a linked list fashion or 0 credit
//
// Return true if you find the node
// Return the pointer in the argument list to the HotNode and ColdNode (if found)
//----------------------------------------------------------------------------------
bool HotCold::FindKey(int key, ColdNode *&pFoundColdNode, HotNode *&pFoundHotNode)
{
	HotNode* temp = this->GetHotHead();
	while (temp)
	{
		if (temp->key != key)
		{
			temp = temp->pNext;
		}
		else
		{
			pFoundHotNode = temp;
			pFoundColdNode = temp->pCold;
			return true;
		}
	}
	return false;
}

HotNode *HotCold::GetHotHead() const
{
	return this->pHotHead;
}

// ---  End of File ---

