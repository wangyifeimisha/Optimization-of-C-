//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Monkey.h"
int Monkey::numStringsCreated = 0;
int Monkey::numStringsDestroyed = 0;

Monkey::Monkey()
	:x(878), y(979)
{
	// Q1: Still don't understand why I need an array with length+=1
	//null terminated 
	size_t length = strlen("This string was initialized by a default constructor!");
	length += 1;
	this->pStatus = new char[length]();
	assert(this->pStatus);

	strcpy_s(this->pStatus, length, "This string was initialized by a default constructor!");
	Monkey::numStringsCreated++;
}

Monkey::Monkey(const Monkey& m)
{
	this->x = m.x;
	this->y = m.y;
	size_t length = strlen(m.pStatus);
	length += 1;
	this->pStatus = new char[length]();
	assert(this->pStatus);

	strcpy_s(this->pStatus, length, m.pStatus);
	Monkey::numStringsCreated++;
}

Monkey& Monkey::operator = (const Monkey& m)
{
	// Q2: What does pointer == pointer compare with
	if (this->x == m.x && this->y == m.y && this->pStatus == m.pStatus) return *this;
	//if (this == &m)
	//	return *this;
	this->x = m.x;
	this->y = m.y;
	size_t length = strlen(m.pStatus);
	length += 1;

	// Q3: Why without this line it will cause memory leak?
	delete this->pStatus;
	this->pStatus = new char[length]();
	assert(this->pStatus);

	strcpy_s(this->pStatus, length, m.pStatus);
	Monkey::numStringsCreated++;
	Monkey::numStringsDestroyed++;
	return *this;
}

Monkey::Monkey(int _x)
	:x(_x), y(575)
{
	size_t length = strlen("ThIs tring was initilizxd by a clever user!");
	length += 1;
	this->pStatus = new char[length]();
	strcpy_s(this->pStatus, length, "ThIs tring was initilizxd by a clever user!");
	Monkey::numStringsCreated++;
}

Monkey::Monkey(int _x, int _y )
	:x(_x), y(_y)
{
	size_t length = strlen("ThIs tring was initilizxd by a clever user!");
	length += 1;
	this->pStatus = new char[length]();

	strcpy_s(this->pStatus, length, "ThIs tring was initilizxd by a clever user!");
	Monkey::numStringsCreated++;
}


Monkey::~Monkey()
{
	Monkey::numStringsDestroyed++;
	// Q4: What is this line for? Does delete call the destructor of the content of the pStatus
	// In this case does it call the destructor of char array?
	delete this->pStatus;
	// https://www.learncpp.com/
	// https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/
	// https://www.youtube.com/watch?v=h-HBipu_1P0&list=PL2_aWCzGMAwLZp6LMUKI3cc7pgGsasm2_&ab_channel=mycodeschool
}

int Monkey::getX()
{
	return this->x;
}

int Monkey::getY()
{
	return this->y;
}

char *Monkey::getStatus()
{
	return this->pStatus;
};

void Monkey::printStatus()
{
	Trace::out("Monkey (Status): %s\n", this->pStatus);
}
// Q5: Any code optimization or advice on code behavior?

//---  End of File ---
