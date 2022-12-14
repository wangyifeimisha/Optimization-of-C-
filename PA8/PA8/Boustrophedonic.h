//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef BOUSTROPHEDIC_H
#define BOUSTROPHEDIC_H

#include "Node.h"

enum NodeType
{
	CornerNode,			// 4 situations
	HorizontalEdge,		// 6 situations
	VerticalEdge,		// 4 situations
	Center				// 4 situations
};


void Remove(Node *&head, int row, int col);
NodeType checkNodeType(Node* n);
Node* findNode(Node*& pHead, int row, int col);

// Add extra methods here (if desired):


#endif

// ---  End of File ---

