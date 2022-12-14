//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Order.h"

// -----------------------------------------------
// AZUL_REPLACE_ME_STUB
// this is place holder for compiling purposes
// Delete each AZUL_REPLACE_ME_STUB line
// Replace with your own code
// -----------------------------------------------

// Methods

Order::Order()
{
	this->head = nullptr;
	this->next = nullptr;
	this->prev = nullptr;
	this->owner = Name::Unknown;
}

Order::Order(Name name)
{
	this->head = nullptr;
	this->next = nullptr;
	this->prev = nullptr;
	this->owner = name;
}

Order::~Order()
{
	HotDog* temp = this->head;
	while (temp) {
		HotDog* deleteMe;
		deleteMe = temp;
		temp = temp->GetNext();
		delete deleteMe;
	}
	
}

Order::Order(const Order& o)
{
	HotDog* temp = o.head;
	int count = 0;
	while (temp != nullptr)
	{
		count++;
		temp = temp->GetNext();
	}
	
	this->owner = o.GetName();
	this->head = nullptr;
	this->next = nullptr;
	this->prev = nullptr;

	for (int i = 0; i < count; i++)
	{
		HotDog* pNewDog = new HotDog();
		
		this->Add(pNewDog);
	}

	//copy data

	HotDog* pOurs = this->head;
	HotDog* pIn = o.head;

	while (pIn != nullptr && pOurs != nullptr)
	{
		pOurs->Add((Condiments)(pIn->GetCondiments()));
		pOurs = pOurs->GetNext();
		pIn = pIn->GetNext();
	}
}


Order& Order::operator = (const Order& o)
{
	if (this != &o)
	{
		//assert(this->head == nullptr);

		HotDog* temp = o.head;
		int count = 0;
		while (temp != nullptr)
		{
			count++;
			temp = temp->GetNext();
		}

		delete this->head;

		for (int i = 0; i < count; i++)
		{
			HotDog* pNewDog = new HotDog();
			// without this?
			this->Add(pNewDog);
		}

		this->owner = o.GetName();
		//copy data

		HotDog* pOurs = this->head;
		HotDog* pIn = o.head;

		while (pIn != nullptr && pOurs != nullptr)
		{
			pOurs->Add((Condiments)(pIn->GetCondiments()));
			pOurs = pOurs->GetNext();
			pIn = pIn->GetNext();
		}

	}
	return *this;
}



void Order::Add(HotDog *p)
{
	if (p)
	{
		if (this->head!=nullptr)
		{
			HotDog* temp;
			temp = this->head;
			this->head = p;
			this->head->SetNext(temp);
			temp->SetPrev(head);
			
			this->head->SetPrev(nullptr);
		}
		else
		{
			this->head = p;
			this->head->SetPrev(nullptr);
			this->head->SetNext(nullptr);
		}
	}
}

void Order::Remove(HotDog *p)
{
	if (p)
	{
		HotDog* temp;
		temp = this->head;
		if (!temp) return;

		while (temp)
		{
			if (temp == p)
			{
				// if the node is not head or tail
				if (temp->GetPrev()) temp->GetPrev()->SetNext(temp->GetNext());
				if (temp->GetNext()) temp->GetNext()->SetPrev(temp->GetPrev());
				// if the node is head, need to reset head
				if (temp == this->head) this->head = temp->GetNext();
				delete temp;
				break;
			}
			else temp = temp->GetNext();
		}
	}
}

Order * const Order::GetNext() const
{
	return this->next;
}

Order * const Order::GetPrev() const
{
	return this->prev;
}

HotDog * const Order::GetHead() const
{
	return this->head;
}

void Order::SetNext(Order *p)
{
	this->next = p;
	//p->prev = this;
}

void Order::SetPrev(Order *p)
{
	this->prev = p;
	//p->next = this;
}

Name Order::GetName() const
{
	return this->owner;
}

void Order::SetName(Name name)
{
	this->owner = name;
}


//---  End of File ---
