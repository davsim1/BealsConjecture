// Code by David Michael Simmons.  Current date: June 21, 2013.  Code type: C.  Beal's Problem: If A^x + B^y = C^z, then A, B, and C must have a common prime factor when
// This code is to find examples and counterexamples of Beal's Conjecture using 64bit integers.| x, y, and z are greater than 2 and A, B, C, x, y, and z are positive integers.   
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//This currently allows the use of printf() and scanf() in Microsoft Visual Studio Express 2012
#pragma warning(disable: 4996)

int TRUE = 1;
int FALSE = 0;

//Counters
long long int i = 0;

//Returns base ^ exponent as long long int
long long int power(long long int base, long long int exponent){
	long long int ans = base;
	for(i = 2; i <= exponent; i++)
		ans = ans * base;
	return ans;
}


//Returns true if input is prime.  Needs to be optimized
bool isPrime(long long int num){
	if((num==(long long int)2)||(num==(long long int)3)||(num==(long long int)5)||(num==(long long int)7)||(num==(long long int)11)||(num==(long long int)13)||(num==(long long int)17)||(num==(long long int)19)||(num==(long long int)23)||(num==(long long int)29)||(num==(long long int)31)||(num==(long long int)37)){
		return true;
	}

	if(num<(long long int)37){
		return false;
	}

	if((num % (long long int)2) == 0){
		return false;
	}

	// These loop through an approximation of sqrt(num) the sqrt() function is avoided because it takes type double
	if((num <= (long long int)131)){
		for(i = (long long int)3; i<=(num/(long long int)6); i++){
			if((num % i) == 0){
				return false;
			}
		}
	
	}else{
		for(i = 3; i<=((num/75) + 20); i++){
			if((num % i) == 0){
				return false;
			}
		}
	}
		return true;
}

//Returns true if the given triad has no common prime factors.
bool noCommonPrimeFactors(long long int a, long long  int b, long long  int c){
	long long int aFactor = 0;
	long long int bFactor = 0;
	long long int cFactor = 0;
	/* // Code with brackets
	for (aFactor = 2; aFactor <= a; aFactor++){
		printf(" \ntest1 ");
		if (a % aFactor == 0){
			printf(" A factor of %d is %d ",a, aFactor);
			if(isPrime(aFactor)){
				for (bFactor = 2; bFactor <= b; bFactor++){
					printf(" test2 ");
					if (b % bFactor == 0){
						printf(" A factor of %d is %d ",b, bFactor);
						if(isPrime(bFactor)){
							for (cFactor = 2; cFactor <= c; cFactor++){
								printf(" test3 ");
								if (c % cFactor == 0){
									printf(" A factor of %d is %d ",c, cFactor);
									if(isPrime(cFactor)){
										if((aFactor == bFactor) && (bFactor == cFactor)){
											return false;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	*/
	for (aFactor = 2; aFactor <= a; aFactor++)
		if (a % aFactor == 0)
			if(isPrime(aFactor))
				for (bFactor = 2; bFactor <= b; bFactor++)
					if (b % bFactor == 0)
						if(isPrime(bFactor))
							for (cFactor = 2; cFactor <= c; cFactor++)
								if (c % cFactor == 0)
									if(isPrime(cFactor))
										if((aFactor == bFactor) && (bFactor == cFactor))
											return false;

	return true;
}

//The main code block, returns 0 to exit program.
int main(){
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


	/*
	//power function test
	printf("%llu^%llu=%llu\n",(long long int)2,(long long int)2,power((long long int)2,(long long int)2));
	printf("%llu^%llu=%llu\n",(long long int)4,(long long int)32,power((long long int)4,(long long int)32));
	return 0;
	*/

	/*
	//prime function test
	while(cont == 1){
	printf("enter num for prime test:\n");
	scanf("%d%c",&input,&phantom);

	if(isPrime(input)){
		printf("1that num is prime\n");
	}else{
		printf("0that num is not prime\n");
	}

	printf("enter 1 for continue, 0 for exit:\n");
	scanf("%d%c",&cont,&phantom);
	}
	return 0;
	*/
	/*
	//Prime function test2
	printf("%d",39%3);
	printf("%llu\n\n",(long long int)((long long int)39%(long long int)3));
	
	
	for(i=2;i<=39;i++){
		if(isPrime(i)){
			printf("%llu ",i);
		}
		
}
	return 0;*/
	/*
	// nocommonprimefactors function test
	printf("enter 3 num for prime factor test:\n");
	scanf("%d%c",&input,&phantom);
	scanf("%d%c",&inputTwo,&phantom);
	scanf("%d%c",&inputThree,&phantom);
	printf("%d%d%d",input,inputTwo,inputThree);
	if(noCommonPrimeFactors(input,inputTwo,inputThree)){
		printf("Those numbers do not share a prime factor\n");
	}else{
		printf("Those numbers share a prime factor\n");
	}
	return 0;
	*/

	
	/*
	//power alg test
	printf("A%d x%d B%d y%d C%d z%d\n",A,x,B,y,C,z);
	printf("enter a, x, b, y, c, z:\n");
	scanf("%d%c",&A,&phantom);
	scanf("%d%c",&x,&phantom);
	scanf("%d%c",&B,&phantom);
	scanf("%d%c",&y,&phantom);
	scanf("%d%c",&C,&phantom);
	scanf("%d%c",&z,&phantom);
	printf("A%d x%d B%d y%d C%d z%d\n",A,x,B,y,C,z);
	result = pow(A,x) + pow(B,y) - pow(C,z);
	printf("A%d x%d B%d y%d C%d z%d\n",A,x,B,y,C,z);
	printf("result: %d\n",result);
	return 0;
	*/
	
	/*
	//test
	int j=0;
	for(x=1;x<=3;x++){
		y++;
	for(z=1;z<=2;z++){
		y++;
		for(i=1;i<=4;i++){
			y++;
			//for(j=1;j<=3;j++){
			//	y++;
		}}}
		
	printf("Y%d",y);
	return 0;*/

	//Take inputs.
	printf("A^x + B^y = C^z\n");
	printf("Enter a maximum number to test for A, B, and C:\n");
	scanf("%d%c",&input,&phantom);
	maxBase = input;
	printf("The maximum number to be tested for the bases is %d.\n",maxBase);
	printf("Enter a maximum number to test for x, y, and z:\n");
	scanf("%d%c",&input,&phantom);
	maxExponent = input;
	printf("The maximum number to be tested for the exponents is %d.\n",maxExponent);
	printf("\nThe current output file name is %s.  \nTo change this enter 1, to start test enter another number.\n",outFileName);
	printf("Note: The contents of this file will be erased if the file already exists:\n");
	scanf("%d%c",&input,&phantom);
	if(input==1){
		printf("Enter an output file name or path: ");
		scanf("%s%c",outFileName,&phantom);
	}
	printf("Output file name: %s\n",outFileName);

	

	//Following comments are trial and error for the steps algorithm.

	// This gives the correct steps for the first three or the last three when seperated here
	//                                                                         \/
	//steps = (pow((double)(maxExponent-2),3) + (maxExponent-2)*(maxExponent-1))*(pow((double)(maxBase),3) + (maxBase)*(maxBase+1));
	//This gives best close ans
	//steps = (pow((double)(maxExponent-2),3) + (maxExponent-2))*(pow((double)(maxBase),3) + (maxBase)*(maxBase))-((maxExponent-2)*(maxExponent-2)*(maxBase)*(maxBase));
	//this gives same as previous
	//steps = (pow((double)(maxExponent-2),3) + (maxExponent-2)*(maxExponent-3))*(pow((double)(maxBase),3) + (maxBase)*(maxBase))-3*((maxExponent-2)*(maxExponent-2)*(maxBase)*(maxBase));
	//This works for 5,5
	//steps = (pow((double)(maxExponent-2),3) + (maxExponent-2))*(pow((double)(maxBase),3) + (maxBase)*(maxBase))-((maxExponent-2)*(maxExponent-2)*(maxBase)*(maxBase))-2*((maxBase)*(maxBase))-1;
	//steps = (pow((double)(maxExponent-2),3) + (maxExponent-2))*(pow((double)(maxBase),3) + (maxBase)*(maxBase))-((maxExponent-2)*(maxExponent-2)*(maxBase)*(maxBase));

	//This gives correct steps for no if statements
	steps = power((maxExponent-2),3) * power((maxBase),3) + power((maxExponent-2),3) * power((maxBase),2) + power((maxExponent-2),3) * maxBase + power((maxExponent-2),3) + power((maxExponent-2),2) + maxExponent-2;

	//steps = (pow((double)(maxExponent-2),3) + (maxExponent-2)*(maxExponent-1))*(pow((double)(maxBase),3) + (maxBase)*(maxBase+1));

	//Final correct algorithm for the number of steps in six stacked loops.  First three loops are off of maxExponent, last three off of maxBase.  Each set of three can have no repeats.
	//steps = (maxExponent-2)*(maxExponent-3)*(maxExponent-4)*(maxBase)*(maxBase-1)*(maxBase-2) + (maxExponent-2)*(maxExponent-3)*(maxExponent-4)*(maxBase)*(maxBase-1) + (maxExponent-2)*(maxExponent-3)*(maxExponent-4)*(maxBase) + (maxExponent-2)*(maxExponent-3)*(maxExponent-4) + (maxExponent-2)*(maxExponent-3) + (maxExponent-2);

	
	// New Legit: Main code loops
	// Exponents loops
	for(x = 3; x <= maxExponent; x++){
		stepCount++;
		for(y = 3; y <= maxExponent; y++){ 
			stepCount++;
			for(z = 3; z <= maxExponent; z++){ 
				stepCount++;
				// Bases loops
				for(A = 1; A<=maxBase; A++){
					stepCount++; 
					for(B = 1; B<=maxBase; B++){ 
						stepCount++;
						for(C = 1; C<=maxBase; C++){
							stepCount++; 
							// This calculates and prints how far through the program is with the current test.  Change 4 and 3s to adjust fineness/spacing.
							printf("%.4f%%  %llu / %llu steps.  A^x B^y C^z: %3.llu^%3.llu %3.llu^%3.llu %3.llu^%3.llu\n",((double)100*stepCount)/(steps),stepCount,steps,A,x,B,y,C,z);
							result = power(A,x) + power(B,y) - power(C,z);
							if(result == 0){
								if(noCommonPrimeFactors(A,B,C)){
									// Show CounterExample Result.
									printf("\n%llu^%llu + %llu^%llu - %llu^%llu = %llu \n",A,x,B,y,C,z,result);
									// Write counterexample to file.
									counterFile = fopen(counterFileName, "w");
									fprintf(counterFile, "%llu,%llu,%llu,%llu,%llu,%llu\n",A,x,B,y,C,z);
									fclose(counterFile);
									// This stops the program to show a counterexample to Beale's Hypothesis.
									system("pause");
									return 0;
								}else{
									// This is an example of Beal's Hypothesis, the numbers follow the equation and have a common prime factor
									outputFile = fopen(outFileName, "a");
									fprintf(outputFile, "%llu,%llu,%llu,%llu,%llu,%llu\n",A,x,B,y,C,z);
									fclose(outputFile);
								} 
							}
						}
					}
				}
			}
		}
	}


	/*
	// outdated step counts and errors
	// Exponents loops
	for(x = 3; x <= maxExponent; x++){
		stepCount++;
		for(y = 3; y <= maxExponent; y++){
			stepCount++; 
			if(y != x){
				for(z = 3; z <= maxExponent; z++){
					stepCount++; 
					if(z != y){
						if(z != x){
							// Bases loops
							for(A = 1; A<=maxBase; A++){
								stepCount++; 
								for(B = 1; B<=maxBase; B++){
									stepCount++; 
									if(B != A){
										for(C = 1; C<=maxBase; C++){
											stepCount++; 
													printf("Current step is %d out of about %d steps.\n",stepCount,steps);
											if(C != B){
												if(C != A){
													
													if(noCommonPrimeFactors(A,B,C)){
														result = pow((double)A,(double)x) + pow((double)B,(double)y) - pow((double)C,(double)z);
														if(result == 0){
															printf("\n%d^%d + %d^%d - %d^%d = %d \n",A,x,B,y,C,z,result);
															// Error cases (These need to be changed because if a=b, c could = 2a)
															if(!(pow((double)A,(double)x)==pow((double)B,(double)y)))
																if(!(pow((double)A,(double)x)==pow((double)C,(double)z)))
																	if(!(pow((double)B,(double)y)==pow((double)C,(double)z)))
																		return 0;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	
	*/
	
	/*
	//test: no if statements, different counts, different errors
		for(x = 3; x <= maxExponent; x++){
			stepCount++;
			for(y = 3; y <= maxExponent; y++){
				stepCount++; 
				//if(y != x){
					for(z = 3; z <= maxExponent; z++){
						stepCount++; 
						//if(z != y){
						//	if(z != x){
								// Bases loops
								for(A = 1; A<=maxBase; A++){
									stepCount++; 
									for(B = 1; B<=maxBase; B++){
										stepCount++; 
									//	if(B != A){
											for(C = 1; C<=maxBase; C++){
												stepCount++; 
												printf("Current step is %llu / %llu\n",stepCount,steps);
											//	if(C != B){
											//	if(C != A){

													

													//if(noCommonPrimeFactors(A,B,C)){
														//result = pow((double)A,(double)x) + pow((double)B,(double)y) - pow((double)C,(double)z);
													//	if(result == 0){
														//	printf("\n%d^%d + %d^%d - %d^%d = %d \n",A,x,B,y,C,z,result);
														//	// Error cases (These need to be changed because if a=b, c could = 2a)
														//	if(!(pow((double)A,(double)x)==pow((double)B,(double)y)))
														//		if(!(pow((double)A,(double)x)==pow((double)C,(double)z)))
														//			if(!(pow((double)B,(double)y)==pow((double)C,(double)z)))
														//				return 0;
												//		}
												//	}
												}
											}
										}
									}
								}
							}
						//}
					//}
				//}
			//}
		//}
	//}
					
*/
	
	
	printf("\n\nA,x,B,y,C,z = \n");
	outputFile = fopen(outFileName,"r");
	i=0;
	while((charHolder = fgetc(outputFile)) != EOF){
		printf("%c",charHolder);
		i++;
	}
	fclose(outputFile);
	
	// Default case: The test was unsuccessful.
	printf("\n\nThis test of Beal's Problem with A,B,C up to %llu and x,y,z up to %llu \ndid not find a set of numbers to disprove Beal's Hypothesis.\n\n",maxBase,maxExponent);
	printf("\nThe above number sets fall under Beal's Hypothesis.  \nThey are of format A,x,B,y,C,z and saved as %s\n",outFileName);

	system("pause");
	return 0;
}