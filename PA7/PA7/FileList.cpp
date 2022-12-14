//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "AList.h"
#include "Node.h"
#include "FileList.h"

// --------------------------------
// -->    MODIFY This FILE    <----
// --------------------------------

FileList::FileList()
: pHead(nullptr),
NumNodes(0)
{
	// Hint you might need to rework this...
	// if you add data to FileList class
}

FileList::~FileList()
{
	delete pHead;
	pHead = nullptr;
}


void FileList::WriteToFile(const char * const pFileName, AList *pAList)
{
	// Do your magic

	// Make sure you close the file after you fill it
	// Use fopen,fwrite,ftell,...,fclose

	// Hint: Open the file, write the nodes into the file 

	// Grads - You need to do the Load-In-Place technique
	//         You cannot have more than 2 new functions in this method

	// Ungrads - You need to store the data and reconstruct the linked list
	//           You can use as many new/deletes as needed

	// Everyone - Fill in your CustomDestructCommand::Command() that will be used 
	//            in the destructor..

	// Quick sample code... remove this code and replace with your own


	FILE *pFileHandle = nullptr;

	assert(pFileName);
	errno_t status;
	status = fopen_s(&pFileHandle, pFileName, "wb");
	assert(pFileHandle);
	assert(status == 0);

	Node* tmp = pAList->GetHead();
	unsigned int data = tmp->x;
	size_t numBytesWritten = fwrite(&data, 1, sizeof(unsigned int), pFileHandle);
	data = tmp->y;
	numBytesWritten = fwrite(&data, 1, sizeof(unsigned int), pFileHandle);
	data = tmp->z;
	numBytesWritten = fwrite(&data, 1, sizeof(unsigned int), pFileHandle);
	data = tmp->key;
	numBytesWritten = fwrite(&data, 1, sizeof(unsigned int), pFileHandle);
	while (tmp->pNext)
	{
		tmp = tmp->pNext;
		
		data = tmp->x;
		numBytesWritten = fwrite(&data, 1, sizeof(unsigned int), pFileHandle);
		data = tmp->y;
		numBytesWritten = fwrite(&data, 1, sizeof(unsigned int), pFileHandle);
		data = tmp->z;
		numBytesWritten = fwrite(&data, 1, sizeof(unsigned int), pFileHandle);
		data = tmp->key;
		numBytesWritten = fwrite(&data, 1, sizeof(unsigned int), pFileHandle);
	}
	assert(numBytesWritten == sizeof(unsigned int));

	fclose(pFileHandle);

}

FileList::FileList(const char * const pFileName, int numNodes)
{
	// Do your magic here:

	// Create the Linked List... You cannot use the original code
	// The input file, and numNodes is all you need to recreate the FileList
	
	// Hint: Open the file, read and create new nodes, 
	//       fill them with the data from the file

	// Grads - You need to do the Load-In-Place technique
	//         You cannot have more than 2 new functions in this method
	     
	// Ungrads - You need to store the data and reconstruct the linked list
	//           You can use as many new/deletes as needed

	// Everyone - Fill in your CustomDestructCommand::Command() that will be used 
	//            in the destructor.

	// Quick sample code... remove this code and replace with your own

	this->pHead = nullptr;
	this->NumNodes = 0;

	AZUL_REPLACE_ME(pFileName);
	AZUL_REPLACE_ME(numNodes);

	FILE *pFileHandle;

	errno_t status;
	assert(pFileName);
	status = fopen_s(&pFileHandle, pFileName, "rb");
	assert(pFileHandle);
	assert(status == 0);

	int data;

	size_t numBytesRead = fread(&data, 1, sizeof(int), pFileHandle);
	assert(numBytesRead == sizeof(int));
	AZUL_UNUSED_VAR(numBytesRead);
	fclose(pFileHandle);

	assert(data == 0xAABBCCDD);
}

// ---  End of File ---
