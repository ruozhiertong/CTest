/*
Contains Duplicate.

Given an array of integers, find if the array contains any duplicates.

Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct.

Example 1:

Input: [1,2,3,1]
Output: true

*/

#include <stdio.h>

int containsDuplicate(int* nums, int numsSize) 
{
    for(int i = 0; i < numsSize; i++)
    {
    	int compare = nums[i];
    	for(int j = i + 1; j < numsSize; j++)
    	{
    		if(compare == nums[j])
    			return 1;
    	}
    }
    return 0;
}
int main()
{
	int nums[4] = {1,2,3,1};
	printf("%d\n", containsDuplicate(nums, 4));
	return 0;
}