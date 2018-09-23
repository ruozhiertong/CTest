/*
Remove Duplicates from Sorted Array.

Given a sorted array nums, remove the duplicates in-place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.

Example 1:

Given nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively.

It doesn't matter what you leave beyond the returned length.

*/


/*
双指针的妙用。解决数组等问题。
一慢一块。
*/
#include <stdio.h>

//使用双指针。
int removeDuplicates(int* nums, int numsSize) {
    if(numsSize == 0)
    	return 0;
    
	int preNum = nums[0];
	int len = 1;
	for(int i = 1; i< numsSize; i++)
	{
		if(nums[i] != preNum)
		{
			nums[len++] = nums[i];
			preNum = nums[i];
		}
	}

	return len;


}


int main()
{
	int arr[3] = {1,1,2};

	int len = removeDuplicates(arr, 3);

	for(int i =0; i < len ; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}