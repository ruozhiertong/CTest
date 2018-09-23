/*
Single Number.

Given a non-empty array of integers, every element appears twice except for one. Find that single one.

Note:

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

Example 1:

Input: [2,2,1]
Output: 1

*/
#include <stdio.h>
//目前只能想到愚蠢的暴力 o(n^2)。 当然也可以先排序后再搜索，这个是O(n)，但是排序要O(n^2).
int singleNumber(int* nums, int numsSize) 
{
	int i = 0 , j= 0;
	for(i = 0; i < numsSize; i++)
	{
		for(j = 0; j < numsSize ; j++)
		{
			if(i != j && nums[i] == nums[j])
				break;
		}
		if(j == numsSize)
			break;
	}
	    
	return nums[i];
}

//利用位操作处理。 异或操作。 a⊕0=a，a⊕1= ~a,  a⊕a=0.
int singleNumber2(int * nums, int numsSize)
{
	int result = 0;
	for(int i = 0; i < numsSize; i++)
	{
		result ^= nums[i];
	}
	return result;
}