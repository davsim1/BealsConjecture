// Code by David M. Simmons.  Language: C.  Beal's Problem: If A^x + B^y = C^z, 
// then A, B, and C must have a common prime factor when x, y, and z are greater 
// than 2 and A, B, C, x, y, and z are positive integers. 
// This code is to find examples and counterexamples of Beal's Conjecture using 
// 64bit integers.
// Original Date: 6/21/2013
// Current Date: 6/21/2016

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
// This allows the use of printf() and scanf() in Visual Studio Express 2012.
#pragma warning(disable: 4996)

int TRUE = 1;
int FALSE = 0;

// Counter
long long int i = 0;

// Returns base ^ exponent as long long int.
long long int power(long long int base, long long int exponent) {
	long long int ans = base;
	for (i = 2; i <= exponent; i++)
		ans = ans * base;
	return ans;
}


// Returns true if input is prime.  Needs to be optimized.
bool isPrime(long long int num) {
	// Use some chached primes.
	if ((num == (long long int)2) || (num == (long long int)3) || (num == (long long int)5) ||
	(num == (long long int)7) || (num == (long long int)11) || (num == (long long int)13) ||
	(num == (long long int)17) || (num == (long long int)19) || (num == (long long int)23) ||
	(num == (long long int)29) || (num == (long long int)31) || (num == (long long int)37)) {
		return true;
	}

	if (num < (long long int)37) {
		return false;
	}

	if ((num % (long long int)2) == 0) {
		return false;
	}

	// These loop through an approximation of sqrt(num). The sqrt() function is 
	// avoided because it takes type double
	if ((num <= (long long int)131)) {
		for (i = (long long int)3; i <= (num / (long long int)6); i++) {
			if ((num % i) == 0) {
				return false;
			}
		}

	}
	else {
		for (i = 3; i <= ((num / 75) + 20); i++) {
			if ((num % i) == 0) {
				return false;
			}
		}
	}
	return true;
}

// Returns true if the given triad has no common prime factors.  Needs to be
// optimized.
bool noCommonPrimeFactors(long long int a, long long  int b, long long  int c) {
	long long int aFactor = 0;
	long long int bFactor = 0;
	long long int cFactor = 0;

	// For each factor of A
	for (aFactor = 2; aFactor <= a; aFactor++)
		if (a % aFactor == 0)
			if (isPrime(aFactor))
				// For each factor of B
				for (bFactor = 2; bFactor <= b; bFactor++)
					if (b % bFactor == 0)
						if (isPrime(bFactor))
							// For each factor of C
							for (cFactor = 2; cFactor <= c; cFactor++)
								if (c % cFactor == 0)
									if (isPrime(cFactor))
										// Return false if there is a common factor
										if ((aFactor == bFactor) && (bFactor == cFactor))
											return false;

	return true;
}

int main() {
	//Initializations. 
	long long int x = 0;
	long long int y = 0;
	long long int z = 0;
	long long int A = 0;
	long long int B = 0;
	long long int C = 0;
	long long int result = 0;

	long long int maxBase = 10;
	long long int maxExponent = 10;

	long long int input = 0;
	long long int inputTwo = 0;
	long long int inputThree = 0;
	char phantom = ' ';

	long long int steps = 0;
	long long int stepCount = 0;

	int cont = 1;

	char charHolder = ' ';
	char outFileName[100] = "output.txt";
	char counterFileName[50] = "BEALCOUNTEREXAMPLE.txt";
	FILE* outputFile = NULL;
	FILE* counterFile = NULL;


	//Take inputs.
	printf("A^x + B^y = C^z\n");
	printf("Enter a maximum number to test for A, B, and C:\n");
	scanf("%llu%c", &input, &phantom);
	maxBase = input;
	
	printf("The maximum number to be tested for the bases is %llu.\n", maxBase);
	printf("Enter a maximum number to test for x, y, and z:\n");
	scanf("%llu%c", &input, &phantom);
	maxExponent = input;
	
	printf("The maximum number to be tested for the exponents is %llu.\n", maxExponent);
	printf("\nThe current output file name is %s.  \n", outFileName);
	printf("Note: The contents of this file will be erased if the file already exists:\n");
	printf("To change this enter 1, to start test enter another number:\n");
	scanf("%llu%c", &input, &phantom);
	if (input == 1) {
		printf("Enter an output file name or path: ");
		scanf("%s%c", outFileName, &phantom);
	}
	printf("Output file name: %s\n", outFileName);

	// This gives correct number of steps for no if statements
	steps = power((maxExponent - 2), 3) * power((maxBase), 3) + power((maxExponent - 2), 3) * 
	power((maxBase), 2) + power((maxExponent - 2), 3) * maxBase + power((maxExponent - 2), 3) + 
	power((maxExponent - 2), 2) + maxExponent - 2;

	// Final correct algorithm for the number of steps in six stacked loops.  
	// First three loops are off of maxExponent, last three off of maxBase. 
	// Each set of three can have no repeats.
	//steps = (maxExponent-2)*(maxExponent-3)*(maxExponent-4)*(maxBase)*(maxBase-1)*
	//(maxBase-2) + (maxExponent-2)*(maxExponent-3)*(maxExponent-4)*(maxBase)*(maxBase-1)
	//+ (maxExponent-2)*(maxExponent-3)*(maxExponent-4)*(maxBase) + (maxExponent-2)*
	//(maxExponent-3)*(maxExponent-4) + (maxExponent-2)*(maxExponent-3) + (maxExponent-2);

	// Exponents loops
	// For each x
	for (x = 3; x <= maxExponent; x++) {
		stepCount++;
		// For each y
		for (y = 3; y <= maxExponent; y++) {
			stepCount++;
			// For each z
			for (z = 3; z <= maxExponent; z++) {
				stepCount++;
				
				// Bases loops
				// For each A
				for (A = 1; A <= maxBase; A++) {
					stepCount++;
					// For each B
					for (B = 1; B <= maxBase; B++) {
						stepCount++;
						// For each C
						for (C = 1; C <= maxBase; C++) {
							stepCount++;
							// This calculates and prints how far the program is 
							// with the current test.  Change 4 and 3s to adjust fineness/spacing.
							printf("%6.2f%% %8llu / %llu steps.  A^x B^y C^z: ", 
								((double)100 * stepCount) / (steps), stepCount, steps);
							printf("%3.llu^%3.llu %3.llu^%3.llu %3.llu^%3.llu\n",
								A, x, B, y, C, z);
							result = power(A, x) + power(B, y) - power(C, z);
							if (result == 0) {
								if (noCommonPrimeFactors(A, B, C)) {
									// Show CounterExample Result.
									printf("\n%llu^%llu + %llu^%llu - %llu^%llu = %llu \n", 
										A, x, B, y, C, z, result);
									// Write counterexample to file.
									counterFile = fopen(counterFileName, "w");
									fprintf(counterFile, "%llu,%llu,%llu,%llu,%llu,%llu\n", 
										A, x, B, y, C, z);
									fclose(counterFile);
									// This stops the program to show a counterexample 
									// to Beal's Hypothesis.
									system("pause");
									return 0;
								}
								else {
									// This is an example of Beal's Hypothesis, 
									// the numbers follow the equation and have a common prime factor
									outputFile = fopen(outFileName, "a");
									fprintf(outputFile, "%llu,%llu,%llu,%llu,%llu,%llu\n", 
										A, x, B, y, C, z);
									fclose(outputFile);
								}
							}
						}
					}
				}
			}
		}
	}


	// Print output file to screen.
	printf("\n\nA,x,B,y,C,z = \n");
	outputFile = fopen(outFileName, "r");
	i = 0;
	while ((charHolder = fgetc(outputFile)) != EOF) {
		printf("%c", charHolder);
		i++;
	}
	fclose(outputFile);

	// Default case: The test was unable to find a counterexample.
	printf("\n\nThis test of Beal's Problem with A,B,C up to %llu and x,y,z up to %llu\n", maxBase, maxExponent);
	printf("did not find a set of numbers to disprove Beal's Hypothesis.\n\n");
	printf("\nThe above number sets fall under Beal's Hypothesis.");
	printf("\nThey are of format A,x,B,y,C,z and saved as %s\n", outFileName);

	system("pause");
	return 0;
}