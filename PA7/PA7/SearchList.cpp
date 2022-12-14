//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "SearchList.h"
#include "Node.h"
#include "AList.h"

// --------------------------------
// -->    MODIFY This FILE    <----
// --------------------------------

void SearchList::MergeSort()
{
    myMergeSort(&pHead);
}

void SearchList::myMergeSort(Node** headRef)
{
    Node* head = *headRef;
    if ((head == nullptr) || (head->pNext == nullptr)) return;

    Node* a;
    Node* b;
    frontBackSplit(head, &a, &b);

    myMergeSort(&a);
    myMergeSort(&b);

    *headRef = sortedMerge(a, b);
}

Node* SearchList::sortedMerge(Node* a, Node* b)
{
    Node* result;
    Node* tmp;

    if (a == nullptr)
        return b;
    else if (b == nullptr)
        return a;

    if (a->key <= b->key) {
        result = a;
        tmp = sortedMerge(a->pNext, b);
        result->pNext = tmp;
        if (tmp) tmp->pPrev = result;
    }
    else {
        result = b;
        tmp = sortedMerge(a, b->pNext);
        result->pNext = tmp;
        if (tmp) tmp->pPrev = result;
    }
    return result;
}

void SearchList::frontBackSplit(Node* head, Node** frontRef, Node** backRef)
{
    Node* fast;
    Node* slow;
    slow = head;
    fast = head->pNext;

    while (fast != nullptr) {
        fast = fast->pNext;
        if (fast != nullptr) {
            slow = slow->pNext;
            fast = fast->pNext;
        }
    }

    *frontRef = head;
    *backRef = slow->pNext;
    if(slow->pNext) slow->pNext->pPrev = nullptr;
    slow->pNext = nullptr;
    
}


void SearchList::InsertionSort()
{
    Node* curr = this->pHead;
    Node* sortedHead = nullptr;
    while (curr != nullptr)
    {
        Node* currNext = curr->pNext;
        sortedHead = sortedInsert(sortedHead, curr);
        curr = currNext;
    }
    this->pHead = sortedHead;
}

void SearchList::myInsertionSort(Node** headref)
{
    Node* curr = *headref;
    Node* sortedHead = nullptr;
    while (curr != nullptr)
    {
        Node* currNext = curr->pNext;
        sortedHead = sortedInsert(sortedHead, curr);
        curr = currNext;
    }
    *headref = sortedHead;
}

Node* SearchList::sortedInsert(Node* sortedHead, Node* n)
{
    if (sortedHead == nullptr || sortedHead->key >= n->key)
    {
        n->pNext = sortedHead;
        if (sortedHead) sortedHead->pPrev = n;
        n->pPrev = nullptr;
        return n;
    }
    else
    {
        Node* curr = sortedHead;
        while (curr->pNext != nullptr && curr->pNext->key < n->key)
        {
            curr = curr->pNext;
        }
        n->pNext = curr->pNext;
        n->pPrev = curr;
        if (curr->pNext) curr->pNext->pPrev = n;
        curr->pNext = n;
        
        return sortedHead;
    }
}


void SearchList::MergeComboSort(int CutoffLength)
{
	// add your magic here
    myMergeComboSort(&pHead, CutoffLength);
}

void SearchList::myMergeComboSort(Node** headRef, int length)
{
    Node* head = *headRef;
    if ((head == nullptr) || (head->pNext == nullptr)) return;

    Node* a;
    Node* b;
    currLength tmp;
    tmp = frontBackSplitCombo(head, &a, &b);

    if (tmp.a > length) myMergeComboSort(&a, length);
    else myInsertionSort(&a);
    if (tmp.b > length)myMergeComboSort(&b, length);
    else myInsertionSort(&b);

    *headRef = sortedMerge(a, b);
}

struct currLength SearchList::frontBackSplitCombo(Node* head, Node** front, Node** back)
{
    currLength c;
    int a = 1;
    int b = 0;

    Node* fast;
    Node* slow;
    slow = head;
    fast = head->pNext;

    while (fast != nullptr) {
        fast = fast->pNext;
        b = 0;
        if (fast != nullptr) {
            slow = slow->pNext;
            a++;
            fast = fast->pNext;
            b = 1;
        }
    }

    *front = head;
    *back = slow->pNext;
    if (slow->pNext) slow->pNext->pPrev = nullptr;
    slow->pNext = nullptr;

    c.a = a;
    c.b = (b == 1) ? a - 1 : a;
    return c;
}
// ---  End of File ---
