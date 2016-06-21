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
#include <limits.h>
// This allows the use of printf() and scanf() in Visual Studio Express 2012.
#pragma warning(disable: 4996)

// Returns base ^ exponent as unsigned long long.
unsigned long long power(unsigned long long base, unsigned long long exponent) {
	unsigned long long ans = base;
	unsigned long long i = 0;
	for (i = 2; i <= exponent; i++)
		ans = ans * base;
	return ans;
}

// Returns true if input is prime.  Needs to be optimized.
bool isPrime(unsigned long long num) {
	unsigned long long i = 0;
	// Use some chached primes.
	if ((num == (unsigned long long)2) || (num == (unsigned long long)3) || 
	(num == (unsigned long long)5) || (num == (unsigned long long)7) || 
	(num == (unsigned long long)11) || (num == (unsigned long long)13) ||
	(num == (unsigned long long)17) || (num == (unsigned long long)19) || 
	(num == (unsigned long long)23) || (num == (unsigned long long)29) || 
	(num == (unsigned long long)31) || (num == (unsigned long long)37)) {
		return true;
	}

	if (num < (unsigned long long)37) {
		return false;
	}

	if ((num % (unsigned long long)2) == 0) {
		return false;
	}

	// These loop through an approximation of sqrt(num). The sqrt() function is 
	// avoided because it takes type double.
	if ((num <= (unsigned long long)131)) {
		for (i = (unsigned long long)3; i <= (num / (unsigned long long)6); i++) {
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

// Returns the minimum of 3 values.
unsigned long long min(unsigned long long a, long long  int b, long long  int c) {
	if (a <= b && a <= c) {
		return a;
	} else if (b <= a && b <= c) {
		return b;
	} else {
		return c;
	}
}

// Returns true if the given triad has no common prime factors.
bool noCommonPrimeFactors(unsigned long long a, long long  int b, long long  int c) {
	unsigned long long minimum = min(a, b, c);
	unsigned long long i = 0;
	
	// Loop from 2 to min(a,b,c)/2 looking for a shared prime factor.
	// Example for why to divide by 2: 100 has no factors 50 < x < 100
	// because 1 < 100/x < 2.  The same goes for all numbers.
	for (i = 2; i <= minimum/(unsigned long long)2 + 1; i++) {
		if (a % i == 0 && b % i == 0 && c % i == 0 && isPrime(i)) {
			return false;
		}
	}
	
	// There are no factors min/2 < x < min, but min may be a factor
	printf("min %llu\n", minimum);
	printf("mod a %d\n", minimum % a == 0);
	printf("mod b %d\n", minimum % b == 0);
	printf("mod c %d\n", minimum % c == 0);
	printf("prime %d\n", isPrime(minimum));
	if (a % minimum == 0 && b % minimum == 0 && c % minimum == 0 && isPrime(minimum)) {
		return false;
	}

	return true;
}

// Returns true if base can be raised to power without overflow.
bool isValidPower(unsigned long long base, unsigned long long exponent) {
	unsigned long long prev = 0;
	unsigned long long ans = base;
	unsigned long long i = 0;
	for (i = 2; i <= exponent; i++) {
		prev = ans;
		ans = ans * base;
		if (ans < prev) {
			return false;
		}
	}
	return true;
}

// Returns true if the maximum base and exponent can be used without overflow and
// if they can be summed with A^x + B^y without overflow.
bool isValidInput(unsigned long long maxBase, unsigned long long maxExponent) {
	if (!isValidPower(maxBase, maxExponent)) {
		return false;
	}
	unsigned long long first = power(maxBase, maxExponent);
	unsigned long long second = power(maxBase, maxExponent);
	if (first + second < first) {
		return false;
	}
	return true;
}

int main() {
	// Initializations. 
	unsigned long long x = 0;
	unsigned long long y = 0;
	unsigned long long z = 0;
	unsigned long long A = 0;
	unsigned long long B = 0;
	unsigned long long C = 0;
	unsigned long long result = 0;

	unsigned long long maxBase = 10;
	unsigned long long maxExponent = 10;

	unsigned long long input = 0;
	unsigned long long inputTwo = 0;
	unsigned long long inputThree = 0;
	char phantom = ' ';

	unsigned long long steps = 0;
	unsigned long long stepCount = 0;

	int cont = 1;

	char charHolder = ' ';
	char outFileName[100] = "..\\output\\output.csv";
	char counterFileName[50] = "..\\output\\BEALCOUNTEREXAMPLE.txt";
	FILE* outputFile = NULL;
	FILE* counterFile = NULL;
	
	bool validInput = true;

	unsigned long long i = 0;

	// Take inputs.
	do {
		printf("A^x + B^y = C^z\n");
		printf("Enter a maximum number to test for A, B, and C:\n");
		scanf("%llu%c", &input, &phantom);
		maxBase = input;
		printf("The maximum number to be tested for the bases is %llu.\n", maxBase);
		
		printf("Enter a maximum number to test for x, y, and z:\n");
		scanf("%llu%c", &input, &phantom);
		maxExponent = input;
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
	
	printf("\nThe current output file name is %s.  \n", outFileName);
	printf("Note: The contents of this file will be erased if the file already exists:\n");
	printf("To change this enter 1, to start test enter another number:\n");
	scanf("%llu%c", &input, &phantom);
	if (input == 1) {
		printf("Enter an output file name or path: ");
		scanf("%s%c", outFileName, &phantom);
	}
	printf("Output file name: %s\n", outFileName);

	// This gives correct number of steps for no extra if statements.
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

	// Open output file to be closed after computations.
	outputFile = fopen(outFileName, "w");
	// Add header labels.
	fprintf(outputFile, "A,x,B,y,C,z\n");
	
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
							if ((power(A, x) + power(B, y)) == power(C, z)) {
								if (noCommonPrimeFactors(A, B, C)) {
									// Show counterexample result.
									printf("\nA COUNTEREXAMPLE HAS BEEN FOUND: ");
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

	system("pause");
	return 0;
}