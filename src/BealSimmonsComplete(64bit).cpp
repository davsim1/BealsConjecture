// Code by David M. Simmons.  Language: C.  Beal's Problem: If A^x + B^y = C^z, 
// then A, B, and C must have a common prime factor when x, y, and z are greater 
// than 2 and A, B, C, x, y, and z are positive integers. 
// This code is to find examples and counterexamples of Beal's Conjecture using 
// 64bit integers.
// Original Date: 6/21/2013
// Current Date: 6/22/2016

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
// This allows the use of printf() and scanf() in Visual Studio Express 2012.
#pragma warning(disable: 4996)

// Returns base ^ exponent as unsigned long long using exponentiation by
// squaring.  This only works with positive numbers.
unsigned long long power(unsigned long long base, unsigned long long exponent) {
	unsigned long long ans = 1;
	
	while (exponent != 0) {
		if ((exponent & 1) != 0) {
			ans *= base;
		}
		exponent >>= 1;
		base *= base;
	}
	
	return ans;
}

// Calculates and returns the gcd of u and v using the iterative version of the 
// standard Euclidean Algorithm.  On this machine, this ran faster than binary, 
// subtraction, and recursive versions of this algorithm.  See previous commits
// for functions that searched for common prime factors rather than computing GCDs.
unsigned long long gcd(unsigned long long u, unsigned long long v) {
	unsigned long long temp;
	
	while (v != 0) {
		temp = v;
		v = u % v;
		u = temp;
	}
	
	return u;
}

// Returns if a, b, and c are pairwise coprime by checking their GCDs.
bool coprime(unsigned long long a, long long int b, long long int c) {
	return gcd(a,b) == 1 && gcd(b,c) == 1 && gcd(a,c) == 1;
}

// Returns true if base can be raised to power without overflow.
bool isValidPower(unsigned long long base, unsigned long long exponent) {
	unsigned long long prev = 0;
	unsigned long long ans = base;
	unsigned long long i = 0;
	
	// Try the sequence of mutiplications that makes base^exponent.
	for (i = 2; i <= exponent; i++) {
		prev = ans;
		ans = ans * base;
		// If it overflows, a positive times a positive will create a smaller 
		// number because it wraps around.
		if (ans < prev) {
			return false;
		}
	}
	return true;
}

// Returns true if the maximum base and exponent can be used without overflow and
// if they can be summed by A^x + B^y without overflow.
bool isValidInput(unsigned long long maxBase, unsigned long long maxExponent) {
	unsigned long long first, second;
	
	if (!isValidPower(maxBase, maxExponent)) {
		return false;
	}
	
	first = power(maxBase, maxExponent);
	second = power(maxBase, maxExponent);
	
	if (first + second < first) {
		return false;
	}
	
	return true;
}

int main() {
	clock_t startTime, timeDifference;
	unsigned long long A, B, C, x, y, z, maxBase, maxExponent, input, steps, stepCount, i;
	char phantom, charHolder;
	char outFileName[100] = "..\\output\\output.csv";
	char counterFileName[50] = "..\\output\\BEALCOUNTEREXAMPLE.txt";
	FILE* outputFile = NULL;
	FILE* counterFile = NULL;
	bool validInput = true;
	int hours, minutes, seconds;

	// Take inputs.
	do {
		// Take max base and exponent.
		printf("A^x + B^y = C^z\n");
		printf("Enter a maximum number to test for A, B, and C:\n");
		scanf("%llu%c", &maxBase, &phantom);
		printf("The maximum number to be tested for the bases is %llu.\n", maxBase);
		
		printf("Enter a maximum number to test for x, y, and z:\n");
		scanf("%llu%c", &maxExponent, &phantom);
		printf("The maximum number to be tested for the exponents is %llu.\n", maxExponent);
		
		// Continue asking for base and exponent until they won't create a
		// unsigned long long overflow.
		if (isValidInput(maxBase, maxExponent)) {
			validInput = true;
		} else {
			validInput = false;
			printf("Your inputed base: %llu and exponent: %llu", maxBase, maxExponent);
			printf(" will cause overflow of C's unsigned long long.\n");
			printf("Ensure that your max input can satisfy: A^x + B^y < %llu\n", ULLONG_MAX);
			printf("Press any key then enter new input.\n");
			system("pause");
			printf("\n");
		}
	} while (!validInput);
	
	// Take output filename.
	printf("\nThe current output file name is %s.  \n", outFileName);
	printf("Note: The contents of this file will be erased if the file already exists:\n");
	printf("To change this enter 1, to start test enter another number:\n");
	scanf("%llu%c", &input, &phantom);
	if (input == 1) {
		printf("Enter an output file name or path: ");
		scanf("%s%c", outFileName, &phantom);
	}
	printf("Output file name: %s\n\n", outFileName);
	
	// Ask to begin.
	printf("Begin process with above values?\n");
	system("pause");
	
	// Begin timing process.
	startTime = clock();
	
	// This gives correct number of steps for no extra if statements.
	steps = power((maxExponent - 2), 3) * power((maxBase), 3) + power((maxExponent - 2), 3) * 
	power((maxBase), 2) + power((maxExponent - 2), 3) * maxBase + power((maxExponent - 2), 3) + 
	power((maxExponent - 2), 2) + maxExponent - 2;

	// Open output file to be closed after computations.
	outputFile = fopen(outFileName, "w");
	// Add header labels.
	fprintf(outputFile, "A,x,B,y,C,z\n");
	
	stepCount = 0;
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
							// This calculates and prints how far the program is.
							// Change 4 and 3s to adjust fineness/spacing.
							printf("%6.2f%% %8llu / %llu steps.  A^x B^y C^z: ", 
								((double)100 * stepCount) / (steps), stepCount, steps);
							printf("%3.llu^%3.llu %3.llu^%3.llu %3.llu^%3.llu\n",
								A, x, B, y, C, z);
							if ((power(A, x) + power(B, y)) == power(C, z)) {
								if (coprime(A, B, C)) {
									// Show counterexample result.
									printf("\nA COUNTEREXAMPLE HAS BEEN FOUND: ");
									printf("\n%llu^%llu + %llu^%llu = %llu^%llu \n", 
										A, x, B, y, C, z);
									// Write counterexample to file.
									counterFile = fopen(counterFileName, "w");
									fprintf(counterFile, "A,x,B,y,C,z\n");
									fprintf(counterFile, "%llu,%llu,%llu,%llu,%llu,%llu\n", 
										A, x, B, y, C, z);
									fclose(counterFile);
									// This stops the program to show a counterexample 
									// to Beal's Hypothesis.
									system("pause");
									return 0;
								} else {
									// This is an example of Beal's Hypothesis, 
									// the numbers follow the equation and have a 
									// common prime factor.
									fprintf(outputFile, "%llu,%llu,%llu,%llu,%llu,%llu\n", 
										A, x, B, y, C, z);
								}
							}
						}
					}
				}
			}
		}
	}

	// Save and close output file.
	fclose(outputFile);
	
	// Print output file to screen.
	printf("\n\nA^x + B^y = C^z \n\n");
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
	
	// Stop timing process and print how much time it took.
	timeDifference = clock() - startTime;
	seconds = timeDifference / CLOCKS_PER_SEC;
	hours = seconds / 3600;
	seconds -= hours * 3600;
	minutes = seconds / 60;
	seconds -= minutes * 60;
	printf("Time taken: %d hours, %d minutes, %d seconds.\n", hours, minutes, seconds);
	
	system("pause");
	return 0;
}