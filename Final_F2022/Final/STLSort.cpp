//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

// Add additional includes if you want

// Some includes that might be useful
#include <algorithm>
#include <functional>   
#include <numeric> 

#include "STLSort.h"

// ----------------------------------------------
// Sort the STL list:
//
// The list is sorted by LocalData's average value
//    (Higher average first... last is smallest average)
// Each LocalData is also rearranged/sorted 
//    (Sorted Highest first... last number smallest)
 
// Mini Example:
// 
// Original:
//     -5  6  5    // avg: 2
//      7  3  2    // avg: 4
//      1  5  9	   // avg: 5
//     -5 -6 -4    // avg: -5
//      5  6  7	   // avg: 6
// 
// Sort by average (largest avg first)
//      7  6  5    // avg: 6   { Each vector is arranged highest to lowest }
//      9  5  1    // avg: 5
//      7  3  2    // avg: 4
//      6  5 -5    // avg: 2
//     -4 -5 -6    // avg: -5
  
// Assume:
//     Out is initially empty
//     In is read-only
//     Sorted list is stored in Out

// Example: a little more realistic sample
//          recommendation:
//               1) test your solution with this data
//               2) then delete your test code for final submission 
//
// ------------------------ 
// Orig:
// ------------------------ 
//   0:   5  9  1  8 -3
//   1:   6  7  8
//   2:  -6 -4  9  6  7  1  3
//   3:  -5 -2 -9 -3
//   4:  -3 -1  2
//   5:   3  8  8  9  9  5  4
//   6:   0  0 -9 -5  7  8
//   7:   8  2  3  2  7 -1
//   8:   6  3  7  5  3  8
//   9:   1  8  8  5
//        
// ------------------------ 
// Sorted :
// ------------------------ 
//   0:   8  7  6              // avg:7.00 
//   1:   9  9  8  8  5  4  3  // avg:6.57 
//   2:   8  8  5  1           // avg:5.50 
//   3:   8  7  6  5  3  3     // avg:5.33 
//   4:   9  8  5  1 -3        // avg:4.00 
//   5:   8  7  3  2  2 -1     // avg:3.50 
//   6:   9  7  6  3  1 -4 -6  // avg:2.29 
//   7:   8  7  0  0 -5 -9     // avg:0.17 
//   8:   2 -1 -3              // avg:-0.67 
//   9:  -2 -3 -5 -9           // avg:-4.75 
//
// Hopefully you see the obvious pattern
//
// ----------------------------------------------

bool cmpAverage(LocalData& l1, LocalData& l2)
{
	return l1.getAverage() > l2.getAverage();
}

void SortMe(std::list<LocalData> &Out, const std::list<LocalData> &In)
{
	Out = In;
	std::list<LocalData>::iterator it;
	
	for (it = Out.begin(); it != Out.end(); ++it)
	{
		std::sort(it->vect.begin(), it->vect.end());
		std::reverse(it->vect.begin(), it->vect.end());
	}

	Out.sort(cmpAverage);
}


// ---  End of File ---
