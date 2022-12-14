//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef LANGUAGE_H
#define LANGUAGE_H

class Language
{
public:
    Language() = delete;
    Language(const Language&) = delete;
    Language& operator = (const Language&) = delete;
   ~Language();

    Language(const char* const type);

    // ------------------------------------------
    // Data:  (do not add or modify the data)
    // ------------------------------------------

public:
    Language *pNext;
    char     *poType;
};

#endif

// --- End of File ---
