//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#ifndef HOTLIST_H
#define HOTLIST_H

class List;
class Hot;

class HotList
{
public:
	HotList() = delete;
	HotList(const HotList &) = delete;
	HotList &operator = (const HotList &) = delete;

	//--------------------------------------------
	// Implement these functions:
	//--------------------------------------------

	HotList(const List *const pList);
	~HotList();
	Hot *Find(unsigned int _key) const;

	// ------------------------------------------
	// Data:  (do not add or modify the data)
	// ------------------------------------------

	Hot *poHead;
};


#endif

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

// ---  End of File ---
