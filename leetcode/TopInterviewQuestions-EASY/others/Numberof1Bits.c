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
//位移操作. 其实相当于十进制。
int hammingWeight(int n)
{

	int countOne = 0;
	while(n >0)
	{
		if( n-((n >>1)<<1) == 1) // 或者 /2 来表示。
			countOne++;
		n >>=1;
	}
	return countOne;
}

int main()
{
    printf("%d\n",hammingWeight(128));
    return 1;
}



//==================

public int hammingWeight(int n) {
    int bits = 0;
    int mask = 1;
    for (int i = 0; i < 32; i++) {
        if ((n & mask) != 0) {
            bits++;
        }
        mask <<= 1;
    }
    return bits;
}

int hammingWeight(uint32_t n) {
      int c=0;
        while(n!=0)
        {
            if(n%2==1)
                c++;
            n=n/2;
        }
        return c;
}

