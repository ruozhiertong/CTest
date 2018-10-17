/*
Number of 1 Bits
  Go to Discuss
Write a function that takes an unsigned integer and returns the number of '1' bits it has (also known as the Hamming weight).

Example 1:

Input: 11
Output: 3
Explanation: Integer 11 has binary representation 00000000000000000000000000001011 
Example 2:

Input: 128
Output: 1
Explanation: Integer 128 has binary representation 00000000000000000000000010000000

*/
#include "stdio.h"
//位移操作
int hammingWeight(int n)
{

	int countOne = 0;
	while(n >0)
	{
		if( n-((n >>1)<<1) == 1)
			countOne++;
		n >>=1;
	}
	return countOne;
}

int main()
{
    printf("%d\n",hammingWeight(1));
    return 1;
}