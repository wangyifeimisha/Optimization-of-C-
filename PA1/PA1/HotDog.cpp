//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "HotDog.h"

// -----------------------------------------------
// AZUL_REPLACE_ME_STUB
// this is place holder for compiling purposes
// Delete each AZUL_REPLACE_ME_STUB line
// Replace with your own code
// -----------------------------------------------

// Methods
HotDog::HotDog()
	:next(nullptr), prev(nullptr), condiments(0x0)
{
	//this->condiments = 0;
	//this->next = nullptr;
	//this->prev = nullptr;
}

HotDog::HotDog(const HotDog& h)
	:next(nullptr), prev(nullptr), condiments(h.condiments)
{
	//
}
HotDog& HotDog::operator =(const HotDog& h)
{
	this->condiments = h.condiments;
	this->next = nullptr;
	this->prev = nullptr;
	return *this;
}

HotDog::~HotDog()
{
	//do nothing
}



void HotDog::Minus(const Condiments condiment)
{
	// Only use bit-wise operations
	this->condiments &= (0xFF - (unsigned int)condiment);
}

void HotDog::Add(const Condiments condiment)
{
	// Only use bit-wise operations
	this->condiments |= (unsigned int)condiment;
}

unsigned int HotDog::GetCondiments() const
{
	return this->condiments;
}

HotDog * const HotDog::GetNext() const
{
	return this->next;
}

HotDog * const HotDog::GetPrev() const
{
	return this->prev;
}

void HotDog::SetNext(HotDog *pDog)
{
	this->next = pDog;
	
}

void HotDog::SetPrev(HotDog *pDog)
{
	this->prev = pDog;
	
}


// ---  End of File ---------------

