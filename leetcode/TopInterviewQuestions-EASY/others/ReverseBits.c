/*

Reverse Bits
  Go to Discuss
Reverse bits of a given 32 bits unsigned integer.

Example:

Input: 43261596
Output: 964176192
Explanation: 43261596 represented in binary as 00000010100101000001111010011100, 
             return 964176192 represented in binary as 00111001011110000010100101000000.
Follow up:
If this function is called many times, how would you optimize it?

*/
#include "stdio.h"


int reverseBits(int n)
{
	int result = 0;
	for(int i =0 ; i < 32; i++)
	{
		printf("%d \n", (n-((n >>1)<<1)));
		result = (result<<1) + (n-((n >>1)<<1)); // (n-((n >>1)<<1)) ==》n&1
		n >>=1;
	}

	return result;
    
}


int main()
{
    reverseBits(43261596);
    return 0;
}


//简洁
uint32_t reverseBits(uint32_t n) {
    int i = 0;
    uint32_t new_num1 = 0;
  
    for (i= 0; i < 32; i ++) {
        if (!n) {
            break;
        }
        if (n & 1) {
            new_num1 |= (1 << (32 - i - 1));
        }
        n = n >> 1;
    }
    return (new_num1);
}