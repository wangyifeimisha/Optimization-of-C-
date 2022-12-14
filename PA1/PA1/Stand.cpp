//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Stand.h"

// -----------------------------------------------
// AZUL_REPLACE_ME_STUB
// this is place holder for compiling purposes
// Delete each AZUL_REPLACE_ME_STUB line
// Replace with your own code
// -----------------------------------------------

// Methods
Stand::Stand()
	:oHead(nullptr), sNext(nullptr), sPrev(nullptr), peakCount(0)
{
}

Stand::~Stand()
{
	Order* temp = this->oHead;
	while (temp) {
		Order* deleteMe;
		deleteMe = temp;
		temp = temp->GetNext();
		delete deleteMe;
	}

}

int Stand::GetCurrOrders() const
{
	int count = 0;
	if (!this->oHead) return count;
	else
	{
		Order* temp = this->oHead;
		while (temp)
		{
			count++;
			temp = temp->GetNext();
		}
		return count;
	}
}

int Stand::GetPeakOrders() const
{
	return peakCount;
}

Order * const Stand::GetHead()
{
	return oHead;
}

void Stand::Remove(const Name name)
{
	if (!this->oHead) { return; }

	Order* temp = this->oHead;
	while (temp)
	{
		if (temp->GetName() == name)
		{
			if (temp->GetPrev()) temp->GetPrev()->SetNext(temp->GetNext());
			if (temp->GetNext()) temp->GetNext()->SetPrev(temp->GetPrev());
			if (temp == this->oHead) this->oHead = temp->GetNext();
			delete temp;
			break;
		}
		else temp = temp->GetNext();
	}
}

void Stand::Add(Order * const pOrder)
{
	if (pOrder)
	{
		if (!this->oHead)
		{
			this->oHead = pOrder;
			this->oHead->SetPrev(nullptr);
			this->oHead->SetNext(nullptr);
		}
		else
		{
			Order* temp = this->oHead;
			while (temp->GetNext()) temp = temp->GetNext();
			temp->SetNext(pOrder);
			pOrder->SetPrev(temp);
		}

		peakCount++;
	}
}

//---  End of File ---
