Finds a local maximum in an integer array using binary search in O(log n) time. Uses sentinel values to handle array boundaries cleanly. Demonstrates divide and conquer reasoning and defensive edge case handling.

Instructions: Given an integer array, find the index of a local maxima in it. A local maximum is an element not smaller than its immediate neighbors if they exist. If an element is at the beginning or end of the array, it only needs to be not smaller than its existing neighbor (the one present) to be considered a local maximum. 

An array might have multiple local maxima, and the solution should return any local maximum.