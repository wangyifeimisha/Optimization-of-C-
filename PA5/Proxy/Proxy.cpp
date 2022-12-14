//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Proxy.h"

// Modify This File
Vect2D::Vect2D()
	:x(0.0f), y(0.0f)
{}

Vect2D::Vect2D(const Vect2D& tmp)
	:x(tmp.x), y(tmp.y)
{}

Vect2D& Vect2D::operator =(const Vect2D& tmp)
{
	this->x = tmp.x;
	this->y = tmp.y;
	return *this;
}

Vect2D::~Vect2D()
{}


// ---  End of File ---------------
