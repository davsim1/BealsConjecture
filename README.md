# Beal's Conjecture
Author: David Simmons (GitHub: davsim1) 
This is a program to find examples or counterexamples of Beal's Conjecture.  It uses a brute force
approach to do this by looping through all of the possibilities, and it can handle numbers up to 
the size of C's unsigned long long int (2^64 - 1).  I made this for practice using C and git.  C++ 
style booleans were used.

Beal's conjecture states that if A^x + B^y = C^z where where A, B, C, x, y, and z are positive 
integers with x, y, z > 2, then A, B, and C have a common prime factor.  Read more about the problem at: 
https://en.wikipedia.org/wiki/Tijdeman%E2%80%93Zagier_conjecture.  There is a million dollar prize 
to anyone that publishes a proof or counterexample to this conjecture.  Read more about the prize
at: http://www.ams.org/profession/prizes-awards/ams-supported/beal-prize.  Note that no one has 
found and published a counterexample as of 6/2016 even though many have run programs to find one.

