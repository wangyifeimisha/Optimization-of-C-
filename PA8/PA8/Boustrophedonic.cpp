//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Boustrophedonic.h"

void Remove(Node *&pHead, int row, int col)
{
	Node* target = findNode(pHead, row, col);
	NodeType type = checkNodeType(target);
	
	if (type == NodeType::CornerNode)
	{
		// 6 situations, first handle top corner
		// 1.Upperright
		if (target->pSouth)
		{
			target->pSouth->pWest->pNorth->pEast = nullptr;
			delete target;
		}
		// 2&3 Upperleft or bottomleft at odd number row
		else if (target->pEast)
		{
			// Upperleft
			if (target->pEast->pSouth)
			{
				target->pEast->pSouth->pWest->pNorth = nullptr;
				pHead = target->pEast;
				delete target;
			}
			// Bottomleft at odd row
			else
			{
				target->pEast->pNorth->pWest->pSouth = nullptr;
				delete target;
			}
		}
		//4 Bottomright at even row
		else if (target->pWest)
		{
			target->pWest->pNorth->pEast->pSouth = nullptr;
			delete target;
		}
		//5&6 Bottom left at even row and bottom right at odd row
		else if (target->pNorth)
		{
			// Bottomleft
			if (target->pNorth->pEast)
			{
				target->pNorth->pEast->pSouth->pWest = nullptr;
				delete target;
			}
			// Bottomright
			else
			{
				target->pNorth->pWest->pSouth->pEast = nullptr;
				delete target;
			}
		}
	}

	else if (type == NodeType::HorizontalEdge)
	{
		// 6 situations
		// 2 for if last even row
		if (target->pWest)
		{
			if (!target->pNorth)
			{
				target->pWest->pNorth->pEast->pSouth = nullptr;
				target->pWest->pNorth->pEast->pEast->pEast->pSouth->pWest->pWest = target->pWest;
				delete target;
			}
			else
			{
				target->pNorth->pEast->pSouth->pWest = target->pWest;
				delete target;
			}
		}
		else
		{
			// 2 for if first row
			if (target->pSouth)
			{
				target->pSouth->pWest->pNorth->pEast = target->pEast;
				delete target;
			}
			else if (target->pEast->pSouth)
			{
				target->pEast->pSouth->pWest->pNorth = nullptr;
				target->pEast->pSouth->pWest->pWest->pWest->pNorth->pEast->pEast = target->pEast;
				delete target;
			}
			// 2 for if last odd row
			else if (target->pNorth)
			{
				target->pNorth->pWest->pSouth->pEast = target->pEast;
				delete target;
			}
			else
			{
				target->pEast->pNorth->pWest->pSouth = nullptr;
				target->pEast->pNorth->pWest->pWest->pWest->pSouth->pEast->pEast = target->pEast;
				delete target;
			}
		}
	}

	else if (type == NodeType::VerticalEdge)
	{
		// 4 situations
		// 1. first column situation 1
		if (target->pEast)
		{
			target->pEast->pNorth->pWest->pSouth = target->pEast->pSouth->pWest;
			target->pEast->pSouth->pWest->pNorth = target->pEast->pNorth->pWest;
			delete target;
		}
		// 2. first column situation 2
		else if (target->pNorth->pEast)
		{
			target->pNorth->pEast->pSouth->pWest = nullptr;
			delete target;
		}
		// 3. last column situation 1
		else if (target->pWest)
		{
			target->pWest->pNorth->pEast->pSouth = target->pWest->pSouth->pEast;
			target->pWest->pSouth->pEast->pNorth = target->pWest->pNorth->pEast;
			delete target;
		}
		// 4. last column situation 2
		else
		{
			target->pNorth->pWest->pSouth->pEast = nullptr;
			delete target;
		}
	}

	// it is center node 4 situations
	else
	{
		// 2 for odd number row
		if (target->pEast)
		{
			if (target->pNorth)
			{
				target->pNorth->pWest->pSouth->pEast = target->pEast;
				delete target;
			}
			else
			{
				target->pEast->pNorth->pWest->pSouth = target->pEast->pSouth->pWest;
				target->pEast->pSouth->pWest->pNorth = target->pEast->pNorth->pWest;
				target->pEast->pNorth->pWest->pWest->pWest->pSouth->pEast->pEast = target->pEast;
				delete target;
			}
		}
		// 2 for even number row
		else
		{
			if (target->pNorth)
			{
				target->pNorth->pEast->pSouth->pWest = target->pWest;
				delete target;
			}
			else
			{																  
				target->pWest->pNorth->pEast->pSouth = target->pWest->pSouth->pEast;
				target->pWest->pSouth->pEast->pNorth = target->pWest->pNorth->pEast;
				target->pWest->pNorth->pEast->pEast->pEast->pSouth->pWest->pWest = target->pWest;
				delete target;
			}
		}
	}
}


Node* findNode(Node*& pHead, int row, int col)
{
	Node* result = pHead;
	// Odd number row
	int counter = row / 2;
	if (row % 2 == 0)
	{
		for (int i = 0; i < counter; i++)
		{
			result = result->pEast->pSouth->pWest->pSouth;
		}

		for (int j = 0; j < col; j++)
		{
			result = result->pEast;
		}
	}

	// Even number row
	else
	{
		for (int i = 0; i < counter; i++)
		{
			result = result->pEast->pSouth->pWest->pSouth;
		}

		if (col % 2 != 0)
		{
			for (int j = 0; j < col; j++)
			{
				result = result->pEast;
			}
			result = result->pSouth;
		}

		else
		{
			for (int j = 0; j < col + 1; j++)
			{
				result = result->pEast;
			}
			result = result->pSouth->pWest;
		}
	}

	return result;
}

NodeType checkNodeType(Node* n)
{
	// odd row
	if (n->pEast)
	{
		if (!n->pNorth && !n->pSouth)
			// First row ... need to decide whether is corner or edge
		{
			if (!n->pEast->pNorth)
			{
				// Upper left corner
				if (!n->pEast->pSouth->pWest->pWest) return NodeType::CornerNode;
				// First row horizontal edge at odd,odd  eg.[0,2]
				else return NodeType::HorizontalEdge;
			}
			else
			{
				// Check whether is the final row ---> odd number row
				if (!n->pEast->pSouth)
				{
					// Bottom left corner
					if (!n->pEast->pNorth->pWest->pWest) return NodeType::CornerNode;
					else return NodeType::HorizontalEdge;
				}
				// If not last row ---> vertical edge or center node
				else
				{
					if (!n->pEast->pNorth->pWest->pWest) return NodeType::VerticalEdge;	// Leftmost column
					else return NodeType::Center;
				}
			}
		}
		else if (n->pSouth && !n->pNorth) return NodeType::HorizontalEdge;	// First row
		else if (n->pNorth && !n->pSouth) return NodeType::HorizontalEdge;	// Last row
		else return NodeType::Center;
			
	}
	
	// Wierd case
	else if (!n->pEast && !n->pWest)
	{
		if (!n->pNorth) return NodeType::CornerNode;// Upper right corner
		if (!n->pSouth) return NodeType::CornerNode;// Bottom left corner if even number row or Bottom right corner if odd number row
		else return NodeType::VerticalEdge;			// Maybe the leftmost column or rightmost column
	}

	// Handle pWest (even row£©
	else
	{
		
		if (!n->pSouth && !n->pNorth)
		{
			// If last row
			if (!n->pWest->pSouth)
			{
				if (!n->pWest->pNorth->pEast->pEast) return NodeType::CornerNode;	// Bottom right corner if even number row
				else return NodeType::HorizontalEdge;
			}
			else
			{
				if (!n->pWest->pNorth->pEast->pEast) return NodeType::VerticalEdge;	// Rightmost column
				else return NodeType::Center;
			}
		}
		else if (n->pNorth && !n->pSouth) return NodeType::HorizontalEdge;			// Last row
		else return NodeType::Center;
	}
}



// ---  End of File ---

