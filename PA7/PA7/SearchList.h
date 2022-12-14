//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef SEARCH_LIST_H
#define SEARCH_LIST_H

#include "Node.h"

class AList;

class SearchList
{
public:
	// ---> CHANGE this value
	static const unsigned int CUT_OFF = 64;

public:
	// Big four
	SearchList() = delete;
	~SearchList();
	SearchList(const SearchList &) = delete;
	SearchList &operator = (const SearchList &) = delete;

	SearchList(AList *pList);

	// Accessors
	Node *GetHead() const;
	void SetHead(Node *pNode);
	int GetNumNodes() const;

	// Class methods
	int GetCutoffLength(); 

	//---------------------------------------------------------------------------------------
	// Please implement(rework) these methods (add additional methods to help if you want)
	//---------------------------------------------------------------------------------------
	void InsertionSort();
	void MergeSort();
	void MergeComboSort(int CutoffLength);
	
	void myInsertionSort(Node** head);
	Node* sortedInsert(Node* sortedHead, Node* n);

	void myMergeSort(Node** headRef);
	Node* sortedMerge(Node* a, Node* b);
	void frontBackSplit(Node* head, Node** frontRef, Node** backRef);

	void myMergeComboSort(Node** headRef, int length);
	struct currLength frontBackSplitCombo(Node* head, Node** front, Node** back);

private:
	// ------------------------------------------------------
	// Data - YOU CANNOT add or change data in this class
	// ------------------------------------------------------

	Node *pHead;
	int  NumNodes;
	int  mCutoffLength;
};


struct currLength
{
	int a;
	int b;
};
#endif 

// ---  End of File ---
