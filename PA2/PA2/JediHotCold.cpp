//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// Users
#include "Bloated.h"
#include "Node.h"
#include "JediHotCold.h"
#include "JediRedirect.h"

JediHotCold::JediHotCold(const Bloated * const pBloated)
{
	unsigned int numBloated = 0;
	Node* temp = pBloated->GetListHead();
	while (temp)
	{
		numBloated++;
		temp = temp->pNext;
	}

	this->pHotHead = new JediHotNode[numBloated / JediHotNode::KeyMax]();
	this->pRedirectHead = new JediRedirect[numBloated / JediHotNode::KeyMax]();
	this->pColdHead = new JediColdNode[numBloated]();

	JediHotNode* pFirst = this->pHotHead;
	JediHotNode* pLast = this->pHotHead + (numBloated / JediHotNode::KeyMax) - 1;
	JediHotNode* pCurr = pFirst;

	JediHotNode* tempHot = this->pHotHead;
	JediRedirect* tempRedirect = this->pRedirectHead;
	JediColdNode* tempCold = this->pColdHead;
	temp = pBloated->GetListHead();

	// initialize the all nodes
	for (unsigned int i = 0; i < numBloated / JediHotNode::KeyMax; ++i)
	{
		// copy data from bloated
		for (unsigned int j = 0; j < JediHotNode::KeyMax; ++j)
		{
			tempHot->key[j] = temp->key;
			tempHot->pRedirect = tempRedirect;
			tempRedirect->pCold[j] = tempCold;
			tempRedirect->pCold[j]->key = temp->key;
			tempRedirect->pCold[j]->aa = temp->aa;
			tempRedirect->pCold[j]->bb = temp->bb;
			tempRedirect->pCold[j]->cc = temp->cc;
			tempRedirect->pCold[j]->dd = temp->dd;
			tempRedirect->pCold[j]->x = temp->x;
			tempRedirect->pCold[j]->y = temp->y;
			tempRedirect->pCold[j]->z = temp->z;
			tempRedirect->pCold[j]->w = temp->w;
			tempRedirect->pCold[j]->A = temp->A;
			tempRedirect->pCold[j]->B = temp->B;
			tempRedirect->pCold[j]->C = temp->C;
			tempRedirect->pCold[j]->D = temp->D;
			tempRedirect->pCold[j]->MA = temp->MA;
			tempRedirect->pCold[j]->MB = temp->MB;
			tempRedirect->pCold[j]->MC = temp->MC;
			tempRedirect->pCold[j]->MD = temp->MD;
			tempRedirect->pCold[j]->ME = temp->ME;
			//strcpy_s(tempHot->pCold->name, Node::NAME_SIZE, temp->name);
			memcpy_s(tempRedirect->pCold[j]->name, Node::NAME_SIZE, temp->name, Node::NAME_SIZE);
			temp++;
			tempCold++;
		}
		
		pCurr->pNext = (pCurr + 1);
		pCurr->pPrev = (pCurr - 1);
		pCurr++;
		tempHot++;
		tempRedirect++;
	}
	// fix up the first and last node
	pLast->pNext = nullptr;
	pFirst->pPrev = nullptr;
}

JediHotCold::~JediHotCold()
{
	// HINT - do something here
	delete[]pHotHead;
	delete[]pRedirectHead;
	delete[]pColdHead;
}
//----------------------------------------------------------------------------------
// Find Key using linked lists (pointers only) 
//    Hint: use ->pNext
//    YOU MUST - iterate through the nodes in a linked list fashion or 0 credit
//
// Return true if you find the node
// Return the pointer in the argument list to the HotNode and ColdNode (if found)
//----------------------------------------------------------------------------------
bool JediHotCold::FindKey(int key, JediColdNode *&pFoundColdNode, JediHotNode *&pFoundHotNode)
{
	JediHotNode* temp = this->GetHotHead();
	while (temp)
	{
		for (unsigned int i = 0; i < JediHotNode::KeyMax; ++i)
		{
			if (temp->key[i] != key)
			{
				//do nothing
			}
			else
			{
				pFoundHotNode = temp;
				pFoundColdNode = temp->pRedirect->pCold[i];
				return true;
			}
		}
		temp = temp->pNext;
	}
	return false;
}

JediHotNode *JediHotCold::GetHotHead() const
{
	return this->pHotHead;
}

// ---  End of File ---

